#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <limits.h>
#include <arpa/inet.h>
#include <cstring>

#define PORT 55555

int main(){
    int socketfd, acceptsocket;
    struct sockaddr_in servaddr;
    char *hi ="Hellow,client";
    char buffer[30000] = {0};

    //Create a socket
    if((socketfd = socket(AF_INET,SOCK_STREAM,0)) == 0){
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    
    //Structure socket adress
    //(inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr.s_addr)) <=0 ? std::cout << "Invalid address/ Address not supported" << std::endl : std::cout << "Address OK!" << std::endl;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    
    //Bind the socket
    // bind(созданный сокет,указатель структура в которой указаны параметры адреса, размер структуры в байтах (длина))
    if((bind(socketfd, (sockaddr*)&servaddr, sizeof(servaddr))) == -1){
        perror("In bind");
        exit(EXIT_FAILURE); 
    }
    
    //Listen on the socket  
    if(listen(socketfd,5) <0 ){
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        std::cout << "\n------------------Waiting for new connection------------------\n\n" << std::endl;
        //Accept a connection
        if((acceptsocket = accept(socketfd,NULL,NULL))<0){
        //if((acceptsocket = accept(socketfd,(struct sockaddr *)&servaddr,(socklen_t*)&servaddr))<0){
            perror("In accept");
            exit(EXIT_FAILURE);
        };
        //Read and send message
        long valread = read( acceptsocket , buffer, 30000);
        std::cout << buffer << std::endl;
        send(acceptsocket , hi , strlen(hi),0);
        std::cout << "\n------------------Hello message sent-------------------\n" << std::endl;
        close(acceptsocket);
    }
    return 0;
}