#include<bits/stdc++.h>
#define pb push_back
#define para pair<pair<int,int>,int>
#define ss second
#define ff first
#define ll long long
using namespace std;

ll r,rs,d,ri,x,y,d2;
int n,wyn;

bool war1(){
	return ( (rs+ri)*(rs+ri) )<=d2;
}

bool war2(){
	return d2<=( (r-ri)*(r-ri) );
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);


	cin>>r>>d;
	cin>>n;

	rs=r-d;

	while(n--){
		cin>>x>>y>>ri;
		d2=x*x+y*y;
		if(war1() && war2()) wyn++;
	}

	cout<<wyn;
	return 0;
}
//4 4 1 2 3

