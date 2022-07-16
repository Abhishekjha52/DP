//In this problem we need to find the minimum values of the triangles formed in polygon
//We know that first vertex and last vertex are adjacent since it is in clockwise order
// we first need to find the third point which ranges from i+1 to j-1
//first point is i, last point is j, third point need to be found to form a triangle
//recurrence relation formed is i*j*k + solve(i,k)+solve(k,j) 
#include<bits/stdc++.h>
using namespace std;
int solveRec(vector<int>&values, int i, int j)
{
    //base case
    if(i+1==j)//if first and last point are only vertices in a polygon, then we cant find triangle
        return 0;
    
    int ans=INT_MAX;
    for(int k=i+1;k<j;k++)
    {
        ans=min(ans, values[i]*values[j]*values[k] + solveRec(values, i, k) + solveRec(values, k, j));
    }
    return ans;
}
int solveMemo(vector<int>&values, int i, int j, vector<vector<int>>&dp)
{
    //base case
    if(i+1==j)//if first and last point are only vertices in a polygon, then we cant find triangle
        return 0;
    
    if(dp[i][j]!=-1)return dp[i][j];
    
    int ans=INT_MAX;
    for(int k=i+1;k<j;k++)
    {
        ans=min(ans, values[i]*values[j]*values[k] + solveMemo(values, i, k, dp) + solveMemo(values, k, j, dp));
    }
    dp[i][j]=ans;
    return dp[i][j];
}
int minScoreTriangulation(vector<int>& values) {
    int n=values.size();
    vector<vector<int>>dp(n, vector<int>(n, -1));
    //return solveRec(values, 0, n-1);
    return solveMemo(values, 0, n-1, dp);
}
int main()
{
    int n;cin>>n;
    vector<int>values(n);
    for(int i=0;i<n;i++)cin>>values[i];
    int ans=minScoreTriangulation(values);
    cout<<ans<<"\n";
    return 0;
}
    