#include <iostream>
#include <fstream>
#include "net.h"
#include "l_string.h"
#define BUFFERSIZE 1024
#define TARGETSIZE 512
using namespace std;
int get_message(char *buffer, int buffer_size);
enum Request { file, chat, disconnect,down,none};
typedef struct {
    Request request;
    char target[TARGETSIZE];
} L_msg;

class Server : public ServerSocket{
public:
    Server( unsigned short port);
    void run();
private:
    CommuSocket *commu;
    char receive[BUFFERSIZE];
    char send[BUFFERSIZE];
    int nrecv,nsend;
    L_msg msg;
    bool keep_running;
    bool get_message();
    int do_command();
    bool endline( char *str,int size);
};
    

int main()
{
    Server server(9458);
    server.run();
    return 0;
}

Server :: Server( unsigned short port) : ServerSocket(port)
{
    commu = NULL;
    nrecv = nsend = 0;
    keep_running = true;
}

void Server::run()
{
    while(keep_running){
        listen_client();
        accept_client(commu);
        commu->send_msg("Welcome to L_NET!\r\n");
        commu->send_msg("$:");
        while(get_message()){
            do_command();
        }
        commu->close_socket();
        delete commu;
        commu = NULL;
    }
}

bool Server::endline(char *str,int size)
{
    int count = 0;
    while(*str++ != '\n' && count++ < size);
    if(count < size){
        *str = '\0';
        return true;
    }     
    else return false;
}
 
bool Server :: get_message()
{
    bool keep_receiving = true;
    int all_bytes = 0;
    while(keep_receiving){
        nrecv = commu->recv_msg(receive+all_bytes,BUFFERSIZE-all_bytes);
        if(endline(receive+all_bytes,nrecv)) keep_receiving = false;
        all_bytes += nrecv;
    }
    char ** words ;
    int n = get_words(receive,BUFFERSIZE,words,100); 
    if(n<=0){
        msg.request = none;
        return true;
    }
    if(strcmp(words[0],"disconnect")==0){
        msg.request = disconnect;
        return false;
    }
    else if(strcmp(words[0], "serverdown")==0){
        cout << "Server will be shutdown" << endl;
        keep_running = false;
        msg.request = down;
        return false;
    }
    else if(strcmp(words[0],"file")==0){
        msg.request = file;
    }
    else{
        msg.request = chat;
    }
    return true;
}


int Server:: do_command()
{
    cout << receive;
    fstream f;
    char file_buffer[100];
    switch(msg.request){
    case down:
        commu->send_msg("server will be shutdown!\r\n");
        cout << "Warning : server will be shudown!" << endl;
        keep_running = false;
        break;
    case file:
        commu->send_msg("prepare file...\r\n");
        f.open("net.h",ios::in);
        f.read(file_buffer,100);
        commu->send_block(file_buffer,100);
        break;
    case disconnect:
        commu->send_msg("connection will be terminated!\r\n");
        break;
    case chat:
        commu->send_msg("how are you !\r\n");
        break;
    }
    commu->send_msg("$:");
  
}
