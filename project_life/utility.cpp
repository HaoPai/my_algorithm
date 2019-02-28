#include "utility.h"

bool user_says_yes()
{
    int c;
    bool initial_response = true;
    do{
        if(initial_response){
            cout << " (y,n)? "<< flush;
            initial_response = false;
        }else
            cout << "Respond with either y or n: "<<flush;
        do{
            c = cin.get();
        }while(c=='\n' || c==' ' || c== '\t');
    }while( c!= 'y'&& c!= 'Y' && c != 'n' && c !='N');
    return( c== 'y' || c== 'Y');
}
