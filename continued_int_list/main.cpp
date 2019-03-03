#include <iostream>
#include "utility.h"
#include "list.h"

using namespace std;

int main()
{
    List l;
    Shell<List> sh(l);
    sh.main();
    return 0;
}