#include<bits/stdc++.h>
#define pb push_back
#define ll long long
using namespace std;
const int N=200005;
const ll mod=1000000007;

int n,k;
int t[10];
ll ile;

void wczyt(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>k;
}

ll pot(ll x,int wyk){
	ll wyn=1;
	for(int i=0;i<wyk;i++){
		wyn*=x;
		if(wyn>mod) wyn%=mod;
	}
	return wyn;
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	wczyt();

	ll pom1=pot(k,k-1);
	ll pom2=pot(n-k,n-k);
	cout<<(pom1*pom2)%mod;
	return 0;
}
