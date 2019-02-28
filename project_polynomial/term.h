#ifndef _TERM_H_
#define _TERM_H_
struct Term{
    int degree;
    double coefficient;
//constructors
    Term(int exponent = 0, double scalar = 0);
};

Term :: Term(int exponent,double scalar)
{
    degree = exponent;
    coefficient= scalar;
}   
#endif
