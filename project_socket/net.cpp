#include "net.h"
#include <sys/socket.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
CommuSocket::CommuSocket()
{
    if((sock_fd = socket(AF_INET,SOCK_STREAM,0))==-1){
        cout << "create socket error!"<<endl;   
        exit(1);
    }
}
int CommuSocket :: send_block(char *buffer, int len)
{
    if(send(sock_fd,buffer,len,0)<0){
        cout << "send_error!" << endl;
    }
}
    
CommuSocket::CommuSocket(const int sock_id,const struct sockaddr_in &addr)
{
    sock_fd = sock_id;
    peer_addr = addr;
}
void CommuSocket::connect_server(const char *ipaddr,unsigned short port)
{
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_addr.s_addr = inet_addr(ipaddr);
    peer_addr.sin_port = htons(port);
    if(connect(sock_fd,(struct sockaddr *)(&peer_addr),sizeof(struct sockaddr))== -1){
        cout << "connect error!"<<endl;
        exit(1);
    }
}

void CommuSocket::send_msg(const char *msg)
{
    int msg_len;
    if((msg_len = strlen(msg))<= 200){
        if(send(sock_fd,msg,strlen(msg),0)<0){
            cout << "send error!"<<endl;
            exit(1);
        }
    }
    else
        cout << "Buffer overflowed!"<<endl;
}

int  CommuSocket::recv_msg(char *msg,int len)
{
    return recv(sock_fd,msg,len,0);
}
void CommuSocket::close_socket()
{
    close(sock_fd);
}
ServerSocket::ServerSocket(unsigned short port)
{
    if((sock_fd = socket(AF_INET,SOCK_STREAM,0))==-1){
        cout << "create socket error!"<<endl;
        exit(1);
    }
    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(my_addr.sin_zero),sizeof(my_addr.sin_zero));
    if(bind(sock_fd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr)) == -1){
        cout << "bind error"<<endl;
        exit(1);
    }
}
void ServerSocket::listen_client()
{
    cout << endl << "Server: Server is listenning !"<<endl;
    if(listen(sock_fd,20)== -1){
        cout << "listen error" << endl;
        exit(1);
    }
}
void ServerSocket::accept_client(CommuSocket* &commu)
{
    int sin_size = sizeof(struct sockaddr_in);
    struct sockaddr_in client_addr;
    int commu_sock_fd;
    if((commu_sock_fd=accept(sock_fd,(struct sockaddr *)(&client_addr),(socklen_t *)&sin_size))==-1){
        cout << "accept error!"<<endl;
        exit(1);
    }
    cout << endl << "Server: acepted from "<< inet_ntoa(client_addr.sin_addr)<<endl;
    commu = new CommuSocket(commu_sock_fd,client_addr);
}


