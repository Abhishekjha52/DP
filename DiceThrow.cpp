#include<bits/stdc++.h>
using namespace std;
long long solveRec(int dice, int faces, int target)
{
    //base case
    if(target<0)return 0;
    if(dice==0 && target!=0)return 0;
    if(target==0 && dice!=0)return 0;
    if(dice==0 && target==0)return 1;
    
    long long ans=0;
    for(int i=1;i<=faces;i++)
    {
        ans=ans+solveRec(dice-1, faces, target-i);
    }
    return ans;

}

long long solveMemo(int dice, int faces, int target, vector<vector<long long>>&dp)
{
    //base case
    if(target<0)return 0;
    if(dice==0 && target!=0)return 0;
    if(target==0 && dice!=0)return 0;
    if(dice==0 && target==0)return 1;
    
    if(dp[dice][target]!=-1)
        return dp[dice][target];
    
    long long ans=0;
    for(int i=1;i<=faces;i++)
    {
        ans=ans+solveMemo(dice-1, faces, target-i, dp);
    }
    return dp[dice][target]=ans;

}

long long solveTab(int d, int f, int t)
{
    vector<vector<long long>>dp(d+1, vector<long long>(t+1, 0));
    //covering one base case which gives value 1, remaining covers in declaration
    dp[0][0]=1;
    
    for(int dice=1;dice<=d;dice++)
    {
        for(int target=1;target<=t;target++)
        {
            long long ans=0;
            for(int i=1;i<=f;i++)
            {
                if(target-i>=0)//to handle integer overflow
                    ans=ans+dp[dice-1][target-i];
            }
            dp[dice][target]=ans;
        }
    }
    return dp[d][t];
    
}

long long solveOpt(int d, int f, int t)
{
    //since answer is depending on prev row we require only two 1D array instead of 2D array
    vector<long long>prev(t+1, 0);
    vector<long long>curr(t+1, 0);
    
    //covering one base case which gives value 1, remaining covers in declaration
    prev[0]=1;
    
    for(int dice=1;dice<=d;dice++)
    {
        for(int target=1;target<=t;target++)
        {
            long long ans=0;
            for(int i=1;i<=f;i++)
            {
                if(target-i>=0)//to handle integer overflow
                    ans=ans+prev[target-i];
            }
            curr[target]=ans;
        }
        prev=curr;//after every iteration prev becomes curr
    }
    return prev[t];
    
}

long long noOfWays(int N , int M , int X) {
    //return solveRec(N, M, X);
    vector<vector<long long>>dp(N+1, vector<long long>(X+1, -1));
    return solveMemo(N, M, X, dp);
}
int main()
{
    //n-dices, m-faces, x-targetSum
    int n, m, x;cin>>n>>m>>x;
    long long ans=noOfWays(n, m, x);
    cout<<ans<<"\n"l

}