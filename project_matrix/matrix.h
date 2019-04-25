#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define LINE_N 100

class matrix
{
public:
    matrix();
    matrix(int n);
    ~matrix();
    void input();
    void print();
    void file();
    double value();
    void set_size(int n);
private:
    double **array;
    int count_item(char line[]);
    int set_line(char line[],int l);
    double recursive_value(int row[],int col[]);
    int SIZE;
};

matrix::matrix()
{
    SIZE = 0;
}

matrix::matrix(int n)
{
    set_size(n);
}


void matrix::set_size(int n)
{
    if(SIZE != 0){
        //cout << "Waring: reset size!" << endl;
        for(int i=0;i< SIZE;i++)
            delete []array[i];
        delete []array;
    } 
    array = new double*[n];
    for(int i=0;i<n;i++)
        array[i] = new double[n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            array[i][j] = 0;
    SIZE = n;
}


void matrix::input()
{
    string file = "matrix_in.txt";
    ifstream in;
    in.open(file,ios_base::in);
    int c =0,max = SIZE*SIZE;
    double temp;
    while(!in.eof()&&c<max){
        in >> temp;
        array[c/SIZE][c%SIZE] = temp;
        c++;
    }
    in.close();
}

void matrix::print()
{
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
            cout <<" "<< array[i][j];
        cout << endl;
    }    
}

void matrix::file()
{
    ofstream out;
    out.open("matrix_out.txt",ios_base::out);
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
            out <<" "<< array[i][j];
        out << "\r\n";
    }    
}

double matrix::value()
{
    int *row = new int[SIZE];
    int *col = new int[SIZE];
    for(int i=0;i<SIZE;i++){
        row[i] = col[i] = 1;
    }
    double r = recursive_value(row,col);
    delete []row;
    delete []col;
    return r;
}

double matrix::recursive_value(int row[],int col[]){
    vector<int> rows,cols;
    for(int i=0;i<SIZE;i++){
        if(row[i] == 1) rows.push_back(i);
        if(col[i] == 1) cols.push_back(i);
    }
    int s = rows.size();
    if(rows.size()!=cols.size()){
        cout << "Error detected!" << endl;
        return 0;
    }
    if(s == 1) return array[rows[0]][cols[0]];
    double r =0;
    row[rows[0]] = 0;
    int sign = 1;
    for(int i=0;i<s;i++){
        col[cols[i]] = 0;
        r += array[rows[0]][cols[i]] * recursive_value(row,col)*sign;
        sign *= -1;
        col[cols[i]] = 1;
    }
    row[rows[0]] = 1;
    return r;
}

matrix::~matrix()
{
    set_size(0);
}

