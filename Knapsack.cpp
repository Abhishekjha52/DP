//C++ program to solve O/1 Knapsaack problem
#include<bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;
#define fast_IO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
int solveRec(vector<int>&weight, vector<int>values, int index, int capacity)
{
    //base case
    //if only one item to steal then just compare its weight with bag capacity
    if(index==0)
    {
        if(weight[0]<=capacity)
            return values[0];
        else    
            return 0;
    }
    int include=0;
    if(capacity>=weight[index])
        include=values[index] + solveRec(weight, values, index-1, capacity-weight[index]);
    
    int exclude=solveRec(weight, values, index-1, capacity);

    int ans=max(include, exclude);
    return ans;
}


int solveMemo(vector<int>&weight, vector<int>value, int index, int capacity, vector<vector<int>>&dp)
{
    //base case
    //if only one item to steal then just compare its weight with bag capacity
    if(index==0)
    {
        if(weight[0]<=capacity)
            return value[0];
        else    
            return 0;
    }
    if(dp[index][capacity]!=-1)
        return dp[index][capacity];
    int include=0;
    if(capacity>=weight[index])
        include=value[index] + solveMemo(weight, value, index-1, capacity-weight[index], dp);
    
    int exclude=solveMemo(weight, value, index-1, capacity, dp);

    dp[index][capacity]=max(include, exclude);
    return dp[index][capacity];
}


int solveTab(vector<int>weight, vector<int>&value, int n, int capacity)
{
    vector<vector<int>>dp(n+1, vector<int>(capacity+1, 0));
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=capacity;j++)
        {
            if(i==0 || j==0)
                dp[i][j]=0;
        }
    }
    for(int i=1;i<(n+1);i++)
    {
        for(int j=1;j<(capacity+1);j++)
        {
            if(weight[i-1]<=j)
                dp[i][j]=max(value[i-1]+dp[i-1][j-weight[i-1]],dp[i-1][j]);
            else
                dp[i][j]=dp[i-1][j];
        }
    }
    return dp[n][capacity];
    
}

int solveOpt(vector<int>weight, vector<int>&value, int n, int capacity)
{
    vector<int>prev(capacity+1, 0);
    vector<int>curr(capacity+1, 0);

    //base case
    for(int i=weight[0];i<=capacity;i++)
    {
        if(weight[0]<=capacity)
            prev[i]=value[0];
        else
            prev[i]=0;
    }

    for(int index=1;index<n;index++)
    {
        for(int w=0;w<=capacity;w++)
        {
            int include=0;
            if(weight[index]<=w)
                include=value[index] + prev[w-weight[index]];
            int exclude=prev[w];

            curr[w]=max(include, exclude);
        }
        prev=curr;
    }
    return prev[capacity];
}


int knapSack(vector<int>&weight, vector<int>&values, int n, int w)
{
    //int ans=solveRec(weight, values, n-1, w);
    // vector<vector<int>>dp(n, vector<int>(w+1, -1));
    // int ans=solveMemo(weight, values, n-1, w, dp);
    // int ans=solveTab(weight, values, n, w);
    int ans=solveOpt(weight, values, n, w);
    return ans;
}


int main()
{
    int n,w;//n-value of n items and w-capacities of bags
    cin>>n>>w;
    vector<int>values(n), weight(n);
    for(int i=0;i<n;i++)
        cin>>values[i];
    for(int i=0;i<n;i++)
        cin>>weight[i];
    cout<<knapSack(weight, values, n, w)<<"\n";

}