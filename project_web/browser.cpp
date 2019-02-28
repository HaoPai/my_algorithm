#include "net.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
    CommuSocket con;
    con.connect_server("127.0.0.1",80);
    string request = "GET /test.txt HTTP/1.1\n\r";
    con.send_msg(request.c_str());
    char buffer[500];
    con.recv_msg(buffer,500);
    cout << buffer << endl;
    con.close_socket();
    return 0;
}
