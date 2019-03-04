#include <iostream>
#include "utility.h"
#include "sort_list.h"

using namespace std;

int main()
{
    Sort_list l;
    Shell<Sort_list> sh(l);
    sh.main();
    return 0;
}