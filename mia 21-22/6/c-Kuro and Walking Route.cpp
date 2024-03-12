#include<bits/stdc++.h>
#define pb push_back
#define ll long long
using namespace std;
const int N=300005;

int x,y;
ll n;
ll ile;
vector<int>g[N];
ll roz[N];

bool dfs(int v, int ojcz){
	bool pomi=(v==x);
	roz[v]=1;
	for(int i=0;i<g[v].size();i++){
		if(ojcz!=g[v][i]){
			pomi|=dfs(g[v][i],v);
			roz[v]+=roz[g[v][i]];
		}
	}
	if(pomi && v!=y) ile=roz[v];
	return pomi;
}


void wczyt(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int a,b;

	cin>>n>>x>>y;

	for(int i=1;i<n;i++){
		cin>>a>>b;
		g[a].pb(b);
		g[b].pb(a);
	}
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	wczyt();
	dfs(y,0);
	ll wszystkie=(n*(n-1));
	ll zajete=roz[x]*(n-ile);
	//printf("wszystkie: %lld zajęte: %lld ile: %lld roz[x]: %lld\n",wszystkie,zajete,ile,roz[x]);
	cout<<wszystkie-zajete;
	return 0;
}
