#include<bits/stdc++.h>
using namespace std;
int solveRec(vector<int>&a, int n, int curr, int prev)//TC:O(2^N)
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
int solveMemo(vector<int>&a, int n, int curr, int prev, vector<vector<int>>&dp)//TC:O(N*N) SC:O(N*N)
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
int solveTab(vector<int>&a, int n)//TC:O(N*N) SC:O(N*N)
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
int solveOpt(vector<int>&a, int n)//TC:O(N*N) SC:O(N)
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

int solveMostOpt(vector<int>&a, int n)//TC:O(NlogN) SC:O(N)
{
    //using DP with Binary Search
    //the approach is to use lower_bound to find the index of just increasing number in array
    //and replacing it with lowest number
    if(n==0)
        return 0;
        
    vector<int>ans;
    ans.push_back(a[0]);
    
    for(int i=1;i<n;i++)
    {
        if(a[i]>ans.back())
            ans.push_back(a[i]);
        else
        {
            int index=lower_bound(ans.begin(), ans.end(), a[i])-ans.begin();
            ans[index]=a[i];
        }
    }
    return ans.size();
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
