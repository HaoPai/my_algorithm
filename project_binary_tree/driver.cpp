#include <iostream>
#include "utility_test.h"
#include "dictionary.h"
using namespace std;
int main()
{
    Dictionary dictionary;
    Shell<Dictionary> run(dictionary);
    run.add_command("traversal",&Dictionary::traversal);
    run.add_command("insert",&Dictionary::insert);
    run.add_command("search",&Dictionary::search);
    run.main();
    return 0;
}
