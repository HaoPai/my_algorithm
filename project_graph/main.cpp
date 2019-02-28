#include "utility.h"
#include "network.h"

#include <iostream>

int main()
{
    Graph g;
    Shell<Graph> run(g);
    run.main();
    return 0;

}