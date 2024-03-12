#include<bits/stdc++.h>
#define ff first
#define ss second
using namespace std;

map<pair<int,int>,int>m;
pair<int,int> t[120];
vector<int>g[120];
bool vis[120];
int dst;
bool wyn;
void dfs(int x){
    if(wyn) return;
    vis[x]=true;
    for(int i=0;i<g[x].size();i++){
        if(!vis[g[x][i]]){
            if(g[x][i]==dst) wyn=true;
            else dfs(g[x][i]);
        }
    }

}

int num=1;
int main(){
    int n;

    cin>>n;
    while(n--){
        int a,b,c;
        cin>>a>>b>>c;
        if(a==1){
            t[num]={b,c};
            m[{b,c}] = num; //num++;
            for(int i=1;i<num;i++){
                if( (b<t[i].ff && c>t[i].ff) || (b<t[i].ss && t[i].ss<c)){
                    //g[num].push_back(i);
                    g[i].push_back(num);
                }
                if(( t[i].ff<b && b<t[i].ss) || (t[i].ff<c && c<t[i].ss)) g[num].push_back(i);
            }
            num++;
        }
        else{
            for(int i=1;i<num;i++) vis[i]=false;
            dst=c; wyn=false;
            dfs(b);
            if(wyn) cout<<"YES\n"; else cout<<"NO\n";
        }
    }
}
