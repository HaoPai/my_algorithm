#ifndef _UTILITY_H_
#define _UTILITY_H_
#include <iostream>
#include <stdlib.h>
using namespace std;
const int max_command_num = 20;
template <class Object>
class Shell
{
public:
    Shell(Object &);
    void main();
    void add_command(string command,void (Object::*fun)());
private:
    Object &instance;
    int count;
    int sys_count;
    string command[max_command_num];
    void (Object::*fun[max_command_num])(); 
    void prompt();
    void help();
    void clear();
    int  get_command(string &cmd);
    bool do_command(int num);
    bool check_command(string cmd,int &num);
};

template <class Object>
Shell<Object>::Shell(Object &obj):instance(obj)
{
    count = 0;
    command[count]="quit";
    count ++;
    command[count]="help";
    count ++;
    command[count]="clear";
    count++;
    sys_count = count;
    for(int i= 0; i < obj.norder; i++){
        add_command(obj.command[i],obj.method[i]);
    }
}

template <class Object>
void Shell<Object>::main()
{
    string cmd;
    while(do_command(get_command(cmd))){
    }
}

template <class Object>
void Shell<Object>::help()
{
    int i;
    for(i=sys_count;i<count;i++)
        cout <<"["<<command[i]<<"]" << endl;
    cout << "[help] for manual" <<endl;
    cout << "[clear] to clear the screen" <<endl;
    cout << "[quit] to quit the program"<<endl;
}

template <class Object>
void Shell<Object>::clear()
{
    system("clear");
}
template <class Object>
int  Shell<Object>:: get_command(string &cmd)
{
    bool waiting = true;
    int num;
    string input;
    prompt();
    while(waiting){
        cin >> input;
        if(check_command(input,num))
            return num;
        else{
            cout << "Warning:invalid command!"<<endl;
            cout << "type <help> for more information" << endl;
            prompt();
        }
    }
    cmd = input;
}

template <class Object>
void Shell<Object>::prompt()
{
    cout << endl;
    cout << "$ Your command: ";

}


template <class Object>
bool Shell<Object>::check_command(string cmd,int &num)
{
    int i;
    for(i=0;i<count;i++)
        if(command[i]== cmd){
             num = i;
             return true;
        }
    return false;
}


template <class Object>
bool Shell<Object>::do_command(int num)
{
    if(num<sys_count)
        switch(num){
        case 0:
            return false;
        case 1:
            help();
            return true;
            break;
        case 2:
            clear();
            return true;
        }
    else{
        (instance.*fun[num-sys_count])();
        return true;
    }
}

template <class Object>
void Shell<Object>::add_command(string cmd,void (Object::*f)())
{
    if(count < max_command_num){
        command[count] = cmd;
        fun[count-sys_count] = f;
        count ++;
    } 
}

#endif

