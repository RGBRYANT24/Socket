#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <cstdio>
#include <cstdlib> 

using namespace std;

void server_5_4_listen() // 监听服务器端程序
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    //创建Socket文件描述符
    //if((server_fd == socket(AF_INET, SOCK_STREAM, 0)) == 0)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        cout << "create socket failed " << endl;
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //绑定到8080端口
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    //绑定Socket到地址
    if(bind(server_fd, (struct sockaddr *)& address, sizeof(address)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //开始监听
    if(listen(server_fd, 3) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    cout << "server_fd " << server_fd << endl;
    //等待客户端连接
    if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    std::cout << "New connection accepted" << std::endl;
    //关闭Socket连接
    close(server_fd);
}

int main()
{
    server_5_4_listen();
    return 0;
}