//C++ program to return the minimum number of dollars you need to travel every day
//Leetcode 983 - https://leetcode.com/problems/minimum-cost-for-tickets/
#include<bits/stdc++.h>
using namespace std;
int solveRec(vector<int>&days, vector<int>&cost, int index)
{
    //base case
    //if already we are at last day of journey
    //we don't want to further travel
    if(index>=days.size())return 0;

    //if we take 1-day pass
    int option1=cost[0]+solveRec(days, cost, index+1);

    //if we take 7-day pass
    //we need to cover 7 days
    int i;
    //this will track the index after 7 days pass
    for(i=index;i<days.size() && days[i]<days[index]+7;i++);

    int option2=cost[1]+solveRec(days, cost, i);

    //if we take 30-day pass
    //we need to cover 30 days
    //this will track the index after 30 days pass
    for(i=index;i<days.size() && days[i]<days[index]+30;i++);

    int option3=cost[2]+solveRec(days, cost, i);

    return min({option1, option2, option3});

}
int solveMemo(vector<int>&days, vector<int>&cost, int index, vector<int>&dp)
{
    //base case
    //if already we are at last day of journey
    //we don't want to further travel
    if(index>=days.size())return 0;
    
    if(dp[index]!=-1)return dp[index];

    //if we take 1-day pass
    int option1=cost[0]+solveMemo(days, cost, index+1, dp);

    //if we take 7-day pass
    //we need to cover 7 days
    int i;
    //this will track the index after 7 days pass
    for(i=index;i<days.size() && days[i]<days[index]+7;i++);

    int option2=cost[1]+solveMemo(days, cost, i, dp);

    //if we take 30-day pass
    //we need to cover 30 days
    //this will track the index after 30 days pass
    for(i=index;i<days.size() && days[i]<days[index]+30;i++);

    int option3=cost[2]+solveMemo(days, cost, i, dp);

    dp[index] = min({option1, option2, option3});
    return dp[index];

}
int solveTab(int n, vector<int>&days, vector<int>&cost)
{
    vector<int>dp(n+1, INT_MAX);
    dp[n]=0;
    for(int k=n-1;k>=0;k--)
    {
        //1-day pass
        int option1=cost[0]+dp[k+1];
        
        //if we take 7-day pass
        //we need to cover 7 days
        int i;
        //this will track the index after 7 days pass
        for(i=k;i<n && days[i]<days[k]+7;i++);

        int option2=cost[1]+dp[i];
        
        //if we take 30-day pass
        //we need to cover 30 days
        //this will track the index after 30 days pass
        for(i=k;i<n && days[i]<days[k]+30;i++);

        int option3=cost[2]+dp[i];

        dp[k]= min(option1, min(option2, option3));
    }
    return dp[0];
}
int solveOpt(int n, vector<int>&days, vector<int>&cost)
{
    //if we add anything to INT_MAX, we get interger overflow,hence use 0
    int ans=0;
    queue<pair<int,int>>month;
    queue<pair<int,int>>week;
    
    for(int day:days)
    {
        //step 1:remove expired days from queue
        while(!month.empty() && month.front().first+30<=day)
            month.pop();
        
        while(!week.empty() && week.front().first+7<=day)
            week.pop();
        
        //step 2:add cost for current day
        week.push({day, ans+cost[1]});
        month.push({day, ans+cost[2]});
        
        //step 3:update ans
        ans=min(ans+cost[0], min(month.front().second, week.front().second));
    }
    return ans;
}
int minCostTickets(int n, vector<int>&days, vector<int>&costs)
{
    vector<int>dp(n+1, -1);
    return solveMemo(days, costs, 0, dp);
    //return solveRec(days, costs, 0);
}
int main()
{
    int n;cin>>n;
    vector<int>days(n);
    for(int i=0;i<n;i++)cin>>days[i];
    int m;cin>>m;
    vector<int>costs(m);
    for(int i=0;i<m;i++)cin>>costs[i];
    int ans=minCostTickets(n, days, costs);
    cout<<ans<<"\n";

}
