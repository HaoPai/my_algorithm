#include "life.h"
#include <iostream>
#include <math.h>
using namespace std;
void Life::initialize()
{
    int row,col;
    for(row = 0; row < maxrow+2; row ++)
        for(col= 0;col < maxcol+2; col ++)
            grid[row][col] = 0;
    cout << "List coordinates for living cells."<<endl;
    cout << "Terminate the list with the special pair (-1,-1)"<<endl;
    cin >> row >> col;
    while( row!= -1 || col != -1){
        if(row >= 1 && row <= maxrow)
            if(col >= 1 && col <= maxcol)
                grid[row][col] = 1;
            else
                cout << "Column " << col << " is out of range." << endl;
        else 
            cout << "Row " << row << " is out of range." << endl;
        cin >> row >> col;
    }
}

void Life::print()
{
    int row,col;
    for(col = 1; col <= maxcol; col++)
        cout<< "  ——  ";
    cout << endl;
    for(row = 1; row <= maxrow; row++){
        cout << "| ";
        for(col = 1; col <= maxcol; col ++){
            if(grid[row][col])
                cout << " O  | ";
            else cout << "    | ";
        }
        cout << endl;
        for(col = 1; col <= maxcol ; col ++)
            cout << "  ——  ";
        cout << endl;
    }
}
 

void Life::update()
{
    int row,col;
    int new_grid[maxrow+2][maxcol+2];
    for(row = 1; row <= maxrow; row++)
        for(col = 1;col <= maxcol; col++){
            switch(neighbor_count(row,col)){
            case 2:
                new_grid[row][col]= grid[row][col];
                break;
            case 3:
                new_grid[row][col] = 1;
                break;
            default:
                new_grid[row][col] = 0;
            }
        }
    for(row = 1; row <= maxrow; row ++)
        for(col = 1; col <= maxcol; col++)
            grid[row][col] = new_grid[row][col];
}

int Life::neighbor_count(int row,int col)
{
    int i,j,count =0;
    for(i = row-1;i<= row+1;i++)
        for(j= col-1;j<= col+1;j++)
            count += grid[i][j];
    count -= grid[row][col];
    return count;
}

