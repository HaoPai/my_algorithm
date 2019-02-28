#include "utility.h"
#include "life.h"
void instructions();
int main()
{
    Life configuration;
    instructions();
    configuration.initialize();
    configuration.print();
    cout << "Continue viewing new generations ?"<<endl;
    while(user_says_yes()){
        configuration.update();
        configuration.print();
        cout << "Continue viewing new generations ?"<<endl;
    }
    return 0;
}

void instructions()
{
    cout << "Welcome to Conway's game of life."<<endl;
    cout << "This game uses a grid of size "
         << endl;
    cout << "each cell can either be occupied by an organism or not."<<endl;
    cout << " The occupied cells change from generation to genration"<<endl;
    cout << "according to the number of neighboring cells which are alive." << endl;
}
