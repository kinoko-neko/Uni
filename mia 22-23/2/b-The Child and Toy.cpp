#include<bits/stdc++.h>
using namespace std;
const int N=1005;

int val[N];
int cost[N];
int cont[N];
int con[N];
vector<int>g[N];
priority_queue<pair<int,int> >q;

int main(){


    int n,m;
    cin>>n>>m;

    int a,b;
    for(int i=1;i<=n;i++) cin>>val[i];
    for(int i=0;i<m;i++){
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
        cost[a]+=val[b];
        cost[b]+=val[a];
        con[a]++;
        con[b]++;
    }

    for(int i=1;i<=n;i++) q.push({val[i],i});
    long long wyn=0;
    pair<int,int>temp;

    if(n==1){
        cout<<0;
        return 0;
    }
    while(n>0){
        n--;
        temp=q.top(); q.pop();
    //    cout<<temp.first<<" "<<temp.second<<" jdfaf\n";
        if(val[temp.second]!=-1 && con[temp.second]!=0){

            wyn+=cost[temp.second];
         //   n--;
            for(int i=0;i<g[temp.second].size();i++){
                con[g[temp.second][i]]--;
            //    if(con[g[temp.second][i]]==0) n--;
                cost[g[temp.second][i]] -= val[temp.second];
            }
            val[temp.second]=-1;
        }
    }
    cout<<wyn;
    return 0;
}
