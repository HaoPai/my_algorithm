#ifndef _L_STRING_H_
#define _L_string_h_
#include <iostream>
#include <stdlib.h>
using namespace std;
int get_line(const char* buffer, const int buffer_size, char  *line , const int line_size);
int get_words( char* buffer, const int buffer_size, char ** &words,const int max_word);

int strlen(const char  *str)
{
    int len =0;
    while(*str++)
        len++;
    return len;
}

void strcpy(char *in , char *out)
{
    while(*in++ = *out++);
    *in = '\0';
}

int strcmp(const char *in,const char *out)
{
    while(*in == *out && *in != '\0' && *out != '\0'){
        in++;
        out ++;
    }
    if(*in == '\0' && *out == '\0')
        return 0;
    else
        return (*in > *out)? 1:-1 ;
}
int get_line(const char* buffer, const int buffer_size,char  *line , const int max_line)
{
    return 0;
}

int get_words(char *buffer,const int buffer_size, char  ** &words, const int max_word)
{
    bool inword = false;
    int nword = 0,count= 0;
    const char *p = buffer;
    while(*p != '\n'&& *p != '\r' && count++ < buffer_size){
       if(*p == ' ' || *p == '\t'){
            inword = false;
        }
       else if(inword == false && *p != ' ' && *p != '\t'){
            inword = true;
            nword ++;
        }     
        p++;
    } 
    if(nword == 0 ) return 0;
    words = (char **) malloc(nword * sizeof (char *));
    char temp_word[max_word];
    int i =0, j= 0;
    p = buffer;
    count = 0;
    inword = false;
    while(*p != '\n' && count++ < buffer_size){
        
        if(*p != ' ' && *p != '\t' && *p != '\r')
            if(inword) temp_word[j++] = *p;
            else {
                inword = true;
                j= 0;
                temp_word[j++] = *p;
            }
        else if(inword){
            temp_word[j] = '\0';
            words[i] = (char *) malloc( strlen(temp_word)+1);
            strcpy(words[i],temp_word);
            inword = false;
            i ++;
        } 
        p++;
    }
    if(inword){
        temp_word[j]='\0';
        words[i] = (char *) malloc (strlen(temp_word));
        strcpy(words[i],temp_word);
    }
    return nword; 
}
#endif

