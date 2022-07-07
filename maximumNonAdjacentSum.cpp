//c++ program to find the maximum sum of non adjacent elements
//House Robber Problem
#include<bits/stdc++.h>
using namespace std;
int solveRec(vector<int>&nums, int n)
{
    //base case
    if(n<0)
        return 0;

    if(n==0)//if we are at the first index then maximum element is first element
        return nums[0];

    int include=solveRec(nums, n-2)+nums[n];
    int exclude=solveRec(nums, n-1);

    return max(include, exclude);
}

int solveMemo(vector<int>&nums, int n, vector<int>&dp)
{
    //base case
    if(n<0)
        return 0;

    if(n==0)//if we are at the first index then maximum element is first element
        return nums[0];

    if(dp[n]!=-1)
        return dp[n];

    int include=solveRec(nums, n-2)+nums[n];
    int exclude=solveRec(nums, n-1)+0;

    dp[n]=max(include,exclude);

    return dp[n];
}
int solveTab(vector<int>&nums, int n)
{
    vector<int>dp(n, 0);
    dp[0]=nums[0];
    for(int i=1;i<=n;i++)
    {
        int include=dp[i-2]+nums[i];
        int exclude=dp[i-1]+0;
        dp[i]=max(include, exclude);
    }
    return dp[n-1];
}

int solveSpaceOpt(vector<int>&nums, int n)
{
    int prev2=0;
    int prev1=nums[0];
    for(int i=1;i<n;i++)
    {
        int include=prev2+nums[i];
        int exclude=prev1+0;

        int ans=max(include, exclude);
        prev2=prev1;
        prev1=ans;
    }
    return prev1;
}
int maximumNonAdjacentSum(vector<int>&nums, int n)
{
    // int ans=solveRec(nums, n-1);
    // return ans;

    // vector<int>dp(n+1,-1);
    // int res=solveMemo(nums, n-1, dp);
    // return res;

    // int n=nums.size();
    // return solveTab(nums,n);

    return solveSpaceOpt(nums, n);
}
int main()
{
    int n;cin>>n;
    vector<int>v(n);
    for(int i=0;i<n;i++)cin>>v[i];
    int ans=maximumNonAdjacentSum(v,n);
    cout<<ans<<"\n";
}
