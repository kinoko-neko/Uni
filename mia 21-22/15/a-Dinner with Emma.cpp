#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int inf=1000000099;

int n,m;

int wyn=0;

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>m;

	int a, pomi;

	for(int i=0;i<n;i++){
		pomi=inf;
		for(int j=0;j<m;j++){
			cin>>a;
			pomi=min(pomi,a);
		}
		wyn=max(wyn,pomi);
	}
	cout<<wyn;
	return 0;
}

