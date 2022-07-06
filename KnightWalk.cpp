//C++ program to find the minimum steps a Knight will take to reach the target position
#include<bits/stdc++.h>
using namespace std;
#define fast_IO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
int minSteps(vector<ll>&knightPos, vector<ll>&targetPos, int n)
{
    queue<pair<vector<ll>, ll>>q;//vector<int> stores knight position values and int stores no of moves
    q.push({knightPos, 0});
    vector<pair<ll,ll>>moves={{1,2}, {2,1}, {-1,2}, {-2,1},{1,-2},{2,-1},{-1,-2},{-2,-1}};
    vector<vector<ll>>vis(n+1, vector<ll>(n+1, INT_MAX));

    while(q.size())
    {
        auto currPos=q.front().first;
        ll move=q.front().second;
        q.pop();

        if(currPos==targetPos)
            return move;

        for(auto x:moves)
        {
            int new_x=currPos[0]+x.first;
            int new_y=currPos[1]+x.second;
            if(new_x>0 && new_x<=n && new_y>=0 && new_y<=n && vis[new_x][new_y]>move+1)
            {
                vis[new_x][new_y]=move+1;
                q.push({{new_x,new_y}, move+1});
            }
        }
    }
    return -1;

}
int main()
{
    fast_IO;
    ll n;cin>>n;
    vector<ll>knightPos(2);
    vector<ll>targetPos(2);
    cin>>knightPos[0]>>knightPos[1];
    cin>>targetPos[0]>>targetPos[1];
    int ans=minSteps(knightPos, targetPos, n);
    cout<<ans<<"\n";
    return 0;
}
