#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

int M,N;
vector<int> fav;
bool canPlace(int mid)
{
    vector<int> row_seats(M,0);
    int row;
    for (int i=0; i<mid;i++)
    {
        row = fav[i];
        if (row_seats[row]<N)
        {
            row_seats[row]++;
        }
        
        else
        {
            row=(row+1)%M;
            if (row_seats[row]<N)
            {
                row_seats[row]++;
            }
            else
            {
                return false;
            }
        }    
    }
    for( auto c: row_seats)
    {
        
    }  
    return true;
}

int MaxStudents(int right)
{
    int left=0;
    int mid;
    int ans=0;
    while (left<=right)
    {
        mid=(left+right)/2;
        if(canPlace(mid))
        {
            ans=mid;
            left=mid+1;
            
            
        }
        else
        {
            right=mid-1;
        }
        
    }
    
    return ans;
    
}

int main()
{
    int X;
    cin>>X>>M>>N;
    fav.resize(X);
    srand(time(NULL));
    cout<<"Favorite places: "<<endl;
    for (int i=0; i<X; i++)
    {
        int num=rand()%M;
        fav[i]=num;
        cout<<num<<" ";
    }
    cout<<endl;
    cout<<X-MaxStudents(X);
}