//Leetcode Hard: https://leetcode.com/problems/reducing-dishes/
// A chef has collected data on the satisfaction level of his n dishes. Chef can cook any dish in 1 unit of time.
// Like-time coefficient of a dish is defined as the time taken to cook that dish including previous dishes multiplied 
//by its satisfaction level i.e. time[i] * satisfaction[i].
// Return the maximum sum of like-time coefficient that the chef can obtain after dishes preparation.
#include<bits/stdc++.h>
using namespace std;
int solveRec(vector<int>&satisfaction, int size, int index, int time)//TC:O(2^n), TLE
{
    //base case
    if(index>=size)return 0;
    
    int include=satisfaction[index]*(time+1) + solveRec(satisfaction, size, index+1, time+1);
    int exclude=0 + solveRec(satisfaction, size, index+1, time);
    
    return max(include, exclude);
}

//TC:O(n*n) SC:O(n*n)
int solveMemo(vector<int>&satisfaction, int size, int index, int time, vector<vector<int>>&dp)
{
    //base case
    if(index>=size)return 0;
    if(dp[index][time]!=-1)return dp[index][time];
    
    int include=satisfaction[index]*(time+1) + solveMemo(satisfaction, size, index+1, time+1, dp);
    int exclude=0 + solveMemo(satisfaction, size, index+1, time, dp);
    
    dp[index][time]= max(include, exclude);
    return dp[index][time];
}

//TC:O(n*n) SC:O(n*n)
int solveTab(vector<int>&satisfaction)
{
    int n=satisfaction.size();
    vector<vector<int>>dp(n+1, vector<int>(n+1, 0));
    
    for(int index=n-1;index>=0;index--)
    {
        for(int time=index;time>=0;time--)
        {
            int include=satisfaction[index]*(time+1) + dp[index+1][time+1];
            int exclude=0 + dp[index+1][time];
    
            dp[index][time]=max(include, exclude);
        }
    }
    return dp[0][0]; 
}

//TC:O(n*n) SC:O(n)
int solveOpt(vector<int>&satisfaction)
{
    int n=satisfaction.size();
    vector<int>curr(n+1, 0);
    vector<int>next(n+1, 0);
    
    for(int index=n-1;index>=0;index--)
    {
        for(int time=index;time>=0;time--)
        {
            int include=satisfaction[index]*(time+1) + next[time+1];
            int exclude=0 + next[time];
    
            curr[time]=max(include, exclude);
        }
        next=curr;
    }
    return next[0];
}

//TC:O(nlogn) SC:O(1)
int solveGreedy(vector<int>satisfaction)
{
    int n=satisfaction.size();
    sort(satisfaction.begin(), satisfaction.end());
    int maxiSum=0, sum=0;
    for(int i=n-1;i>=0 && satisfaction[i]+sum>0;i--)
    {
        sum+=satisfaction[i];
        maxiSum+=sum;
    }
    return maxiSum;
}
int maxSatisfaction(vector<int>& satisfaction)
{
    //here we need to sort the satisfaction array to increase the like-time coefficient
    //this problem is similar to knapsack as it is works with include that dish or exclude the dish
    int n=satisfaction.size();
    sort(satisfaction.begin(), satisfaction.end());
    //we pass the index and its current time to validate
    //int ans=solveRec(satisfaction, n, 0, 0);
    
    vector<vector<int>>dp(n+1, vector<int>(n+1, -1));
    //return solveMemo(satisfaction, n, 0, 0, dp);
    //return solveTab(satisfaction);
    //return solveOpt(satisfaction);
    return solveGreedy(satisfaction);
    //return ans;
}
int main()
{
    int n;cin>>n;
    vector<int>v(n);
    for(int i=0;i<n;i++)cin>>v[i];
    int ans=maxStisfaction(v);
    cout<<ans<<"\n";
    return 0;
}