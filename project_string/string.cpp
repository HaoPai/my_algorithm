#include <iostream>
#include <string>

using namespace std;
void strcopy(char *to,const char* from );
int main()
{
    char str_arr[20];
    strcopy(str_arr,"hello,the world!\n");
    string greeting = "how are you!\n";
    cout << greeting;
    cout << str_arr;
    return 0;
}
void strcopy(char *to,const char* from)
{
    while(*to++ = *from++)
        ;
}
