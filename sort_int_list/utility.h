#ifndef _UTILITY_H_
#define _UTILITY_H_
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;


//function to  generate ramdom number to "data.txt"
void rand_file(int n,int MIN,int MAX);

void rand_file(int n,int MIN,int MAX)
{
    ofstream out("data.txt");
    srand((unsigned int )time(NULL));
    while(n>0){
        int temp = rand()%(MAX - MIN) + MIN;
        out << " " << temp;
        n --;
    }
    out.close();
}
// class Shell
const int max_command_num = 100;
template <class Object>
class Shell
{
public:
    Shell(Object &);
    void main();
    void add_command(string command,void (Object::*fun)());
private:
    Object &instance;
    bool show_time;
    int count;
    int sys_count;
    string command[max_command_num];
    void (Object::*fun[max_command_num])(); 
    void prompt();
    void help();
    void clear();
    void time();
    int  get_command(string &cmd);
    bool do_command(int num);
    bool check_command(string cmd,int &num);
};

template <class Object>
Shell<Object>::Shell(Object &obj):instance(obj)
{
    show_time = false;
    count = 0;
    command[count]="quit";
    count ++;
    command[count]="help";
    count ++;
    command[count]="clear";
    count++;
    command[count]="time";
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
    cout << "[time] to show run time" << endl;
}

template <class Object>
void Shell<Object>::clear()
{
    system("clear");
}

template <class Object>
void Shell<Object>::time()
{
    show_time = (show_time == true)? false : true;
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
        case 3:
            time();
            return true;
        }
    else{
        clock_t start,finish;
        start = clock();
        (instance.*fun[num-sys_count])();
        finish = clock();
        if(show_time)
            cout << "Time used: "<< double(finish - start)/((double)CLOCKS_PER_SEC/1000) << " milliseconds." << endl;
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

