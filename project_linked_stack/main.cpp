#include "stack.h"
#include <iostream>

using namespace std;

int main()
{
    Stack<int> numbers,copy;
    int temp;
    bool keep_entering = true;
    while(keep_entering){
        cout << " input a number :";
        cin >> temp;
        numbers.push(temp);
        cout << "continue?";
        char c = cin.get();
        while(c=='\n' || c == '\t' || c == ' ' || c == '\r'){
            c = cin.get();
        }
        if(c!= 'y' && c!= 'Y') keep_entering = false;
    }
    copy = numbers;
    while(!numbers.empty()){
        numbers.top(temp);
        numbers.pop();
        cout << temp << " ";
    }
    cout << endl;
    while(!copy.empty()){
        copy.top(temp);
        copy.pop();
        cout << temp << " ";
    }
    cout << endl;
    return 0;
}  
