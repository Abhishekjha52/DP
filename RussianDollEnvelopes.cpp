//Leetcode Hard-https://leetcode.com/problems/russian-doll-envelopes/
//The approach is similar to LIS(Length Increasing Subsequence)
//We need to sort the envelopes array so that one envelope can be placed in another
//here the logic is sort the envelopes acc to width but if we find same width then sort acc to breadth in desc order
//because if we sort the breadth in decreasing order then we can find the maximum envelopes inserted

#include<bits/stdc++.h>
using namespace std;
static bool cmp(vector<int>&a, vector<int>&b)
{
    if(a[0]==b[0])
        return a[1]>b[1];
    return a[0]<b[0];
}
int maxEnvelopes(vector<vector<int>>& envelopes) {
    int row=envelopes.size();
    int col=envelopes[0].size();
    sort(envelopes.begin(), envelopes.end(), cmp);
    vector<int>ans;
    ans.push_back(envelopes[0][1]);
    for(int i=1;i<row;i++)
    {
        if(envelopes[i][1]>ans.back())
            ans.push_back(envelopes[i][1]);
        else
        {
            int index=lower_bound(ans.begin(), ans.end(), envelopes[i][1])-ans.begin();
            ans[index]=envelopes[i][1];
        }
    }
    return ans.size();
}
int main()
{
    int r,c;cin>>r>>c;
    vector<vector<int>>a(r, vector<int>(c));
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
            cin>>a[i][j];
    }
    // for(int i=0;i<r;i++)
    // {
    //     for(int j=0;j<c;j++)
    //         cout<<a[i][j]<<" ";
    //     cout<<"\n";
    // }
    int ans=maxEnvelopes(a);
    cout<<ans<<"\n";
}