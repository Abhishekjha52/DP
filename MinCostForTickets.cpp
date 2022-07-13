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