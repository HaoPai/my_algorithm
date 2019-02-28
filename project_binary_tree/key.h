#ifndef _KEY_H_
#define _KEY_H_
#include <iostream>
#include "global.h"
using namespace std;
int alphabetic_order(char letter);
int alphabetic_order(char letter)
{
    return letter - 'a';
}
const int max_key_length = 50;
class Key{
public:
    Key();
    Key(string str);
    Error_code set_key(string str);
    void key_str(string &str);
    char key_letter(const int&)const;
    void print_key()const;
private:
    char letter[max_key_length+1];
    int count;
};

void Key::key_str(string &str)
{
    letter[count]= '\0';
    string temp(letter);
    str = temp;
    letter[count] =' ';
}
Error_code Key::set_key(string str)
{
    count =0;
    int position = 0;
    while(str[position]!='\0'&&count < max_key_length){
        char temp_letter = tolower(str[position]);
        if(temp_letter >= 'a'&& temp_letter <= 'z')
            letter[count] = temp_letter;
        else
            return success;
        count ++;
        position ++;
    }
    letter[count] = ' ';
    return success;
}

Key::Key()
{
    count = 0;
    letter[0]=' ';
}
Key::Key(string str)
{
    count = 0;  
    int position = 0;
    int size = str.size();
    while(position<size&&count < max_key_length){
        char temp_letter = tolower(str.at(position));
        if(temp_letter >= 'a'&& temp_letter <= 'z')
            letter[count] = temp_letter;
        else
            return;
        count ++;
        position ++;
    }
    letter[count] = ' ';
}
char Key::key_letter(const int &position)const
{
    if(position > count)
        return ' ';
    else
       return letter[position];
}
void Key::print_key()const
{
    int i;
    for(i=0;i<count;i++)
        cout << letter[i];
    cout << endl;
}
#endif
