#ifndef _ENGLISH_WORD_H_
#define _ENGLISH_WORD_H_
#include "key.h"
class  English_word{
//constructors
public:
    English_word();
    English_word(string word);
    English_word(const English_word &word);
    char key_letter(const int&)const;
    Error_code set_key(string str);
    void set_meaning(const string &str);
    void get_key(Key &key) const;
    void get_meaning(string &str) const;
    void print_info();
//data members 
private:
    Key key;
    string meaning;
};


English_word::English_word():key("")
{
    meaning = "";   
}

Error_code English_word::set_key(string str)
{
    return key.set_key(str);
}

void English_word::set_meaning(const string &str)
{
    meaning = str;
}
English_word::English_word(string word):key(word)
{
    meaning = "";
}

English_word::English_word(const English_word &word)
{
    key = word.key;
    meaning = word.meaning;
}

char English_word::key_letter(const int &position) const
{
    char temp = key.key_letter(position);
    return temp;
}

void English_word::get_key(Key &result) const
{
    result = key;
}

void English_word::get_meaning(string &str) const
{
    str = meaning;
}

void English_word::print_info()
{
    string key_string;
    key.key_str(key_string);
    cout <<key_string<<"\t"<<meaning << endl;
}
#endif
