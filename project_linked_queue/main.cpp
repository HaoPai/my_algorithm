#include "extended_queue.h"
#include <iostream>

using namespace std;

int main()
{
    Extended_queue<int> numbers,copy;
    int temp;
    bool keep_entering = true;
    while(keep_entering){
        cout << " input a number :";
        cin >> temp;
        numbers.append(temp);
        cout << "continue?";
        char c = cin.get();
        while(c=='\n' || c == '\t' || c == ' ' || c == '\r'){
            c = cin.get();
        }
        if(c!= 'y' && c!= 'Y') keep_entering = false;
    }
    copy = numbers;
    while(!numbers.empty()){
        numbers.retrieve(temp);
        numbers.serve();
        cout << temp << " ";
    }
    cout << endl;
    while(!copy.empty()){
        copy.retrieve(temp);
        copy.serve();
        cout << temp << " ";
    }
    cout << endl;
    return 0;
}  
