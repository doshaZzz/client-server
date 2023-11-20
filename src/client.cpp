#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <limits.h>
#include <istream>
#include <string>

#define PORT 55555 //порт сервера

int main(){
    //Create a socket
    int socketfd;
    char* hi = "Hi,server";
    char buffer[1024] = {0};
    long valread;

    if((socketfd = socket(AF_INET,SOCK_STREAM,0)) == 0){
        perror("In socket");
        exit(EXIT_FAILURE);
    }
 
    //Structure socket adress
    struct sockaddr_in servaddr = {0};
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr.s_addr);
    
    //Connect to server
    //connect(созданный сокет,указатель на структуру в которой указаны параметры адреса сервера, размер структуры в байтах (длина))
    if((connect(socketfd,(sockaddr*)&servaddr,sizeof(servaddr)))<0){
        perror("In connect");
        exit(EXIT_FAILURE);
    }

    //Read and send message
    send(socketfd , hi , strlen(hi) , 0 );
    std::cout << "------------------Hello message sent-------------------\n" << std::endl;
    valread = read( socketfd , buffer, 1024);
    std::cout << buffer << std::endl;
    return 0;
}
