#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll wyn(ll x, ll y){
	ll wyn;
	if(x&1){
		wyn=(x+1)>>1;
		wyn*=(y+1)*(y+x);
	}
	else {
		if(y&1){
			wyn=(y+1)>>1;
			return wyn*=(x+1)*(y+x);
		}
		else{
			wyn=(x+y)>>1;
			wyn*=(x+1)*(y+1);
		}
	}
	//printf("%lld %lld %lld\n",x,y,wyn);
	return wyn;
}

ll m,b,best;

ll dej_y(ll x){
	if(x%m!=0)x=-(x/m)-1;
	else x/=-m;
	return x+b;
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>m>>b;

	for(int i=0;i<=b*m;i++)
		best=max(best,wyn(i,dej_y(i)));

	cout<<best;
}
