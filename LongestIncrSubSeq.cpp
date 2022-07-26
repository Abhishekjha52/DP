#include<bits/stdc++.h>
using namespace std;
int solveRec(vector<int>&a, int n, int curr, int prev)
{
    //base case
    if(curr==n)return 0;
    
    //we either take that element or not take
    
    int take=0;
    if(prev==-1 || a[curr]>a[prev])
        take=1+solveRec(a, n, curr+1, curr);
        
    int notTake=0+solveRec(a, n, curr+1, prev);
    
    return max(take, notTake);
}
int solveMemo(vector<int>&a, int n, int curr, int prev, vector<vector<int>>&dp)
{
    //base case
    if(curr==n)return 0;
    if(dp[curr][prev+1]!=-1)return dp[curr][prev+1];
    
    //we either take that element or not take
    
    int take=0;
    if(prev==-1 || a[curr]>a[prev])
        take=1+solveMemo(a, n, curr+1, curr, dp);
        
    int notTake=0+solveMemo(a, n, curr+1, prev, dp);
    
    return dp[curr][prev+1]= max(take, notTake);
}
int solveTab(vector<int>&a, int n)
{
    vector<vector<int>>dp(n+1, vector<int>(n+1, 0));
    for(int curr=n-1;curr>=0;curr--)
    {
        for(int prev=curr-1;prev>=-1;prev--)
        {
            int take=0;
            if(prev==-1 || a[curr]>a[prev])
                take=1+dp[curr+1][curr+1];
                
            int notTake=0+dp[curr+1][prev+1];
            
            dp[curr][prev+1]= max(take, notTake);
        }
    }
    return dp[0][0];
}
int solveOpt(vector<int>&a, int n)
{
    vector<int>currRow(n+1, 0);
    vector<int>nextRow(n+1, 0);
    for(int curr=n-1;curr>=0;curr--)
    {
        for(int prev=curr-1;prev>=-1;prev--)
        {
            int take=0;
            if(prev==-1 || a[curr]>a[prev])
                take=1+nextRow[curr+1];

            int notTake=0+nextRow[prev+1];

            currRow[prev+1]= max(take, notTake);
        }
        nextRow=currRow;
    }
    return nextRow[0];
}
int lengthOfLIS(vector<int>& nums) {
    int n=nums.size();
    //return solveRec(nums, n, 0, -1);
    //vector<vector<int>>dp(n, vector<int>(n+1, -1));
    //return solveMemo(nums, n, 0, -1, dp);
    //return solveTab(nums, n);
    return solveOpt(nums, n);
}
int main()
{
    int n;cin>>n;
    vector<int>v(n);
    for(int i=0;i<n;i++)cin>>v[i];
    int ans=lengthOfLIS(v);
    cout<<ans<<"\n";
}
