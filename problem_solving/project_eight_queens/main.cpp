#include <iostream>
#include <vector>
#include "queens.h"

using namespace std;

void solve_from(Queens &configuration,vector<vector<int>> &result);
int main()
{
    Queens configuration;
    vector<vector<int>> result;
    solve_from(configuration,result);
    //cout << "发现解：" << result.size() << endl;
    int n = result.size();
    cout << "[";
    cout << "[";
    cout << result[0][0];
        for(int j=1;j<QUEEN_SIZE;j++)
            cout << "," << result[0][j];
    cout << "]";
    for(int i=1;i<n;i++){
        cout << ",[";
        cout << result[i][0];
        for(int j=1;j<QUEEN_SIZE;j++)
            cout << "," << result[i][j];
        cout << "]";
    }
    cout << "]";
}

void solve_from(Queens &configuration,vector<vector<int>> &result)
{
    if(configuration.is_solved()){
        vector<int> v;
        configuration.get_location(v);
        result.push_back(v);
    }else for(int col=1;col<=QUEEN_SIZE;col++) if(configuration.unguarded(col)){
        configuration.insert(col);
        solve_from(configuration,result);
        configuration.remove(col);
    }
}