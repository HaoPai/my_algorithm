#include <iostream>
#include <fstream>
#define N 5
using namespace std;

int main()
{
    int num[N];
    ofstream outfile;
    outfile.open("numbers.txt",ios::out);
    cout << "please input "<< N << " numbers." << endl;
    for(int i = 0; i < N; i++){
        cin >> num[i];
        outfile << num[i] << " ";
    }
    outfile << "\r\n";
    outfile.close();
    return 0;
} 
