//C++ program to find largest square area in matrix
#include<bits/stdc++.h>
using namespace std;
int solveRec(vector<vector<int>>&mat, int i, int j, int &maxi)
{
    //base case
    if(i>=mat.size() || j>=mat[0].size())return 0;
    
    int right=solveRec(mat, i, j+1, maxi);
    int diagonal=solveRec(mat, i+1, j+1, maxi);
    int down=solveRec(mat, i+1, j, maxi);
    
    //we get all answers from all directions
    //now if we want to include the answers
    //we need to check the value is 1 at curr position or not
    if(mat[i][j]==1)
    {
        //we need to take minimum of all the ans from function calls
        int ans=1+min({right, diagonal, down});
        maxi=max(maxi, ans);
        return ans;
    }
    else//square forms only if it is 1 else return 0
        return 0;
}
int solveMemo(vector<vector<int>>&mat, int i, int j, int& maxi, vector<vector<int>>&dp)
{
    //base case
    if(i>=mat.size() || j>=mat[0].size())return 0;
    if(dp[i][j]!=-1)return dp[i][j];
    
    int right=solveMemo(mat, i, j+1, maxi, dp);
    int diagonal=solveMemo(mat, i+1, j+1, maxi, dp);
    int down=solveMemo(mat, i+1, j, maxi, dp);
    
    //we get all answers from all directions
    //now if we want to include the answers
    //we need to check the value is 1 at curr position or not
    if(mat[i][j]==1)
    {
        //we need to take minimum of all the ans from function calls
        dp[i][j]=1+min({right, diagonal, down});
        maxi=max(maxi, dp[i][j]);
        return dp[i][j];
    }
    else//square forms only if it is 1 else return 0
        return dp[i][j]=0;
}
int solveTab(vector<vector<int>>&mat, int &maxi)
{
    int r=mat.size(), c=mat[0].size();
    vector<vector<int>>dp(r+1, vector<int>(c+1, 0));//filling with 0 handles base case
    
    for(int i=r-1;i>=0;i--)
    {
        for(int j=c-1;j>=0;j--)
        {
            int right=dp[i][j+1];
            int diagonal=dp[i+1][j+1];
            int down=dp[i+1][j];
            
            //we get all answers from all directions
            //now if we want to include the answers
            //we need to check the value is 1 at curr position or not
            if(mat[i][j]==1)
            {
                //we need to take minimum of all the ans from function calls
                dp[i][j]=1+min({right, diagonal, down});
                maxi=max(maxi, dp[i][j]);
            }
            else//square forms only if it is 1 else store 0
                dp[i][j]=0;
        }
    }
    return dp[0][0];
}
int solveOpt(vector<vector<int>>&mat, int &maxi)
{
    //we can solve using O(m) Space Optimization by using two rows
    //values depending on rows- dp[i] denotes currRow, dp[i+1] denotes nextRow
    int r=mat.size(), c=mat[0].size();
    vector<int>currRow(c+1, 0);
    vector<int>nextRow(c+1, 0);
    
    for(int i=r-1;i>=0;i--)
    {
        for(int j=c-1;j>=0;j--)
        {
            int right=currRow[j+1];
            int diagonal=nextRow[j+1];
            int down=nextRow[j];
            
            //we get all answers from all directions
            //now if we want to include the answers
            //we need to check the value is 1 at curr position or not
            if(mat[i][j]==1)
            {
                //we need to take minimum of all the ans from function calls
                currRow[j]=1+min({right, diagonal, down});
                maxi=max(maxi, currRow[j]);
            }
            else//square forms only if it is 1 else store 0
                currRow[j]=0;
        }
        //after every full iteration traverse next rows
        nextRow=currRow;
    }
    return nextRow[0];
}

int maxSquare(int n, int m, vector<vector<int>> mat){
    int maxi=0;
    //solveRec(mat, 0, 0, maxi);
    //vector<vector<int>>dp(n, vector<int>(m,-1));
    //solveMemo(mat, 0, 0, maxi, dp);
    //solveTab(mat, maxi);
    solveOpt(mat, maxi);
    return maxi;
}
int main()
{
    int r,c;
    cin>>r>>c;
    vector<vector<int>>mat(r, vector<int>(c));
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
            cin>>mat[i][j];
    }
    int ans=maxSquare(r, c, mat);
    cout<<ans<<"\n";
    return 0;
}