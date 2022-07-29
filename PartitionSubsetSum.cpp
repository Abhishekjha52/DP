#include<bits/stdc++.h>
using namespace std;
bool solveRec(int index, vector<int>&nums, int n, int target)
{
    //base case
    if(index>=n)return 0;
    if(target<0)return 0;
    if(target==0)return 1;
    
    bool include=solveRec(index+1, nums, n, target-nums[index]);
    bool exclude=solveRec(index+1, nums, n, target-0);
    
    return include or exclude;
}
bool solveMemo(int index, vector<int>&nums, int n, int target, vector<vector<int>>&dp)
{
    //base case
    if(index>=n)return 0;
    if(target<0)return 0;
    if(target==0)return 1;
    if(dp[index][target]!=-1)
        return dp[index][target];
    
    bool include=solveMemo(index+1, nums, n, target-nums[index], dp);
    bool exclude=solveMemo(index+1, nums, n, target-0, dp);
    
    return dp[index][target] = include or exclude;
}
bool solveTab(int n, vector<int>&arr, int total)
{
    vector<vector<int>>dp(n+1, vector<int>(total+1, 0));
    //from analysing base case we need to make target column 1
    for(int i=0;i<=n;i++)
        dp[i][0]=1;
        
    for(int index=n-1;index>=0;index--)
    {
        for(int target=0;target<=total/2;target++)
        {
            bool include=0;
            if(target-arr[index]>=0)
                include=dp[index+1][target-arr[index]];
                
            bool exclude=dp[index+1][target-0];
            dp[index][target]=include or exclude;
        }
    }
    return dp[0][total/2];
}
bool solveOpt(int n, vector<int>&arr, int total)
{
    vector<int>curr(total+1, 0);
    vector<int>next(total+1, 0);
    
    //from analysing base case we need to make target column 1
    curr[0]=1;
    next[0]=1;
    
    for(int index=n-1;index>=0;index--)
    {
        for(int target=0;target<=total/2;target++)
        {
            bool include=0;
            if(target-arr[index]>=0)
                include=next[target-arr[index]];
                
            bool exclude=next[target-0];
            curr[target]=include or exclude;
        }
        next=curr;
    }
    return next[total/2];
}
bool equalPartition(vector<int>& nums) {
    int totalSum=0;
    int n=nums.size();
    for(int i=0;i<n;i++)
        totalSum+=nums[i];
    if(totalSum & 1)return 0;
    int target=totalSum/2;
    vector<vector<int>>dp(n+1, vector<int>(target+1, -1));
    //return solveMemo(0, nums, n, target, dp);
    //return solveRec(0, nums, n, target);
    //return solveTab(n, nums, totalSum);
    return solveOpt(n, nums, totalSum);
    
}
int main()
{
    int n;cin>>n;
    vector<int>v(n);
    for(int i=0;i<n;i++)cin>>v[i];
    if(equalPartition(v))
        cout<<"YES"<<"\n";
    else
        cout<<"NO"<<"\n";
}