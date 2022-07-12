//C++ program to find minimum no of squares that sums to no
//For ex:  If N = 100 , N can be expressed as (10*10) and 
//also as (5*5 + 5*5 + 5*5 + 5*5) but the output will be 1 as
//minimum number of square is 1 , i.e (10*10).
#include<bits/stdc++.h>
using namespace std;
int solveRec(int n)
{
    //base case
    if(n==0)return 0;
    int ans=n;
    for(int i=1;i*i<=n;i++)
        ans=min(ans, 1+solveRec(n-(i*i)));
    return ans;
}
int solveMemo(int n, vector<int>&dp)
{
    //base case
    if(n==0)return 0;
    if(dp[n]!=-1)return dp[n];
    int ans=n;
    for(int i=1;i*i<=n;i++)
        ans=min(ans, 1+solveMemo(n-(i*i), dp));
    dp[n]=ans;
    return dp[n];
}
int MinSquares(int n)
{
    //int ans=solveRec(n);
    vector<int>dp(n+1, -1);
    int ans=solveMemo(n, dp);
    return ans;
}
int main()
{
    int n;cin>>n;
    int ans=MinSquares(n);
    cout<<ans<<"\n";
}