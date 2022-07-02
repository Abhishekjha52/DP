//c++ program to find the minimum no of coins to reach the target sum
#include<bits/stdc++.h>
using namespace std;
int solveRec(vector<int>&coins, int n, int sum)
{
    //base case
    if(sum==0)
        return 0;
    
    if(sum<0)
        return INT_MAX;

    int mini=INT_MAX;
    for(int i=0;i<n;i++)
    {
        int ans=solveRec(coins, n, sum-coins[i]);
        if(ans!=INT_MAX)
            mini=min(mini, 1+ans);
    }
    return mini;
    
}


int solveMemo(vector<int>&coins, int n, int sum, vector<int>&dp)
{
    //base case
    if(sum==0)
        return 0;
    if(sum<0)
        return 0;

    if(dp[n]!=-1)
        return dp[n];

    int mini=INT_MAX;
    for(int i=0;i<n;i++)
    {
        int ans=solveRec(coins, n, sum-coins[i]);
        if(ans!=INT_MAX)
            mini=min(mini, 1+ans);
    }

    dp[n]=mini;

    return dp[n];
}

int solveTab(vector<int>&coins, int n, int sum)
{
    vector<int>dp(n+1, INT_MAX);
    dp[0]=0;
    for(int i=1;i<=sum;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i-coins[j]>=0 && dp[i-coins[j]]!=INT_MAX)
                dp[j]=min(dp[j], 1+dp[i-coins[j]]);
        }
    }

    if(dp[n]!=INT_MAX)
        return -1;
    return dp[n];
}
int minCoins(vector<int>&a, int n, int sum)
{
    // int ans=solveRec(a, n, sum);
    // if(ans==INT_MAX)
    //     return -1;
    // return ans;

    vector<int>dp(n+1, -1);
    int ans=solveMemo(a, n, sum, dp);
    int res=solveTab(a, n, sum);

    if(ans==INT_MAX)
        return -1;
    else
        return ans;
}
int main()
{
    int n;cin>>n;
    vector<int>v(n);
    for(int i=0;i<n;i++)cin>>v[i];
    int sum;cin>>sum;
    int ans=minCoins(v, n, sum);
    int ans1=minCoins(v, n, sum);
    int ans2=minCoins(v, n, sum);
    int ans3=minCoins(v, n, sum);
    cout<<ans<<" "<<ans1<<" "<<ans2<<" "<<ans3<<"\n";
}