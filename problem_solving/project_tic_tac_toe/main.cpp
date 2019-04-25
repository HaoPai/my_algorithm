#include <iostream>
#include "tic_tac_toe.h"

using namespace std;

int look_ahead(const Board &game,int depth, Move &recommended);

int main()
{
    Board board;
    stack<Move> moves;
    Move m;
    m.row = 0;
    m.col = 0;
    board.play(m);
    m.row = 1;
    m.col = 0;
    board.play(m);
    m.row = 2;
    m.col = 1;
    board.play(m);
    m.row = 1;
    m.col = 1;
    board.play(m);
    board.legal_moves(moves);
    cout << moves.size() << endl;
    while(moves.size()>0){
        Move m = moves.top(),reply;
        Board new_game = board;
        new_game.play(m);
        int value = look_ahead(new_game,9,reply);
        cout << "x: " << m.row << " y: " << m.col << endl;
        cout << "value is : " << value << endl;;
        moves.pop();
    }
    cout << endl;
    board.print();
	return 0;
}

int look_ahead(const Board &game,int depth, Move &recommended)
{
    if(game.done()||depth == 0){
        //cout << game.evaluate() << endl;
        return game.evaluate();
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