#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        int size = dimensions.size();
        int length, width;
        int max=0;
        int max_length, max_width;
        int res, square,square1,square2;
        for (int i=0; i<size; i++)
        {
            length = dimensions[i][0];
            width = dimensions[i][1];
            res=pow(length,2)+pow(width,2);
            if (res>max)
            {
                max=res;
                max_length = length;
                max_width = width;
            }
            else if (res==max)
            {
                square1=length*width;
                square2 =max_length*max_width;
                if (square1>square2)
                {
                    max_length = length;
                    max_width = width;
                }
            }
        }
        square = max_length*max_width;
        return square;
    }
};


int main()
{
    
}