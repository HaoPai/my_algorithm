#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
    matrix m;
    m.set_size(4);
    m.input();
    m.print();
    m.file();
    cout << "value is :" << m.value() << endl;
    return 0;
}