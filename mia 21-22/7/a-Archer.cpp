#include<bits/stdc++.h>
#define ld long double
using namespace std;

ld p1,p2,w;
ld a,b,c,d;

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>a>>b>>c>>d;
	p1=a/b;
	p2=c/d;
	w=p1*(1/(1-((1-p1)*(1-p2))));
	cout<<fixed<<setprecision(7)<<w;
	return 0;
}
