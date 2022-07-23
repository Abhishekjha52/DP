/* Code Link- https://leetcode.com/problems/minimum-sideway-jumps/ */
//Here we need to find the minimum side ways jumpa frog takes to reach end position
//we need to increment jump variable if we jump sideways
//we cannot jump on the position of stones(obstacle)
#include<bits/stdc++.h>
#define fast_IO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
typedef long long ll;
using namespace std;
ll solveRec(vector<ll>&obstacles, ll currLane, ll currPos)
{
    int n=obstacles.size()-1;//since we use 0-based indexing
    //base case
    if(currPos==n)
        return 0;
    
    //forward moving
    if(obstacles[currPos+1]!=currLane)
    {
        //use recursion to solve further movement
        return solveRec(obstacles, currLane, currPos+1);
    }
    else
    {
        //sideways jump
        //we can get many paths sideways and we need minimum ways
        ll ans=INT_MAX;
        //we have three lanes so we iterate three lanes
        for(ll i=1;i<=3;i++)
        {
            //check jump should not be in same position && obstacles conditions
            if(currLane!=i && obstacles[currPos]!=i)
                ans=min(ans, 1+solveRec(obstacles, i, currPos));
        }
        return ans;
    }
}
ll solveMemo(vector<ll>&obstacles, ll currLane, ll currPos, vector<vector<ll>>&dp)
{
    ll n=obstacles.size()-1;//since we use 0-based indexing
    //base case
    if(currPos==n)
        return 0;
    
    if(dp[currLane][currPos]!=-1)
        return dp[currLane][currPos];
    
    //forward moving
    if(obstacles[currPos+1]!=currLane)
    {
        //use recursion to solve further movement
        dp[currLane][currPos]=solveMemo(obstacles, currLane, currPos+1, dp);
    }
    else
    {
        //sideways jump
        //we can get many paths sideways and we need minimum ways
        ll ans=INT_MAX;
        //we have three lanes so we iterate three lanes
        for(ll i=1;i<=3;i++)
        {
            //check jump should not be in same position && obstacles conditions
            if(currLane!=i && obstacles[currPos]!=i)
                ans=min(ans, 1+solveMemo(obstacles, i, currPos, dp));
        }
        dp[currLane][currPos]=ans;
    }
    return dp[currLane][currPos];
}
ll solveTab(vector<ll>&obstacles)
{
    ll n=obstacles.size()-1;
    vector<vector<ll>>dp(4, vector<ll>(obstacles.size(),1e9));
    //base case that is filling last colum with zeros
    for(ll i=0;i<4;i++)
        dp[i][n]=0;
    
    //since it is bottom up we come from last and fill up the columns
    for(ll currPos=n-1;currPos>=0;currPos--)
    {
        for(ll currLane=1;currLane<=3;currLane++)
        {
            //forward moving
            if(obstacles[currPos+1]!=currLane)
                dp[currLane][currPos]=dp[currLane][currPos+1];
            else
            {
                //sideways jump
                //we can get many paths sideways and we need minimum ways
                ll ans=1e9;
                //we have three lanes so we iterate three lanes
                for(ll i=1;i<=3;i++)
                {
                    //check jump should not be in same position && obstacles conditions
                    if(currLane!=i && obstacles[currPos]!=i)
                        ans=min(ans, 1+dp[i][currPos+1]);//here what if next lane value is not calculated and value is dependent on uncalculated value hence we redirect to next column value
            
                }
                dp[currLane][currPos]=ans;
            }
        }
    }
    return min(dp[2][0], min(1+dp[1][0], 1+dp[3][0]));
}

ll solveOpt(vector<ll>&obstacles)
{
    ll n=obstacles.size()-1;
    
    vector<ll>curr(4, INT_MAX);
    vector<ll>next(4, INT_MAX);
    
    for(ll i=0;i<4;i++)
        next[i]=0;
    
    
    for(ll currPos=n-1;currPos>=0;currPos--)
    {
        for(ll currLane=1;currLane<=3;currLane++)
        {
            //forward moving
            if(obstacles[currPos+1]!=currLane)
                curr[currLane]=next[currLane];
            else
            {
                //sideways jump
                //we can get many paths sideways and we need minimum ways
                ll ans=1e9;
                //we have three lanes so we iterate three lanes
                for(ll i=1;i<=3;i++)
                {
                    //check jump should not be in same position && obstacles conditions
                    if(currLane!=i && obstacles[currPos]!=i)
                        ans=min(ans, 1+next[i]);
                }
                curr[currLane]=ans;
            }
        }
        next=curr;
    }
    return min(next[2], min(1+next[1], 1+next[3]));
}
ll minSideWaysJumps(vector<ll>& obstacles) {
    ll n=obstacles.size();
    vector<vector<ll>>dp(4, vector<ll>(n, -1));
    return solveMemo(obstacles, 2, 0, dp);
    // ll ans=solveRec(obstacles, 2, 0);
    // return ans;
    return solveTab(obstacles);
    return solveOpt(obstacles);
}
int main()
{
    fast_IO;
    ll n;cin>>n;
    vector<ll>v(n);
    for(ll i=0;i<n;i++)cin>>v[i];
    ll ans=minSideWaysJumps(v);
    cout<<ans<<"\n";
}