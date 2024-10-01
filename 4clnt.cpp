#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100

void error_handling(const char* msg);

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[BUF_SIZE];
    int str_len;

    if (argc != 3) {  // IP와 포트번호를 인자로 받습니다.
        std::cout << "Usage: " << argv[0] << " <IP> <port>" << std::endl;
        exit(1);
    }

    // 소켓 생성
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    // 서버 주소 설정
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    // 서버에 연결
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");

    // 명령어 입력을 받아서 서버로 전송
    std::string command;
    std::cout << "Enter a command (e.g., showTasks, joinThreeTables CINEMA_BO HOSPITAL_BO MARKET_BO): ";
    std::getline(std::cin, command);  // 사용자로부터 명령어 입력 받음

    // 서버로 명령어 전송
    write(sock, command.c_str(), command.size());

    // 서버로부터 결과 수신
    while ((str_len = read(sock, message, BUF_SIZE - 1)) > 0) {
        message[str_len] = '\0';  // null-terminate the received message
        std::cout << message;
    }

    close(sock);
    return 0;
}

void error_handling(const char* msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}
