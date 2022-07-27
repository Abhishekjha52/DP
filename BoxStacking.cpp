#include<bits/stdc++.h>
using namespace std;

int solve(vector<vector<int>>& v,int n,int idx, vector<int>&dp){
    int ans=0;
    if(dp[idx]!=-1) return dp[idx];
    
    for(int i=0;i<n;i++){
        if(v[idx][0]>v[i][0] and v[idx][1]>v[i][1]){
            ans=max(ans,solve(v, n, i, dp)+v[i][2]);
        }
    }
    return dp[idx]= ans;
}
int maxHeight(vector<int>&height,vector<int>&width,vector<int>&length, int n)
{
    vector<int>dp(702, -1);
    vector<vector<int>>boxes;
    for(int i=0;i<n;i++)
    {
        boxes.push_back({length[i], width[i], height[i]});
        boxes.push_back({width[i], length[i], height[i]});
        boxes.push_back({width[i], height[i], length[i]});
        boxes.push_back({height[i], width[i], length[i]});
        boxes.push_back({height[i], length[i], width[i]});
        boxes.push_back({length[i], height[i], width[i]});
    }
    
    int ans=0;
    for(int i=0;i<6*n;i++)
        ans=max(ans,solve(boxes,6*n,i, dp)+boxes[i][2]);
    return ans;
}
int main()
{
    int n;cin>>n;
    vector<int>height(n), width(n), length(n);
    for(int i=0;i<n;i++)
        cin>>height[i];
    for(int i=0;i<n;i++)
        cin>>width[i];
    for(int i=0;i<n;i++)
        cin>>length[i];

    int ans=maxHeight(height, width, length, n);
    cout<<ans<<"\n";
}