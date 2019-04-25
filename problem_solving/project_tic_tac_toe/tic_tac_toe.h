#ifndef _TIC_TAC_TOE_H_
#define _TIC_TAC_TOE_H_

#include <stack>
using namespace std;

class Move{
public:
    Move();
    Move(int r,int c);
    int row;
    int col;
};

Move::Move()
{
    row = col = 3;
}

Move :: Move(int r,int c)
{
    row = r;
    col = c;
}

class Board {
public:
    Board();
    bool done()const;
    void print() const;
    bool better(int value,int old_value) const;
    void play(Move try_it);
    int worst_case() const;
    int evaluate() const;
    int legal_moves(stack<Move> &moves) const;
private:
    int square[3][3];
    int moves_done;
    int winner() const;
};

Board :: Board()
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            square[i][j] = 0;
    moves_done = 0;
}

void Board :: play(Move try_it)
{
    square[try_it.row][try_it.col] = moves_done %2 +1;
    moves_done ++;
}



int Board :: winner() const
{
    for(int i=0;i<3;i++)
        if(square[i][0]&&square[i][0]==square[i][1]&&square[i][1]==square[i][2])
            return square[i][0];
    for(int i=0; i<3; i++)
        if(square[0][i]&&square[0][i]==square[1][i]&&square[1][i]==square[2][i])
            return square[0][i];
    if(square[0][0]&&square[0][0]==square[1][1]&&square[1][1]==square[2][2])
        return square[0][0];
    if(square[0][2]&&square[0][2]==square[1][1]&&square[1][1]==square[2][0])
        return square[0][2];
    return 0;
}

bool Board :: done()const
{
    return  winner()> 0 || moves_done == 9;
}

void Board :: print() const
{
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            cout << square[i][j] << " ";
        cout << endl;
    }
}

bool Board :: better(int value, int old_value) const
{
    if(moves_done%2 ==0)
        return value > old_value;
    else return value < old_value;
}

int Board ::worst_case()const
{
    if(moves_done%2==0) return -10;
    else return 10;
}

int Board :: evaluate() const
{
    int the_winner = winner();
    if(the_winner ==1) return 10 - moves_done;
    else if(the_winner == 2) return moves_done -10;
    else return 0;
}

int Board :: legal_moves(stack<Move> &s) const
{
    int count = 0;
    while(s.size()>0) s.pop();
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(square[i][j] == 0){
                Move m(i,j);
                s.push(m);
                count ++;
            }
    return count;
}


#endif