#include<bits/stdc++.h>
using namespace std;


bool mapa[55][55];
bool vis[55][55];
pair<int,int> moves[4]= {{-1,0},{1,0},{0,-1},{0,1}};
int n;
int xs,ys,xm,ym;

vector<pair<int,int> >sp1,sp2;

void dfs(int x, int y,vector<pair<int,int> >&sp){
    vis[x][y]=true; sp.push_back({x,y});
    for(int i=0;i<4;i++){
        if(mapa[x+moves[i].first][y+moves[i].second] && !vis[x+moves[i].first][y+moves[i].second]){
            dfs(x+moves[i].first,y+moves[i].second,sp);
        }
    }
}

int siz(pair<int,int>p1, pair<int,int>p2){
    return (p2.first-p1.first)*(p2.first-p1.first)+(p2.second-p1.second)*(p2.second-p1.second);
}
//0-woda, 1-ziemia
int main(){
    cin>>n;
    cin>>xs>>ys>>xm>>ym;
    for(int i=1;i<=n;i++){
        string pom; cin>>pom;
        for(int j=0;j<n;j++) mapa[i][j+1]= (pom[j]=='0');
    }
    dfs(xs,ys,sp1);
    if(vis[xm][ym]) cout<<0;
    else{
        dfs(xm,ym,sp2);
        int wyn=INT_MAX;
   //     cout<<sp1.size()<<" "<<sp2.size()<<"\n";
        for(int i=0;i<sp1.size();i++){
            for(int j=0;j<sp2.size();j++){
                if(wyn>siz(sp1[i],sp2[j])) wyn=siz(sp1[i],sp2[j]);
            }
        }
        cout<<wyn;
    }
}
