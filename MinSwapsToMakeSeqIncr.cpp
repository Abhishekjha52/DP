#include<bits/stdc++.h>
using namespace std;
int solveRec(int index, vector<int>&nums1, vector<int>&nums2, bool swapped)
{
    //base case
    if(index==nums1.size())
        return 0;
    
    int ans=INT_MAX;
    
    //to compare if it is strictly increasing we take prev numbers
    int prev1=nums1[index-1];
    int prev2=nums2[index-1];
    
    //if prev elements are swapped then to handle the correct 
    //sequence we need to swap those stored values
    if(swapped)
        swap(prev1, prev2);
    
    //No swap condition
    if(nums1[index]>prev1 && nums2[index]>prev2)
        ans=solveRec(index+1, nums1, nums2, 0);
    
    //swap condition--to check after swapping its still in increasing order, compare alter prevs
    if(nums1[index]>prev2 && nums2[index]>prev1)
        ans=min(ans, 1+solveRec(index+1, nums1, nums2, 1));
    
    return ans;
}

int solveMemo(int index, vector<int>&nums1, vector<int>&nums2, bool swapped, vector<vector<int>>&dp)
{
    //base case
    if(index==nums1.size())
        return 0;
    
    if(dp[index][swapped]!=-1)
        return dp[index][swapped];
    
    int ans=INT_MAX;
    
    //to compare if it is strictly increasing we take prev numbers
    int prev1=nums1[index-1];
    int prev2=nums2[index-1];
    
    //if prev elements are swapped then to handle the correct 
    //sequence we need to swap those stored values
    if(swapped)
        swap(prev1, prev2);
    
    //No swap condition
    if(nums1[index]>prev1 && nums2[index]>prev2)
        ans=solveMemo(index+1, nums1, nums2, 0, dp);
    
    //swap condition--to check after swapping its still in increasing order, compare alter prevs
    if(nums1[index]>prev2 && nums2[index]>prev1)
        ans=min(ans, 1+solveMemo(index+1, nums1, nums2, 1, dp));
    
    return dp[index][swapped]=ans;
    
    
}

int solveTab(vector<int>&nums1, vector<int>&nums2)
{
    int n=nums1.size();
    vector<vector<int>>dp(n+1, vector<int>(2, 0));
    for(int index=n-1;index>=1;index--)
    {
        for(int swapped=1;swapped>=0;swapped--)
        {
            int ans=INT_MAX;
    
            //to compare if it is strictly increasing we take prev numbers
            int prev1=nums1[index-1];
            int prev2=nums2[index-1];

            //if prev elements are swapped then to handle the correct 
            //sequence we need to swap those stored values
            if(swapped)
                swap(prev1, prev2);

            //No swap condition
            if(nums1[index]>prev1 && nums2[index]>prev2)
                ans=dp[index+1][0];

            //swap condition--to check after swapping its still in increasing order, compare alter prevs
            if(nums1[index]>prev2 && nums2[index]>prev1)
                ans=min(ans, 1+dp[index+1][1]);

            dp[index][swapped]=ans;
        }
    }
    return dp[1][0];
    
}

int solveOpt(vector<int>&nums1, vector<int>&nums2)
{
    int n=nums1.size();
    
    int currswap=0;
    int currnoswap=0;
    int swap=0;
    int noswap=0;
    
    for(int index=n-1;index>=1;index--)
    {
        for(int swapped=1;swapped>=0;swapped--)
        {
            int ans=INT_MAX;
    
            //to compare if it is strictly increasing we take prev numbers
            int prev1=nums1[index-1];
            int prev2=nums2[index-1];

            //if prev elements are swapped then to handle the correct 
            //sequence we need to swap those stored values
            if(swapped)
            {
                int temp=prev1;
                prev2=prev1;
                prev1=temp;
            }

            //No swap condition
            if(nums1[index]>prev1 && nums2[index]>prev2)
                ans=noswap;

            //swap condition--to check after swapping its still in increasing order, compare alter prevs
            if(nums1[index]>prev2 && nums2[index]>prev1)
                ans=min(ans, 1+swap);

            if(swapped)
                currswap=ans;
            else
                currnoswap=ans;
        }
    }
    return min(swap, noswap);
    
}

int minSwap(vector<int>& nums1, vector<int>& nums2) {
    int n1=nums1.size();
    int n2=nums2.size();
    
    nums1.insert(nums1.begin(), -1);
    nums2.insert(nums2.begin(), -1);
    
    bool swapped=0;
    //return solveRec(1, nums1, nums2, swapped);
    
    // vector<vector<int>>dp(n1+1, vector<int>(2, -1));
    // return solveMemo(1, nums1, nums2, swapped, dp);
    return solveTab(nums1, nums2);
}

int main()
{
    int n;cin>>n;
    vector<int>nums1(n), nums2(n);
    for(int i=0;i<n;i++)
        cin>>nums1[i];
    for(int i=0;i<n;i++)
        cin>>nums2[i];

    int ans=minSwaps(nums1, nums2);
    cout<<ans<<"\n";
}