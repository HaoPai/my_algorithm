#include <iostream>
#include "utility.h"
#include "search_list.h"

using namespace std;

int main()
{
    Search_list l;
    Shell<Search_list> sh(l);
    sh.main();
    return 0;
}