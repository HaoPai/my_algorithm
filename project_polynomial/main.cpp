#include "polynomial.h"
#include <iostream>

using namespace std;

int main()
{
    Polynomial p,q,m;
    p.read();
    q.read();
    p.print();
    q.print();
    m.equals_sum(p,q);
    m.print();
    m.equals_difference(p,q);
    m.print();
    return 0;
}
