#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define ss second
#define ff first
using namespace std;
string s;
int a,b;
int n,k,wyn;

void f(char x){
	int l=0,rozne=0;
	for(int i=0;i<n;i++){
		if(s[i]!=x) rozne++;
		while(rozne>k && l<=i){
			if(s[l]!=x) rozne--;
			l++;
		}
		if(rozne<=k) wyn=max(wyn,i+1-l);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>k;
	cin>>s;
	f('a'); f('b');
	cout<<wyn;

}
