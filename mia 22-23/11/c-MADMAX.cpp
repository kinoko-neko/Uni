#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
using namespace std;

int dp[105][105][30];
vector<pair<int, int> >v[105];

bool wyn(int a, int b, int c){//a-gracz start, b-gracz 2
    if(dp[a][b][c]==0){
        for(int i=0;i<v[a].size();i++){
            if(v[a][i].ss>=c){
                if(!wyn(b,v[a][i].ff,v[a][i].ss)) {
                    dp[a][b][c]=1; return true;
                }
            }
        }
        dp[a][b][c]=-1;
    }
    return dp[a][b][c]==1;
}

int main(){
    int n, m;
    cin>>n>>m;
    while(m--){
        int a,b; char c;
        cin>>a>>b>>c;
        v[a].pb({b,c-'a'});
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(wyn(i,j,0)) cout<<"A"; else cout<<"B";
        }
        cout<<"\n";
    }
}
