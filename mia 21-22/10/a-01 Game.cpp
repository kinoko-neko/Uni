#include<bits/stdc++.h>
#define ld long double
using namespace std;

string s;
int t;

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>t;
	while(t--){
		cin>>s;
		int zera=0,jedynki=0;
		for(int i=0;i<s.size();i++){
			if(s[i]=='0') zera++;
			else jedynki++;
		}
		if(min(jedynki,zera)&1) cout<<"DA\n";
		else cout<<"NET\n";
	}
	return 0;
}
