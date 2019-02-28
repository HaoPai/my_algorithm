#include <iostream>
#define NORDER 4
using namespace std;

class hello {
public:
    hello();
    void info();
    void morning();
    void afternoon();
    void evening();
    const int norder;
    void (hello :: *method[NORDER])();
    string command[NORDER];
private:
};

hello :: hello():norder(NORDER)
{
    method[0] = &hello::info;
    method[1] = &hello::morning;
    method[2] = &hello::afternoon;
    method[3] = &hello::evening;  
    command[0] = "info";
    command[1] = "morning";
    command[2] = "afternoon";
    command[3] = "evening";
}

void hello :: morning ()
{
    cout << "Good morning!" << endl;
}

void hello :: afternoon()
{
    cout << "Good afternoon!" << endl;
}

void hello :: evening()
{
    cout << "Good evening !" << endl;
} 

void hello::info()
{
    cout << "Welcome to hello program!" <<endl;
    cout << "This is a program which can say hello to you!" << endl;
    cout << "Enjoy" << endl;
}
