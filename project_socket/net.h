#ifndef _NET_H_
#define _NET_H_
#include <sys/socket.h>
#include <netinet/in.h>
class CommuSocket {
public:
    CommuSocket();
    CommuSocket(const int sock_id,const struct sockaddr_in &addr);
    void connect_server(const char *ipaddr,unsigned short port);
    void send_msg(const char *msg);
    int send_block(char *buffer, int len);
    int recv_msg(char *msg,int len);
    void close_socket();
private:
    int sock_fd;
    struct sockaddr_in peer_addr;
};
class ServerSocket {
public:
    ServerSocket( unsigned short port);
    void listen_client();
    void accept_client(CommuSocket* &commu);
private:
    int sock_fd;
};

#endif

