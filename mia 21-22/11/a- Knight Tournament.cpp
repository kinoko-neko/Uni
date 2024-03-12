#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define ss second
#define ff first
using namespace std;
const int N=300005;
set<int>zywi;
int n,m,a,b,c,akt;
int t[N];

vector<int>yeet;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++) zywi.insert(i);
	for(int i=0;i<m;i++){
		cin>>a>>b>>c;

		set<int>::iterator it=zywi.lower_bound(a);
		while(it!=zywi.end()){
			akt= *it;
			if(akt>b) break;
			if(akt!=c && t[akt]==0) {yeet.pb(akt); t[akt]=c;}
			it++;
		}

		while(!yeet.empty()){
			zywi.erase(yeet.back());
			yeet.pop_back();
		}
	}

	for(int i=1;i<=n;i++){
		cout<<t[i]<<" ";
	}
}
