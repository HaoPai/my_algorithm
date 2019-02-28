#include "proxy_server.h"
#include <iostream>

using namespace std;

Proxy_server :: Proxy_server(const unsigned short port_in,
                             const char *target_server_in,
                             const unsigned short target_port_in)
                             :listen_socket(port_in)
{
    target_server = target_server_in;
    target_port = target_port_in;
    commu = NULL;
}

void Proxy_server :: change_target_port(unsigned short int target_port_in)
{
    target_port = target_port_in;
}


void Proxy_server :: run()
{
    listen_socket.listen_client();
    listen_socket.accept_client(commu);
    while(get_request())
        response();
    listen_socket.close_socket();
}

bool Proxy_server :: get_request()
{
    listen_socket.accept_client(commu);
    int nrecv = 0;
    do{
        nrecv = commu -> recv_msg(buffer,BUFFERSIZE );
        buffer[nrecv] = '\0';
        if(nrecv < 0) {
            cout << "Receive error !" << endl;
            return false;
        }
    }while(nrecv == 0);
    cout << "Receive count : " << nrecv <<" bytes."<<endl;
    int i = 0;
    char temp[2] = {'\0','\0'};
    string method_string;
    while(i<nrecv && buffer[i] == ' ') i++;
    while(i<nrecv && buffer[i] != ' '){
        temp[0] = buffer[i];
        method_string.append(temp);
        i++;
    }
    while(i<nrecv && buffer[i] != '/') i++;
    target = "";
    while(i<nrecv && buffer[i] != ' '){
        temp[0] = buffer[i];
        target.append(temp);
        i++;
    }
    cout << "method = " << method_string << endl;
    cout << "target = " << target << endl;
    if(method_string == "GET") method = GET;
    else if(method_string == "POST") method = POST;
    else if(method_string == "PUT") method = PUT;
    else return false;
    return true;
}

void Proxy_server :: response()
{
    string part_1 = "HTTP/1.1 301 OK   \n\r";
    part_1 +=  "Connection: close\n\r";
    string response = part_1 +
                     "Location: http://"+target_server+target+"\n\r\n\r";
    cout << response << endl;
    commu -> send_msg(response.c_str());
    commu->close_socket();
}
