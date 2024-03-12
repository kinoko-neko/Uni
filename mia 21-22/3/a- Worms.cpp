#include<bits/stdc++.h>
using namespace std;

int t[1000006];

int n,a,q=1;

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		while(a--){
			t[q]=i;
			q++;
		}
	}
	cin>>n;
	while(n--){
		cin>>a;
		cout<<t[a]<<"\n";
	}
}
