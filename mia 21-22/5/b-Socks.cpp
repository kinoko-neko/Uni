#include<bits/stdc++.h>
#define pb push_back
#define ll long long
using namespace std;
const int N=200005;

int n,m,k;
vector<int>g[N];
vector<int>pom,pusty;

int ile[N];
int kol[N];
bool odw[N];
int maxi,siz,wyn;

void dfs(int x){
	if(ile[kol[x]]==0) pom.pb(kol[x]);
	ile[kol[x]]++;
	maxi=max(maxi,ile[kol[x]]);
	siz++;

	odw[x]=true;
	for(int i=0;i<g[x].size();i++){
		if(!odw[g[x][i]]) dfs(g[x][i]);
	}
}

void clearowanie(){
	for(int i=0;i<pom.size();i++){
		ile[pom[i]]=0;
	}
	pom=pusty;
}

void wczyt(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) cin>>kol[i];

	int a,b;

	while(m--){
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

	for(int i=1;i<=n;i++){
		if(!odw[i]){
			maxi=0; siz=0;
			dfs(i);
			wyn+=siz-maxi;
			clearowanie();
		}
	}

	cout<<wyn;
	return 0;
}
