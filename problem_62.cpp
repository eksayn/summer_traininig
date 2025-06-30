#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    int uniquePaths(int m, int n) {
        
    vector <int> AboveRow(n,1);

    for (int row=1; row<m; row++)
    {
        vector <int> CurrentRow(n,1);
        for (int col=1; col<n; col++)
        {
            CurrentRow[col]=AboveRow[col]+CurrentRow[col-1];
        }
        AboveRow=CurrentRow;
    }
    return AboveRow[n-1];

    }
};
int main()
{
    
}