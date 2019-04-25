#include <iostream>
#include<vector>
#define QUEEN_SIZE 8
using namespace std;

class Queens {
public:
    Queens();
    bool unguarded(int col) const;
    void insert(int col);
    void remove(int col);
    bool is_solved()const;
    void print()const;
    void get_location(vector<int> &v);
private:
    int count;
    int location[QUEEN_SIZE];
    bool col_free[QUEEN_SIZE];
    bool downward_free[2*QUEEN_SIZE -1];
    bool upward_free[2*QUEEN_SIZE -1];
};

Queens :: Queens()
{
    count = 0;
    for(int i=0;i<QUEEN_SIZE;i++)
        col_free[i] = true;
    for(int i=0;i<2*QUEEN_SIZE -1;i++){
        downward_free[i] = upward_free[i] = true;
    }
}

bool Queens :: unguarded(int col)const
{
    return col_free[col-1]&&upward_free[count+col-1]&&downward_free[col-count+QUEEN_SIZE-2];
}

void Queens::insert(int col)
{
    col_free[col-1] = false;
    upward_free[count+col-1] = false;
    downward_free[col-count+QUEEN_SIZE-2] = false;
    location[count++] = col;
}

void Queens::remove(int col)
{
    count --;
    col_free[col-1] = true;
    upward_free[count+col-1] = true;
    downward_free[col-count+QUEEN_SIZE-2] = true;
}

bool Queens::is_solved()const
{
    return count == QUEEN_SIZE;
}

void Queens::print()const
{
    cout << "find a solution: " << endl;
    for(int i=0;i<QUEEN_SIZE;i++)
        cout << "( " << i+1 << " , " << location[i] << " )" << endl;
}

void Queens::get_location(vector<int> &v)
{
    v.clear();
    for(int i=0;i<QUEEN_SIZE;i++)
        v.push_back(location[i]);
}