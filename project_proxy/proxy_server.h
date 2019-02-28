#ifndef _PROXY_SERVER_H_
#define _PROXY_SERVER_H_
#include "net.h"
#include <string>
#define BUFFERSIZE 500
using namespace std;
enum Method { GET , POST , PUT };
class  Proxy_server{
public:
    Proxy_server(const unsigned short port_in,
                 const char *targer_server_in,
                 const unsigned short target_port_in);
    void change_target_port(const unsigned short port);
    void run();
private:
    ServerSocket listen_socket;
    CommuSocket  *commu;
    string target_server;
    unsigned short target_port;
    char buffer[BUFFERSIZE];
    Method method;
    string target;
    bool get_request();
    void response();
};

#endif
