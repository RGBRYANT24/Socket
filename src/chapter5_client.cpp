#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

void client_5_4()
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // 创建socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "\n Socket creation error \n";
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
      
    // 将IPv4和IPv6地址从文本转换为二进制形式
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cout << "\nInvalid address/ Address not supported \n";
        return;
    }
  
    // 连接到服务器
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "\nConnection Failed \n";
        return;
    }

    // 发送一个消息
    const char* hello = "Hello from client";
    send(sock, hello, strlen(hello), 0);
    std::cout << "Hello message sent\n";

    // 读取服务器的响应
    valread = read(sock, buffer, 1024);
    std::cout << "Server message: " << buffer << std::endl;
    memset(buffer, '\0', strlen(buffer));
    valread = recv(sock, buffer, 1023, 0);
    std::cout << "Server OOB message: " << buffer << std::endl;

    // 关闭socket
    close(sock);
}

int main() {
    client_5_4();
    return 0;
}
