//Leetcode Hard-https://leetcode.com/problems/maximum-height-by-stacking-cuboids/
//Appraoch here it is similar to LIS
//sort all the cuboids based on height because we can't say that particular element is height or width or height
//that is we can rotate the cuboid to place one on another so we sort based on heights to get maximum height
//then we sort the cuboids in ascending order
//then apply LIS to the cuboid with condition given in question
#include<bits/stdc++.h>
using namespace std;
bool check(vector<int>base, vector<int>newBox)
{
    if(newBox[0]<=base[0] && newBox[1]<=base[1] && newBox[2]<=base[2])
        return true;
    else    
        return false;
}
int LIS(vector<vector<int>>&a, int n)
{
    vector<int>currRow(n+1, 0);
    vector<int>nextRow(n+1, 0);

    for(int curr=n-1;curr>=0;curr--)
    {
        for(int prev=curr-1;prev>=-1;prev--)
        {
            int take=0;
            if(prev==-1 || check(a[curr], a[prev]))
                take=a[curr][2]+nextRow[curr+1];

            int notTake=0+nextRow[prev+1];
            currRow[prev+1]=max(take, notTake);
        }
        nextRow=currRow;
    }
    return nextRow[0];
}
int maxHeights(vector<vector<int>>&cuboids)
{
    //step 1:sort the cuboids based on heights
    for(auto &a:cuboids)
        sort(a.begin(), a.end());

    //step 2: sort all the cuboids
    sort(cuboids.begin(), cuboids.end());

    //step 3:Use LIS
    return LIS(cuboids, cuboids.size());

}
int main()
{
    int r,c;cin>>r>>c;
    vector<vector<int>>v(r, vector<int>(c));
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
            cin>>v[i][j];
    }
    int ans=maxHeights(v);
    cout<<ans<<"\n";
}