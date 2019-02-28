#include "net.h"
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#define BUFFERSIZE 500
using namespace std;

int main()
{
    ServerSocket listen_socket(8080);
    CommuSocket *commu;
    listen_socket.listen_client();
    listen_socket.accept_client(commu);
    NetPeer client = listen_socket.get_client();
    char buffer[BUFFERSIZE];
    int nreceive = commu->recv_msg(buffer,BUFFERSIZE);
    cout << buffer << endl;
    string response = "HTTP/1.1 301 OK\n\rContent-Type: text/html;charset = UTF-8\n\r\n\r";
    commu->send_msg(response.c_str());
    ifstream in("index.html");
    while(in){
	string line;
	getline(in,line);
	commu->send_msg(line.c_str());
    }
    commu->close_socket();
    listen_socket.close_socket();
    return 0;
}
