//Leetcode - https://leetcode.com/problems/maximum-alternating-subsequence-sum/
//The alternating sum of a 0-indexed array is defined as 
//the sum of the elements at even indices minus the sum of the elements at odd indices.

//Approach here would be to take the index and track index whether it is even or odd
//it is same as 0/1 knapsack where we either take it or not 
//if we take we process in two case either odd or even
//if we donot take we use recursion for processing further


#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fast_IO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
ll dp[100005][2];
ll solveRec(vector<ll>&nums, ll index, ll flag)
{
    ll n=nums.size();
    //base case
    if(index>=n)
        return 0;
    
    ll op1=LLONG_MIN, op2=LLONG_MIN;
    
    //don't pick element
    op1=solveRec(nums, index+1, flag);
    
    //pick elements
    //case 1: if it is even
    if(flag==0)
        op2=nums[index]+solveRec(nums, index+1, 1);
    //case 2:if it is odd
    else
        op2=-1*1LL*nums[index]+solveRec(nums, index+1, 0);
    
    return max(op1, op2);
        
}
ll solveMemo(vector<ll>&nums, ll index, ll flag)
{
    //base case
    if(index>=nums.size())
        return 0;
    
    if(dp[index][flag]!=-1)return dp[index][flag];
    
    ll op1=LLONG_MIN, op2=LLONG_MIN;
    
    //don't pick element
    op1=solveMemo(nums, index+1, flag);
    
    //pick elements
    //case 1: if it is even
    if(flag==0)
        op2=nums[index]+solveMemo(nums, index+1, 1);
    //case 2:if it is odd
    else
        op2=-1*1LL*nums[index]+solveMemo(nums, index+1, 0);
    
    return dp[index][flag]=max(op1, op2);
        
}
ll maxAlternatingSum(vector<ll>& nums) {
    //long long ans=solveRec(nums, 0, 0);
    //long long n=nums.size();
    memset(dp, -1, sizeof(dp));
    return solveMemo(nums, 0, 0);
    //return ans;
}
int main()
{
    fast_IO;
    ll n;cin>>n;
    vector<ll>v(n);
    for(int i=0;i<n;i++)cin>>v[i];
    ll ans=maxAlternatingSum(v);
    cout<<ans<<"\n";
}