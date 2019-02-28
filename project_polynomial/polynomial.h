#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_
#include "extended_queue.h"
#include "term.h"
#include <iostream>
using namespace std;
void clear_cin()
{
    while(cin.peek()!='\n') cin.get();
}
class Polynomial : private Extended_queue<Term>{
public:
    void read();
    void print()const;
    void equals_sum(Polynomial p,Polynomial q);
    void equals_difference(Polynomial p,Polynomial q);
    int degree() const;
private:
    void mult_term(Polynomial p, Term t);
};

void Polynomial :: print() const
{
    Queue_node<Term> *print_node = front;
    bool first_term = true;
    while(print_node != NULL){
        Term &print_term = print_node -> entry;
        if(first_term){
            first_term = false;
            if(print_term.coefficient < 0) cout << "-";
        }
        else if(print_term.coefficient <0 ) cout << "-";
        else cout << "+";
        double r = (print_term.coefficient >= 0 )?
                   print_term.coefficient : -(print_term.coefficient);
        if(r!=1) cout << r;
        if(print_term.degree > 1) cout << "X^" << print_term.degree;
        if(print_term.degree == 1 )cout << "X";
        if(r == 1 && print_term.degree == 0 ) cout << "1";
        print_node = print_node -> next;
    }
    if(first_term) cout << "0";
    cout << endl;
} 

void Polynomial :: read()
{
    clear();
    double coefficient;
    int last_exponent, exponent;
    bool first_term = true;
    cout << "Enter the coefficient and exponents for the polynomial "
         << "one pair per line. Exponents must be in descending order."<<endl
         << "Enter a coefficient 0 or an exponent of 0 to terminate." << endl;
    do{
        cout << "Coefficient ?" << flush;
        cin >> coefficient;
        clear_cin();
        if(coefficient != 0.0){
            cout << "Exponent ?" << flush;
            cin >> exponent;
            clear_cin();
            if(!first_term&&exponent >= last_exponent || exponent < 0 ){
                exponent = 0;
                cout << "Bad exponent: Polynomial terminates without its last term." << endl;
            }
            else{
                Term new_term(exponent,coefficient);
                append(new_term);
                first_term = false;
            }
            last_exponent = exponent;
        }
    }while(coefficient != 0.0 && exponent !=0 );
}

int Polynomial :: degree() const
{
    if(empty()) return -1;
    return (front->entry).degree;
}

void Polynomial :: equals_sum(Polynomial p, Polynomial q)
{
    clear();
    while(!p.empty() || !q.empty()){
        Term p_term,q_term;
        if(p.degree() > q.degree()){
            p.serve_and_retrieve(p_term);
            append(p_term);
        }
        else if(q.degree()>p.degree()){
            q.serve_and_retrieve(q_term);
            append(q_term);
        }
        else {
            p.serve_and_retrieve(p_term);
            q.serve_and_retrieve(q_term);
            if(p_term.coefficient + q_term.coefficient != 0){
                Term answer_term(p_term.degree,
                                 p_term.coefficient + q_term.coefficient);
                append(answer_term);
            }
        }
    }
}

void Polynomial :: equals_difference(Polynomial p, Polynomial q)
{
    clear();
    while(!p.empty() || !q.empty()){
        Term p_term,q_term;
        if(p.degree() > q.degree()){
            p.serve_and_retrieve(p_term);       
            append(p_term);
        }
        else if(q.degree()>p.degree()){
            q.serve_and_retrieve(q_term);
            q_term.coefficient = -q_term.coefficient;
            append(q_term);
        }
        else {
            p.serve_and_retrieve(p_term);
            q.serve_and_retrieve(q_term);
            if(p_term.coefficient - q_term.coefficient != 0){
                Term answer(p_term.degree,p_term.coefficient - q_term.coefficient);
                append(answer);
            }
        }
    }
}
#endif
