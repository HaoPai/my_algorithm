#include <iostream>
#include <stdio.h>
#include "net.h"

using namespace std;

int main()
{
    CommuSocket client;
    client.connect_server("127.0.0.1",9458);
    cout << "input the words you want to send!" << endl;
    char send[100];
    gets(send);
    client.send_msg(send);
    char receive[500];
    int nrecv;
    nrecv=client.recv_msg(receive,500);
    receive[nrecv]='\0';
    cout << receive << endl;
    return 0;
}
