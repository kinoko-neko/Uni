#include<bits/stdc++.h>
#define ld long double
using namespace std;

int nwd(int a, int b){
	if(b==0) return a;
	return nwd(b,a%b);
}
int a,d,maxi,t;
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>t;
	cin>>maxi;
	d=maxi;

	for(int i=1;i<t;i++){
		cin>>a;
		maxi=max(maxi,a);
		d=nwd(d,a);
	}
	if(((maxi/d)-t)&1)
		cout<<"Alice";
	else cout<<"Bob";
	return 0;
}
