#include "proxy_server.h"
#include <iostream>

using namespace std;

int main()
{
    Proxy_server server(8080,"wangwj.l-net.cn",9000);
    server.run();
    return 0;
}
