//C++ program to count the number of derangements
#include<bits/stdc++.h>
#define fast_IO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MOD 1000000007
using namespace std;
long long solveRec(int n)
{
    //base case
    if(n==1)return 0;
    if(n==2)return 1;
    
    long long ans=( (n-1)%MOD * ( solveRec(n-1)%MOD + solveRec(n-2)%MOD ))%MOD;
    return ans;
}
long long solveMemo(int n, vector<long long>&dp)
{
    //base case
    if(n==1)return 0;
    if(n==2)return 1;
    if(dp[n]!=-1)return dp[n];
    
    dp[n]=( (n-1)%MOD * ( solveMemo(n-1, dp)%MOD + solveMemo(n-2, dp)%MOD ))%MOD;
    return dp[n];
}
long long solveTab(int n)
{
    vector<long long>dp(n+1, 0);
    dp[1]=0;
    dp[2]=1;
    for(int i=3;i<=n;i++)
    {
        dp[i]=((i-1)%MOD * (dp[i-1]%MOD+dp[i-2]%MOD))%MOD;
    }
    return dp[n];
}
long long solveOpt(int n)
{
    long long prev=0;
    long long curr=1;
    if(n==0)
        return 0;
    if(n==1)
        return 1;
    for(int i=3;i<=n;i++)
    {
        long long ans=((i-1)%MOD*(curr%MOD+prev%MOD))%MOD;
        prev=curr;
        curr=ans;
    }
    return curr;
}
long long countDerangements(int n)
{
    long long ans=solveRec(n);
    return ans;
    vector<long long>dp(n+1, -1);
    long long res=solveMemo(n, dp);
    return solveTab(n);
    return solveOpt(n);
}
int main()
{
    int n;cin>>n;
    long long int ans=countDerangements(n);
    cout<<ans<<"\n";
}