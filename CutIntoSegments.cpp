//c++ program to find maximum number of segments you can make of this rod provided that each segment should be of the length 'X', 'Y', or 'Z'.
#include<bits/stdc++.h>
using namespace std;
int solveRec(int n, int x, int y, int z)
{
    //base case
    if(n==0)
        return 0;
    if(n<0)
        return INT_MIN;
        
    int ans1=solveRec(n-x, x, y, z)+1;
    int ans2=solveRec(n-y, x, y, z)+1;
    int ans3=solveRec(n-z, x, y, z)+1;
    return max({ans1, ans2, ans3});
}
int solveMemo(int n, int x, int y, int z, vector<int>&dp)
{
    //base case
    if(n==0)
        return 0;
    if(n<0)
        return INT_MIN;
    if(dp[n]!=-1)
        return dp[n];
        
    int ans1=solveMemo(n-x, x, y, z, dp)+1;
    int ans2=solveMemo(n-y, x, y, z, dp)+1;
    int ans3=solveMemo(n-z, x, y, z, dp)+1;
    
    dp[n]= max({ans1, ans2, ans3});
    return dp[n];
}
int main()
{
    int n, x, y, z;
    //n- length of the rod
    //x, y, z- are the segments into which a given rod can be cut into. 
    cin>>n>>x>>y>>z;
    // int ans1=solveRec(n, x, y, z);
    // cout<<ans1<<" ";
    vector<int>dp(n+1, -1);
    int res=solveMemo(n, x, y, z, dp);
    if(res<0)
        cout<<"0"<<"\n";
    else
        cout<<res<<"\n";
} 