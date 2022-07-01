//c++ program to find the minimum cost to climb the stairs
#include<bits/stdc++.h>
using namespace std;
int minCostClimbingStairs(vector<int>&cost, int n)
{
    //recursive approach

    //base case
    if(n==0)
        return cost[0];
    if(n==1)
        return cost[1];

    return cost[n]+min(minCostClimbingStairs(cost, n-1), minCostClimbingStairs(cost, n-2));
}

int minCostClimbingStairsMemo(vector<int>&cost, int n, vector<int>&dp)
{
    //recursive +memoisation approach

    //base case
    if(n==0)
        return cost[0];
    if(n==1)
        return cost[1];
    if(dp[n]!=-1)
        return dp[n];

    dp[n]=cost[n]+min(minCostClimbingStairsMemo(cost, n-1, dp), minCostClimbingStairsMemo(cost, n-2, dp));
    return dp[n];
}

int minCostClimbingStairsTab(vector<int>&cost, int n)
{
    //tabulation approach

    vector<int>dp(n+1);
    dp[0]=cost[0];
    dp[1]=cost[1];
    for(int i=2;i<n;i++)
        dp[i]=min(dp[i-1], dp[i-2])+cost[i];
    return min(dp[n-1], dp[n-2]);
}

int minCostClimbingStairsSO(vector<int>&cost, int n)
{
    //space optimization approach

    int a=cost[0], b=cost[1];
    for(int i=2;i<n;i++)
    {
        int c=min(a,b)+cost[i];
        a=b;
        b=c;
    }
    return min(a,b);
}


int main()
{
    int n;cin>>n;
    vector<int>arr(n);
    for(int i=0;i<n;i++)
        cin>>arr[i];
    vector<int>dp(n+1, -1);
    int ans=min(minCostClimbingStairs(arr, n-1), minCostClimbingStairs(arr, n-2));
    int ans1=min(minCostClimbingStairsMemo(arr, n-1, dp), minCostClimbingStairsMemo(arr, n-2, dp));
    int ans2=minCostClimbingStairsTab(arr, n);
    int ans3=minCostClimbingStairsSO(arr, n);
    cout<<ans<<" "<<ans1<<" "<<ans2<<" "<<ans3<<"\n";
    
}