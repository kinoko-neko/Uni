#include<bits/stdc++.h>
using namespace std;
const int N=1005;
bool vis[N];
int ret[N];
int t[N];

int pom;
bool p;

void dfs(int x){
    vis[x]=true;
    if(vis[t[x]]){
       if(ret[t[x]]==0){ ret[t[x]]=t[x];
        // ret[t[x]]=t[x];
      //  if(t[x]!=x){
            p=true;
            pom=t[x];
       // }
       }
    }
    else{
        dfs(t[x]);
    }
    if(p){
        if(pom==x) p=false;
        else ret[x]=x;
    }
    else ret[x]=ret[t[x]];
}

int main(){

    int n;
    cin>>n;

    for(int i=1;i<=n;i++) cin>>t[i];
    for(int i=1;i<=n;i++) {
        if(!vis[i]) dfs(i);
        cout<<ret[i]<<" ";
    }
}
