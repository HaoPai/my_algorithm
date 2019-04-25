#include <stack>
#include <fstream>

#define BOARD_SIZE 15 

#define V_1 1
#define V_2 10
#define V_3 100
#define V_4 1000
#define V_5 10000

using namespace std;



class Move{
public:
    Move();
    Move(int r,int c);
    int row;
    int col;
};

Move :: Move()
{
    row = col = 15;
}

Move :: Move(int r,int c)
{
    row = r;
    col = c;
}


class Board{
public:
    Board();
    void print() const;
    void json() const;
    bool done() const;
    bool play(Move try_it);
    bool better(int value,int old_value) const;
    int evaluate();
    int get_score_one()const;
    int get_score_two()const;
    int worst_case() const;
    int legal_moves(stack<Move> &moves) const;
    void score_row(int row, int &score_1, int &score_2) const;
    void score_col(int col, int &score_1, int &score_2) const;
    void score_up(int n, int &score_1, int &score_2) const;
    void score_down(int n, int &score_1,int &score_2) const;
private:
    int square[BOARD_SIZE][BOARD_SIZE];
    int moves_done;
    int score_one;
    int score_two;
    int winner() const;
    
    
    int score(int n) const;
};


Board :: Board()
{
    for(int i=0;i<BOARD_SIZE ; i++)
        for(int j=0 ; j<BOARD_SIZE ;j++)
            square[i][j] = 0;
    moves_done = 0;
    score_one = score_two = 0;
}

void Board :: print() const
{
    for(int i=0;i<BOARD_SIZE ; i++){
        for(int j=0 ; j<BOARD_SIZE ;j++)
            cout << square[i][j] << " ";
        cout << endl;
    }
}

void Board :: json() const
{
    ofstream f("gobang_board.txt");
    f << "[" << square[0][0];
    for(int i=1; i< 225; i++){
        f << "," << square[i/15][i%15];
    }
    f << "]";
    f.close();
}

bool Board :: done() const
{
    return winner()>0 || moves_done == 225;
}

bool Board :: play(Move m)
{
    if(m.row < 0 || m.row > BOARD_SIZE -1 || m.col < 0 || m.col > BOARD_SIZE -1 || square[m.row][m.col] > 0) return false;
    else square[m.row][m.col] = moves_done%2 +1;
    moves_done ++;
    evaluate();
    return true;
}

bool Board :: better(int value, int old_value) const
{
    if(moves_done%2==0) return value > old_value;
    else return value < old_value;
}


int Board :: worst_case() const
{
    if(moves_done%2 == 0) return -10000;
    else return 10000;
}

int Board :: legal_moves(stack<Move> &moves) const
{
    int count = 0;
    while(moves.size()>0)
        moves.pop();
    for(int i=0;i<BOARD_SIZE; i++)
        for(int j=0; j<BOARD_SIZE; j++)
            if(square[i][j] == 0){
                Move m(i,j);
                moves.push(m);
                count ++;
            }
    return count;
}


int Board :: winner() const
{
    if(score_one - score_two >5000) return 1;
    if(score_one - score_two <-5000) return 2;
    else return 0;
}

int Board :: evaluate()
{
    int score_1=0,score_2=0,temp_1=0,temp_2=0;
    for(int i=0; i<BOARD_SIZE; i++){
        score_row(i,temp_1,temp_2);
        score_1 += temp_1;
        score_2 += temp_2;
        temp_1 = temp_2 = 0;
    }

    for(int i=0; i<BOARD_SIZE; i++){
        score_col(i,temp_1,temp_2);
        score_1 += temp_1;
        score_2 += temp_2;
        temp_1 = temp_2 = 0;
    }

    for(int i=4; i<2*BOARD_SIZE-5; i++){
        score_up(i,temp_1,temp_2);
        score_1 += temp_1;
        score_2 += temp_2;
        temp_1 = temp_2 = 0;
    }

    for(int i=4; i<2*BOARD_SIZE-5; i++){
        score_down(i,temp_1,temp_2);
        score_1 += temp_1;
        score_2 += temp_2;
        temp_1 = temp_2 = 0;
    }
    //cout << "score_1 : " << score_1 << endl;
    //cout << "score_2 : " << score_2 <<endl;
    score_one = score_1;
    score_two = score_2;
    return score_1 - score_2 ;
}

int Board :: get_score_one() const
{
    return score_one;
}

int Board :: get_score_two() const
{
    return score_two;
}


int Board :: score(int n)const
{
    switch(n){
        case 1:
            return V_1;
            break;
        case 2:
            return V_2;
            break;
        case 3:
            return V_3;
            break;
        case 4:
            return V_4;
            break;
        case 5:
            return V_5;
            break;
    }
}



void Board :: score_row(int row, int &score_1, int &score_2)const
{
    int count_1 = 0,count_2 = 0,count_3 = 0;
    int mover = 0;
    int scores[3] = {0};
    for(int i=0;i<BOARD_SIZE; i++){
        if(square[row][i] == 0) count_2 ++;
        else if(i==0||square[row][i-1]==0){
            if(mover>0&&count_1+count_2+count_3>=5){
                scores[mover] += score(count_3);
            }
            count_1 = count_2;
            count_2 = 0;
            count_3 = 1;
            mover = square[row][i];
        }else if(square[row][i-1]!=square[row][i]){
            if(count_1+count_3>=5){
                scores[mover] += score(count_3);
            }
            count_1 = count_2 = 0;
            count_3 = 1;
            mover = square[row][i];
        }else count_3 ++;
    }
    if(mover>0&&count_1+count_2+count_3>=5) 
        scores[mover] += score(count_3);
    score_1 = scores[1];
    score_2 = scores[2];
}

void Board :: score_col(int col, int &score_1, int &score_2)const
{
    int count_1 = 0,count_2 = 0,count_3 = 0;
    int mover = 0;
    int scores[3] = {0};
    for(int i=0;i<BOARD_SIZE; i++){
        if(square[i][col] == 0) count_2 ++;
        else if(i==0||square[i-1][col]==0){
            if(mover>0&&count_1+count_2+count_3>=5){
                scores[mover] += score(count_3);
            }
            count_1 = count_2;
            count_2 = 0;
            count_3 = 1;
            mover = square[i][col];
        }else if(square[i-1][col]!=square[i][col]){
            if(count_1+count_3>=5){
                scores[mover] += score(count_3);
            }
            count_1 = count_2 = 0;
            count_3 = 1;
            mover = square[i][col];
        }else count_3 ++;
    }
    if(mover>0&&count_1+count_2+count_3>=5) 
        scores[mover] += score(count_3);
    score_1 = scores[1];
    score_2 = scores[2];
}

void Board :: score_up(int n, int &score_1, int &score_2)const
{
    int count_1 = 0,count_2 = 0,count_3 = 0;
    int mover = 0;
    int scores[3] = {0};

    int start_row = (n < BOARD_SIZE)?  n : BOARD_SIZE -1;
    int start_col = (n < BOARD_SIZE)? 0 : n - BOARD_SIZE +1;

    for(int i = start_row,j = start_col;i>=0&&j<BOARD_SIZE; i--,j++){
        if(square[i][j] == 0) count_2 ++;
        else if((i==start_row&&j==start_col)||square[i+1][j-1]==0){
            if(mover>0&&count_1+count_2+count_3>=5){
                scores[mover] += score(count_3);
            }
            count_1 = count_2;
            count_2 = 0;
            count_3 = 1;
            mover = square[i][j];
        }else if(square[i][j]!=square[i+1][j-1]){
            if(count_1+count_3>=5){
                scores[mover] += score(count_3);
            }
            count_1 = count_2 = 0;
            count_3 = 1;
            mover = square[i][j];
        }else count_3 ++;
    }
    if(mover>0&&count_1+count_2+count_3>=5) 
        scores[mover] += score(count_3);
    score_1 = scores[1];
    score_2 = scores[2];
}

void Board :: score_down(int n, int &score_1, int &score_2)const
{
    int count_1 = 0,count_2 = 0,count_3 = 0;
    int mover = 0;
    int scores[3] = {0};

    int start_row = (n < BOARD_SIZE)? BOARD_SIZE -1 -n : 0;
    int start_col = (n < BOARD_SIZE)? 0 : n - BOARD_SIZE  + 1;

    for(int i = start_row,j = start_col;i<BOARD_SIZE&&j<BOARD_SIZE; i++,j++){
        if(square[i][j] == 0) count_2 ++;
        else if((i==start_row&&j==start_col)||square[i-1][j-1]==0){
            if(mover>0&&count_1+count_2+count_3>=5){
                scores[mover] += score(count_3);
            }
            count_1 = count_2;
            count_2 = 0;
            count_3 = 1;
            mover = square[i][j];
        }else if(square[i][j]!=square[i-1][j-1]){
            if(count_1+count_3>=5){
                scores[mover] += score(count_3);
            }
            count_1 = count_2 = 0;
            count_3 = 1;
            mover = square[i][j];
        }else count_3 ++;
    }
    if(mover>0&&count_1+count_2+count_3>=5) 
        scores[mover] += score(count_3);
    score_1 = scores[1];
    score_2 = scores[2];
}

