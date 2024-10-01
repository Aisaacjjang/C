#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <mariadb/conncpp.hpp>

#define BUF_SIZE 100
#define MAX_CLNT 256

void *handle_clnt(void *arg);
void send_msg(char *msg, int len);
void error_handling(const char *msg);
void process_db_command(int clnt_sock, const char* command);

// 클라이언트 관련 전역 변수
int clnt_cnt = 0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutx;

// MariaDB 전역 연결 변수
std::unique_ptr<sql::Connection> conn;

// MariaDB 연결을 초기화하는 함수
void initialize_db_connection() {
    try {
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        sql::SQLString url("jdbc:mariadb://10.10.20.113:3306/CARD_INFO");
        sql::Properties properties({{"user", "isac"}, {"password", "1234"}});
        conn = std::unique_ptr<sql::Connection>(driver->connect(url, properties));
        std::cout << "Database connection established successfully." << std::endl;
    } catch (sql::SQLException& e) {
        std::cerr << "DB Connection Error: " << e.what() << std::endl;
        exit(1);  // 연결 실패 시 서버 실행 중단
    }
}

int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;
    pthread_t t_id;

    if (argc != 2) {
        std::cout << "Usage : " << argv[0] << " <port>" << std::endl;
        exit(1);
    }

    // MariaDB 연결 초기화
    initialize_db_connection();

    // 서버 소켓 설정
    pthread_mutex_init(&mutx, NULL);
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    // 클라이언트 요청 처리 루프
    while (1) {
        clnt_adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

        pthread_mutex_lock(&mutx);
        clnt_socks[clnt_cnt++] = clnt_sock;
        pthread_mutex_unlock(&mutx);

        pthread_create(&t_id, NULL, handle_clnt, reinterpret_cast<void*>(&clnt_sock));
        pthread_detach(t_id);
        std::cout << "Connected client IP: " << inet_ntoa(clnt_adr.sin_addr) << std::endl;
    }

    close(serv_sock);
    return 0;
}

void *handle_clnt(void *arg) {
    int clnt_sock = *reinterpret_cast<int*>(arg);
    int str_len = 0;
    char msg[BUF_SIZE];

    while ((str_len = read(clnt_sock, msg, sizeof(msg))) != 0) {
        msg[str_len] = '\0';
        process_db_command(clnt_sock, msg);  // MariaDB 관련 명령 처리
    }

    pthread_mutex_lock(&mutx);
    for (int i = 0; i < clnt_cnt; i++) {
        if (clnt_sock == clnt_socks[i]) {
            while (i++ < clnt_cnt - 1)
                clnt_socks[i] = clnt_socks[i + 1];
            break;
        }
    }
    clnt_cnt--;
    pthread_mutex_unlock(&mutx);
    close(clnt_sock);
    return NULL;
}

void process_db_command(int clnt_sock, const char* command) {
    try {
        // MariaDB 연결이 유효한지 검사
        if (!conn || conn->isClosed()) {
            std::cerr << "DB Connection is closed. Reconnecting..." << std::endl;
            initialize_db_connection();  // 연결이 끊긴 경우 다시 연결
        }

        if (strncmp(command, "showTasks", 9) == 0) {
            std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
            std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery("SELECT * FROM tasks"));

            std::string result = "Tasks:\n";
            while (res->next()) {
                result += "ID: " + std::to_string(res->getInt(1)) +
                          ", Description: " + res->getString(2) +
                          ", Completed: " + (res->getBoolean(3) ? "Yes" : "No") + "\n";
            }
            write(clnt_sock, result.c_str(), result.size());
        }
        else if (strncmp(command, "addTask", 7) == 0) {
            char description[BUF_SIZE];
            sscanf(command, "addTask %s", description);

            std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO tasks (description) VALUES (?)"));
            stmnt->setString(1, description);
            stmnt->executeQuery();

            const char* msg = "Task added successfully\n";
            write(clnt_sock, msg, strlen(msg));
        }
        else if (strncmp(command, "updateTaskStatus", 16) == 0) {
            int id;
            int completed_int;
            sscanf(command, "updateTaskStatus %d %d", &id, &completed_int);
            bool completed = (completed_int != 0);

            std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("UPDATE tasks SET completed = ? WHERE id = ?"));
            stmnt->setBoolean(1, completed);
            stmnt->setInt(2, id);
            stmnt->executeQuery();

            const char* msg = "Task status updated\n";
            write(clnt_sock, msg, strlen(msg));
        }

        else if (strncmp(command, "deleteTask", 10) == 0) {
            int id;
            sscanf(command, "deleteTask %d", &id);

            std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("DELETE FROM tasks WHERE id = ?"));
            stmnt->setInt(1, id);
            stmnt->executeQuery();

            const char* msg = "Task deleted\n";
            write(clnt_sock, msg, strlen(msg));
        }
    } catch (sql::SQLException& e) {
        std::cerr << "DB Error: " << e.what() << std::endl;
        const char* err_msg = "Database error occurred\n";
        write(clnt_sock, err_msg, strlen(err_msg));
    }
}
void executeJoinQuery(const std::string& table1, int clnt_sock) {
    try {
        // MariaDB 연결 설정
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        sql::SQLString url("jdbc:mariadb://10.10.20.113/CARD_INFO");
        sql::Properties properties({{"user", "isac"}, {"password", "1234"}});
        std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

        // 기본 SELECT 쿼리 시작 부분 (테이블 1개 조인)
        std::string query =
            "SELECT BASIC.NUM AS 카드번호, "
            "BASIC.COM AS 카드회사, "
            "BASIC.NAME AS 카드이름, "
            "BASIC.FEE AS 연회비, "
            + table1 + ".VALUE AS 첫번째_혜택, " + table1 + ".CODE AS 첫번째_코드 "
                                                            "FROM BASIC "
                                                            "JOIN " + table1 + " ON BASIC.NUM = " + table1 + ".NUM;";

        // 쿼리 실행
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

        // 결과 출력
        std::string result = "Tasks:\n";
        while (res->next()) {
            result += "카드번호: " + std::to_string(res->getInt("카드번호")) + "\n";
            result += "카드회사: " + res->getString("카드회사") + "\n";
            result += "카드이름: " + res->getString("카드이름") + "\n";
            result += "연회비: " + std::to_string(res->getInt("연회비")) + "\n";
            result += "첫번째 혜택: " + res->getString("첫번째_혜택") + "\n";
            result += "첫번째 코드: " + res->getString("첫번째_코드") + "\n";
            result += "---------------------\n";
        }

        // 클라이언트로 결과 전송
        if (write(clnt_sock, result.c_str(), result.size()) == -1) {
            std::cerr << "Failed to send result to client\n";
        }

    } catch (sql::SQLException& e) {
        std::cerr << "Error executing query: " << e.what() << std::endl;
        const char* err_msg = "Database error occurred\n";
        if (write(clnt_sock, err_msg, strlen(err_msg)) == -1) {
            std::cerr << "Failed to send error message to client\n";
        }
    }
}

// 혜택 2개 처리
void executeJoinQuery(const std::string& table1, const std::string& table2, int clnt_sock) {
    try {
        // MariaDB 연결 설정
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        sql::SQLString url("jdbc:mariadb://10.10.20.113/CARD_INFO");
        sql::Properties properties({{"user", "isac"}, {"password", "1234"}});
        std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

        // 기본 SELECT 쿼리 시작 부분 (테이블 2개 조인)
        std::string query =
            "SELECT BASIC.NUM AS 카드번호, "
            "BASIC.COM AS 카드회사, "
            "BASIC.NAME AS 카드이름, "
            "BASIC.FEE AS 연회비, "
            + table1 + ".VALUE AS 첫번째_혜택, " + table1 + ".CODE AS 첫번째_코드, "
            + table2 + ".VALUE AS 두번째_혜택, " + table2 + ".CODE AS 두번째_코드 "
                                                            "FROM BASIC "
                                                            "JOIN " + table1 + " ON BASIC.NUM = " + table1 + ".NUM "
                                                     "JOIN " + table2 + " ON BASIC.NUM = " + table2 + ".NUM;";

        // 쿼리 실행
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

        // 결과 출력
        std::string result = "Tasks:\n";
        while (res->next()) {
            result += "카드번호: " + std::to_string(res->getInt("카드번호")) + "\n";
            result += "카드회사: " + res->getString("카드회사") + "\n";
            result += "카드이름: " + res->getString("카드이름") + "\n";
            result += "연회비: " + std::to_string(res->getInt("연회비")) + "\n";
            result += "첫번째 혜택: " + res->getString("첫번째_혜택") + "\n";
            result += "첫번째 코드: " + res->getString("첫번째_코드") + "\n";
            result += "두번째 혜택: " + res->getString("두번째_혜택") + "\n";
            result += "두번째 코드: " + res->getString("두번째_코드") + "\n";
            result += "---------------------\n";
        }

        // 클라이언트로 결과 전송
        if (write(clnt_sock, result.c_str(), result.size()) == -1) {
            std::cerr << "Failed to send result to client\n";
        }

    } catch (sql::SQLException& e) {
        std::cerr << "Error executing query: " << e.what() << std::endl;
        const char* err_msg = "Database error occurred\n";
        if (write(clnt_sock, err_msg, strlen(err_msg)) == -1) {
            std::cerr << "Failed to send error message to client\n";
        }
    }
}

// 혜택 3개 처리
void executeJoinQuery(const std::string& table1, const std::string& table2, const std::string& table3, int clnt_sock) {
    try {
        // MariaDB 연결 설정
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        sql::SQLString url("jdbc:mariadb://10.10.20.113/CARD_INFO");
        sql::Properties properties({{"user", "isac"}, {"password", "1234"}});
        std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

        // 기본 SELECT 쿼리 시작 부분 (테이블 3개 조인)
        std::string query =
            "SELECT BASIC.NUM AS 카드번호, "
            "BASIC.COM AS 카드회사, "
            "BASIC.NAME AS 카드이름, "
            "BASIC.FEE AS 연회비, "
            + table1 + ".VALUE AS 첫번째_혜택, " + table1 + ".CODE AS 첫번째_코드, "
            + table2 + ".VALUE AS 두번째_혜택, " + table2 + ".CODE AS 두번째_코드, "
            + table3 + ".VALUE AS 세번째_혜택, " + table3 + ".CODE AS 세번째_코드 "
                                                            "FROM BASIC "
                                                            "JOIN " + table1 + " ON BASIC.NUM = " + table1 + ".NUM "
                                                     "JOIN " + table2 + " ON BASIC.NUM = " + table2 + ".NUM "
                                                     "JOIN " + table3 + " ON BASIC.NUM = " + table3 + ".NUM;";

        // 쿼리 실행
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

        // 결과 출력
        std::string result = "Tasks:\n";
        while (res->next()) {
            result += "카드번호: " + std::to_string(res->getInt("카드번호")) + "\n";
            result += "카드회사: " + res->getString("카드회사") + "\n";
            result += "카드이름: " + res->getString("카드이름") + "\n";
            result += "연회비: " + std::to_string(res->getInt("연회비")) + "\n";
            result += "첫번째 혜택: " + res->getString("첫번째_혜택") + "\n";
            result += "첫번째 코드: " + res->getString("첫번째_코드") + "\n";
            result += "두번째 혜택: " + res->getString("두번째_혜택") + "\n";
            result += "두번째 코드: " + res->getString("두번째_코드") + "\n";
            result += "세번째 혜택: " + res->getString("세번째_혜택") + "\n";
            result += "세번째 코드: " + res->getString("세번째_코드") + "\n";
            result += "---------------------\n";
        }

        // 클라이언트로 결과 전송
        if (write(clnt_sock, result.c_str(), result.size()) == -1) {
            std::cerr << "Failed to send result to client\n";
        }

    } catch (sql::SQLException& e) {
        std::cerr << "Error executing query: " << e.what() << std::endl;
        const char* err_msg = "Database error occurred\n";
        if (write(clnt_sock, err_msg, strlen(err_msg)) == -1) {
            std::cerr << "Failed to send error message to client\n";
        }
    }
}

void error_handling(const char *msg) {
    std::cerr << msg << std::endl;
    exit(1);
}
