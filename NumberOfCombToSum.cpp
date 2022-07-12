//C++ program to find number of combinations to make sum
//Duplicates are allowed
//Coin Change II
#include<bits/stdc++.h>
using namespace std;
int solveRec(vector<int>&nums, int n, int tar)
{
    //base case
    if(tar==0)return 1;
    if(tar<0)return 0;
    

    int ans=0;
    for(int i=0;i<n;i++)
        ans+=solveRec(nums, n, tar-nums[i]);
    return ans;
}
int solveMemo(vector<int>&num, int n, int tar, vector<int>&dp)
{
    //base case
    if(tar<0)return 0;
    if(tar==0)return 1;
    if(dp[tar]!=-1)return dp[tar];
    int ans=0;
    for(int i=0;i<n;i++)
        ans+=solveMemo(num, n, tar-num[i], dp);
    dp[tar]=ans;
    return dp[tar];
}
int solveTab(vector<int>&nums, int tar)
{
    vector<int>dp(tar+1, 0);
    dp[0]=1;
    for(int i=1;i<=tar;i++)
    {
        for(int j=0;j<nums.size();j++)
        {
            if(i-nums[j]>=0)
                dp[i]+=dp[i-nums[j]];
        }
    }
    return dp[tar];
}
int findWays(vector<int> &num, int tar)
{
    int n=num.size();
    //vector<int>dp(tar+1, -1);
    //int ans=solveRec(num, n, tar);
    //int ans=solveMemo(num, n, tar, dp);
    int ans=solveTab(num, tar);
    return ans;
}





//Duplicates are not allowed
int solveRec1(vector<int>&coins, int n, int amount)
{
    if(amount==0)return 1;
    if(n==0)return 0;
    
    if(amount-coins[n-1]>=0)
        return solveRec(coins, n, amount-coins[n-1])+solveRec(coins, n-1, amount);
    
    return solveRec(coins, n-1, amount);
    
}
int solveMemo1(vector<int>&coins, int n, int amount, vector<vector<int>>&dp)
{
    if(amount==0)return 1;
    if(n==0)return 0;
    if(dp[n][amount]!=-1)return dp[n][amount];
    if(amount-coins[n-1]>=0)
        return dp[n][amount]=solveMemo(coins, n-1, amount, dp)+solveMemo(coins, n, amount-coins[n-1], dp);
    return dp[n][amount]=solveMemo(coins, n-1, amount, dp);
}
int solveTab1(vector<int>&coins, int amount)
{
    int n=coins.size();
    vector<vector<int>>dp(n+1, vector<int>(amount+1, 0));
    for(int i=0;i<=n;i++)
        dp[i][0]=1;
    
    for(int j=0;j<=amount;j++)
        dp[0][j]=0;
    
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=amount;j++)
        {
            if(j-coins[i-1]>=0)
                dp[i][j]=dp[i-1][j]+dp[i][j-coins[i-1]];
            else
                dp[i][j]=dp[i-1][j];
        }
    }
    return dp[n][amount];
}

int change(vector<int>& coins, int amount) 
{
    int n=coins.size();
    //vector<vector<int>>dp(n+1,vector<int>(amount+1, -1));
    //int ans=solveRec1(coins, n, amount);
    //int ans=solveMemo1(coins, n, amount, dp);
    int ans=solveTab1(coins, amount);
    return ans;
}

int main()
{
    int n;cin>>n;
    vector<int>v(n);
    for(int i=0;i<n;i++)cin>>v[i];
    int amount;cin>>amount;
    int ans=findWays(v, amount);
    int res=change(v, amount);
    cout<<ans<<"\n";
}
