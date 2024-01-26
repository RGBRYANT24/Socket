#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <cstdio>
#include <cstdlib> 
#include <string>
#include <vector>

using namespace std;

void server_5_4_listen() // 监听服务器端程序
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *message = "Hello from server";
    const char *oob_msg = "Server oob message";
    //修改TCP发送缓冲区的大小
    int sendbuf = 32768;
    int len_send = sizeof(sendbuf);
    //设置接受缓冲区大小
    int recvbuf = 32768;
    int len_recv = sizeof(recvbuf);

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
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(8080);

    //在bind之前修改接受缓冲区大小，然后立即读取
    setsockopt(server_fd, SOL_SOCKET, SO_RCVBUF, &recvbuf, sizeof(recvbuf));
    getsockopt(server_fd, SOL_SOCKET, SO_RCVBUF, &recvbuf, (socklen_t* )&len_recv);
    cout << "TCP revive buffer size after resize: " << recvbuf << endl;
    //在bind之前修改发送缓冲区大小，然后立即读取
    setsockopt(server_fd, SOL_SOCKET, SO_SNDBUF, &sendbuf, sizeof(sendbuf));
    getsockopt(server_fd, SOL_SOCKET, SO_SNDBUF, &sendbuf, (socklen_t* )&len_send);

    //绑定Socket到地址
    if(bind(server_fd, (struct sockaddr *)& address, sizeof(address)) < 0)
    {
        perror("bind failed");
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

    //接受客户端发送的信息
    read(new_socket, buffer, 1024);
    cout << "Message from client: " << buffer << endl;
    //向客户端发送信息
    send(new_socket, message, strlen(message), 0);
    cout << "Server message sent" << endl;
    //发送带外数据
    //const char *oob_msg = "Server oob message";
    send(new_socket, oob_msg, strlen(oob_msg), MSG_OOB);
    cout << "OOB Data send" << endl;



    //关闭Socket连接
    close(new_socket);
    close(server_fd);
}

int main()
{
    server_5_4_listen();
    return 0;
}