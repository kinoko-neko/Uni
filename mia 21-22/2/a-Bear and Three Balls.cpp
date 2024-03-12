#include<bits/stdc++.h>
using namespace std;

bool t[1005];

int n,a;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n;

	while(n--){
		cin>>a;
		t[a]=true;
	}

	for(int i=2;i<1000;i++){
		if(t[i-1] && t[i] && t[i+1]){
			cout<<"YES"; return 0;
		}
	}
	cout<<"NO"; return 0;
}
