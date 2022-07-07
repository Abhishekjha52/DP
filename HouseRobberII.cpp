//c++ program to return maximum amount of money steal from house
//House Robbery II
//Condition: The houses are arranged in cirular manner, so cannot rob first and last house at a time as it is adjacent to each other
#include<bits/stdc++.h>
using namespace std;
int solveOpt(vector<int>&nums)
{
    int n=nums.size();

    int prev2=0;
    int prev1=nums[0];
    for(int i=1;i<n;i++)
    {
        int incl=prev2+nums[i];
        int excl=prev1+0;
        
        int ans=max(incl, excl);
        prev2=prev1;
        prev1=ans;
    }
    return prev1;

}
int main()
{
    int n;cin>>n;
    vector<int>v(n);
    for(int i=0;i<n;i++)cin>>v[i];
    //to handle the condition we consider two arrays
    //first array contains array starting from second element to last
    //second array contains elements from first to last second element
    vector<int>first(n,0),second(n,0);
    for(int i=0;i<n;i++)
    {
        if(i!=n-1)
            first.push_back(v[i]);
    }
    for(int i=0;i<n;i++)
    {
        if(i!=0)
            second.push_back(v[i]);
    }
    int ans1=solveOpt(first);
    int ans2=solveOpt(second);
    cout<<max(ans1, ans2);
}