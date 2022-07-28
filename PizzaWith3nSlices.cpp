//Leetcode Hard-https://leetcode.com/problems/pizza-with-3n-slices/
//This problem is similar to House Robbery II problem to find the maximum sum, here it is pizza

#include<bits/stdc++.h>
using namespace std;
int solveRec(int index, int endIndex, vector<int>&slices, int n)
{
    //base case
    if(index>endIndex || n==0)
        return 0;
    
    int take=slices[index]+solveRec(index+2, endIndex, slices, n-1);
    int notTake=0+solveRec(index+1, endIndex, slices, n);
    
    return max(take, notTake);
}

int solveMemo(int index, int endIndex, vector<int>&slices, int n, vector<vector<int>>&dp)
{
    //base case
    if(index>endIndex || n==0)
        return 0;
    if(dp[index][n]!=-1)
        return dp[index][n];
    
    int take=slices[index]+solveMemo(index+2, endIndex, slices, n-1, dp);
    int notTake=0+solveMemo(index+1, endIndex, slices, n, dp);
    
    return dp[index][n]= max(take, notTake);

}

int solveTab(vector<int>&slices)
{
    int k=slices.size();
    
    vector<vector<int>>dp1(k+2, vector<int>(k+2, 0));
    vector<vector<int>>dp2(k+2, vector<int>(k+2, 0));
    
    for(int index=k-2;index>=0;index--)
    {
        for(int n=1;n<=k/3;n++)
        {
            int take=slices[index]+dp1[index+2][n-1];
            int notTake=0+dp1[index+1][n];
            dp1[index][n]=max(take, notTake);
            
        }
    }
    
    int case1=dp1[0][k/3];
    
    for(int index=k-1;index>=1;index--)
    {
        for(int n=1;n<=k/3;n++)
        {
            int take=slices[index]+dp2[index+2][n-1];
            int notTake=0+dp2[index+1][n];
            dp2[index][n]=max(take, notTake);
            
        }
    }
    
    int case2=dp2[1][k/3];
    
    return max(case1, case2);
}

int solveOpt(vector<int>&slices)
{
    //here values depends on three rows so we create three vectors instead of dp
    int k=slices.size();
    
    vector<int>prev1(k+2, 0);
    vector<int>curr1(k+2, 0);
    vector<int>next1(k+2, 0);
    
    for(int index=k-2;index>=0;index--)
    {
        for(int n=1;n<=k/3;n++)
        {
            int take=slices[index]+next1[n-1];
            int notTake=0+curr1[n];
            prev1[n]=max(take, notTake);
        }
        next1=curr1;
        curr1=prev1;
    }
    
    int case1=curr1[k/3];
    
    vector<int>prev2(k+2, 0);
    vector<int>curr2(k+2, 0);
    vector<int>next2(k+2, 0);
    
    for(int index=k-1;index>=1;index--)
    {
        for(int n=1;n<=k/3;n++)
        {
            int take=slices[index]+next2[n-1];
            int notTake=0+curr2[n];
            prev2[n]=max(take, notTake); 
        }
        next2=curr2;
        curr2=prev2;
    }
    
    int case2=curr2[k/3];
    
    return max(case1, case2);
}

int maxSizeSlices(vector<int>& slices) {
    int k=slices.size();
    int maxIcanEat=k/3;
    // int case1=solveRec(0, k-2, slices, maxIcanEat);
    // int case2=solveRec(1, k-1, slices, maxIcanEat);
    vector<vector<int>>dp1(k, vector<int>(k, -1));
    int case1=solveMemo(0, k-2, slices, maxIcanEat, dp1);
    
    vector<vector<int>>dp2(k, vector<int>(k, -1));
    int case2=solveMemo(1, k-1, slices, maxIcanEat, dp2);
    return max(case1, case2);
    
}

int main()
{
    int n;cin>>n;
    vector<int>slices(n);
    for(int i=0;i<n;i++)cin>>slices[i];
    int ans=maxSizeSlices(slices);
    cout<<ans<<"\n";
}