#include "net.h"
#include <iostream>

using namespace std;

int main()
{
	ServerSocket server(9458);
	CommuSocket *commu;
	server.listen_client();
	server.accept_client(commu);
	commu ->get_local_info();
	NetPeer peer;
	peer = server.get_client();
	cout << peer.ip <<":"<<peer.port<<endl;
	server.close_socket();
}