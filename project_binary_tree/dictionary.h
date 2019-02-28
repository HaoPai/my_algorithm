#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_
#include <iostream>
#include "english_word.h"
#include "trie.h"
using namespace std;
void print_word(English_word &word)
{
    word.print_info();
}
class Dictionary :public Trie<English_word>{
public:
    void traversal();
    void insert();
    void search();
private:
};
void Dictionary::traversal()
{
    Trie<English_word>::traversal(print_word);
}
void Dictionary::insert()
{
    cout << "please input the key of the word: ";
    string str;
    cin >> str;
    English_word word(str);
    cout << "please input the meaning of the word: ";
    getline(cin,str);
    getline(cin,str);
    word.set_meaning(str);
    Trie<English_word>::insert(word);
}
 
void Dictionary::search()
{
    cout << "please input the key you want to search: ";
    string str;
    cin >> str;
    Key key(str);
    English_word word;
    Trie<English_word>::trie_search(key,word);
    print_word(word);
}
#endif
