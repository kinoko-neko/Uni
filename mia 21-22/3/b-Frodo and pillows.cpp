#include<bits/stdc++.h>
#define pb push_back
#define ll long long
using namespace std;

int n,k;
ll m,pom,lewo,prawo;

ll ile(ll rzedy, ll pod){
	if(rzedy>pod-1){
		return (((pod*(pod-1))/2)+rzedy-pod+1);
	}
	else{
		return	((pod+pod-1-rzedy)*rzedy)/2;
	}
}

bool check(ll x){
	lewo=ile(k-1,x);
	prawo=ile(n-k,x);
	return (lewo+x+prawo)<=m;
}

ll bin(){
	ll w,lewy=1, prawy=m+1;

	while(lewy!=prawy-1){
		w=(lewy+prawy)>>1;
		if(check(w)) lewy=w; else prawy=w;
	}

	return lewy;
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>m>>k;
	cout<<bin();
	return 0;
}
