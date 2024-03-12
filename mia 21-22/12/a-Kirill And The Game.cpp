#include<bits/stdc++.h>
#define pb push_back
#define para pair<pair<int,int>,int>
#define ss second
#define ff first
#define ll long long
using namespace std;
long long l,r,x,y,k,a1,b1;

bool bin(){//szuakm najwiekszego z że x<=z<=y i kz<=r
	ll w,lewy=x, prawy=y+1;
	while(lewy!=prawy-1){
		w=(lewy+prawy)>>1;
		if(k*w<=r) lewy=w; else prawy=w;
	}
	//printf("hakfhasdjkhjksdfhsd %lld \n",lewy);
	return (lewy*k)<=r && l<=(lewy*k);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>l>>r>>x>>y>>k;
	a1=l/k;
	b1=r/k;

	if(a1<=y && x<=b1){
		if(bin()) cout<<"YES";
		else cout<<"NO";
	}
	else cout<<"NO";

	return 0;
}
//4 4 1 2 3

