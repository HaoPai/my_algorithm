#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "five_in_a_row.h"
#define BUFFER_SIZE 1000

using namespace std;

int look_ahead(const Board &game,int depth, Move &recommended);
void get_user_move(int &row, int &col, char buffer[]);


int main()
{
    Board game;
    stack<Move> moves;
    const char *myfifo = "/tmp/gobang";
    mkfifo(myfifo,0666);
    char input[BUFFER_SIZE];
    while(!game.done()){
        int fd = open(myfifo,O_RDONLY);
        int n = read(fd,input,BUFFER_SIZE);
        input[n] = '\0';
        int row = -1,col = -1;
        get_user_move(row,col,input);
        Move user_move(row,col);
        if(!game.play(user_move)){
            close(fd);
            continue;
        }
        Move reply;
        look_ahead(game,2,reply);
        game.play(reply);
        game.json();
        close(fd);
    }
    return 0;
}

int look_ahead(const Board &game,int depth, Move &recommended)
{
    if(game.done()||depth == 0){
        //cout << game.evaluate() << endl;
        return game.get_score_one() - game.get_score_two();
    }
    else {
        stack<Move> moves;
        game.legal_moves(moves);
        int value, best_value = game.worst_case();
        while(moves.size()>0){
            Move try_it,reply;
            try_it = moves.top();
            Board new_game = game;
            new_game.play(try_it);
            value = look_ahead(new_game,depth-1,reply);
            if(game.better(value,best_value)){
                best_value = value;
                recommended = try_it;
            }
            moves.pop();
        }
        return best_value;
    }
}

void get_user_move(int &row, int &col, char buffer[])
{
    stringstream ss;
    ss << buffer;
    ss >> row >>col;
}