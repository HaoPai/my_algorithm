#include <iostream>
#include "utility.h"
#include "alphabetic.h"
using namespace std;
int main()
{
    Alphabetic  alpha;
    Shell<Alphabetic> run(alpha);
    run.add_command("insert",&Alphabetic::insert);
    run.add_command("search",&Alphabetic::search);
    run.add_command("traversal",&Alphabetic::traversal);
    run.add_command("remove",&Alphabetic::remove);
    run.main();
    return 0;
}
