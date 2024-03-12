#include<bits/stdc++.h>
#define ll long long int
using namespace std;
const int N=100005;
int n,k,m;

int t[N];
ll cost[N];
map<string,int>mapa;

int f(int x){
    if(t[x]!=x){
        t[x]=f(t[x]);
    }
    return t[x];
}

void un(int a, int b){
    a=f(a); b=f(b);
    if(cost[a]>cost[b]) t[a]=b;
    else t[b]=t[a];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>k>>m;
    string s;
    for(int i=1;i<=n;i++){
        t[i]=i;
        cin>>s;
        mapa[s]=i;
    }
    for(int i=1;i<=n;i++) cin>>cost[i];
    while(k--){
      int a,b,c;
      cin>>a>>b;
      for(int i=1;i<a;i++){
            cin>>c;
            un(b,c);
      }
    }
    ll wyn=0;
    for(int i=0;i<m;i++){
        cin>>s;
        wyn+=cost[f(mapa[s])];
    }
    cout<<wyn;

}
