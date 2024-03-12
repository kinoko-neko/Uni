#include<bits/stdc++.h>
#define ff first
#define ss second
using namespace std;
const int N=100006;
int w[N];
int dep[N];
priority_queue<pair<int,int>, std::vector<pair<int,int> >, std::greater<pair<int,int> > >q;
vector<int>g[N];
queue<int>pomi;

int main(){

    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++) cin>>dep[i];
    while(m--){
        int a,b;
        cin>>a>>b;
        g[b].push_back(a);
        w[a]++;
    }
    for(int i=0;i<n;i++){
        if(w[i]==0) q.push({dep[i],i});
    }
    int wyn=0;
    while(!q.empty()){
        pair<int,int> y =   q.top(); q.pop();
    //    cout<<"asasaaaaa "<<y.ff<<" "<<y.ss<<"\n";
        if(y.ff==0){
            for(int i=0;i<g[y.ss].size();i++){
                w[g[y.ss][i]]--;
                if(w[g[y.ss][i]]==0) q.push({dep[g[y.ss][i]],g[y.ss][i]});
            }
        }
        else{
     //       cout<<"safafs: "<<y.ss<<"\n";
            wyn++;
            pomi.push(y.ss);
            while(!q.empty()){ pomi.push(q.top().ss); q.pop();} //przerzuć kolejke na wektor
            while(!pomi.empty()){//for(int i=0;i<pomi.size();i++){
                int x=pomi.front();
                pomi.pop();
                for(int j=0;j<g[x].size();j++){
                    w[g[x][j]]--;
                    if(w[g[x][j]]==0) if(dep[g[x][j]]==1) pomi.push(g[x][j]);  else q.push({dep[g[x][j]],g[x][j]});
                }
            }
           // pomi.clear();
        }
    }
    cout<<wyn;
}
