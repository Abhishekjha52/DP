//c++ program to find out the number of ways of painting the fence such that at most 2 adjacent posts have the same color.
//Painting Fence Problem
//constraints 1 <= n <= 10^5, 1 <= k <= 10^5
#include<bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;
#define fast_IO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
int add(int a, int b)
{
    return ((a%MOD) + (b%MOD))%MOD;
}
int mul(int a, int b)
{
    return ((a%MOD) * (b%MOD))%MOD;
}
ll solveRec(int n, int k)
{
    //base case
    if(n==1)return k;
    if(n==2)return add(k, mul(k, k-1));
    ll ans=add( mul(solveRec(n-2, k), k-1), mul(solveRec(n-1, k), k-1));
    return ans;
}
ll solveMemo(int n ,int k, vector<ll>&dp)
{
    //base case
    if(n==1)return k;
    if(n==2)return add(k, mul(k, k-1));
    if(dp[n]!=-1)return dp[n];
    dp[n]=add( mul(solveMemo(n-2, k, dp), k-1), mul(solveMemo(n-1, k, dp), k-1));
    return dp[n];
}
ll solveTab(int n, int k)
{
    vector<ll>dp(n+1, -1);
    dp[1]=k;
    dp[2]=mul(k,k);
    for(int i=3;i<=n;i++)
        dp[i]=add( mul(dp[i-2], k-1), mul(dp[i-1], k-1));
    return dp[n];
}
ll solveOpt(int n, int k)
{
    ll prev=k;
    ll curr=mul(k, k);
    if(n==1)return prev;
    if(n==2)return curr;
    for(int i=3;i<=n;i++)
    {
        ll ans=add(mul(prev, k-1), mul(curr, k-1));
        ans%=MOD;
        prev=curr;
        curr=ans;
    }
    return curr;
}
ll countWays(int n, int k)
{
    //ll ans=solveRec(n, k);
    // vector<ll>dp(n+1, -1);
    // ll ans=solveMemo(n, k, dp);
    // ll ans=solveTab(n, k);
    ll ans=solveOpt(n, k);
    return ans;
}
int main()
{
    fast_IO;
    ll noOfPosts, colours;
    cin>>noOfPosts>>colours;
    cout<<countWays(noOfPosts, colours)<<"\n";
}