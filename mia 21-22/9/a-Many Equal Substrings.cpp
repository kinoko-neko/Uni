#include<bits/stdc++.h>
using namespace std;
string s1,s2;

int n,k;
int t[150];

int z(){
	int r=0,l=0;

	for(int i=1;i<n;i++){
		if(i<=r){
			t[i]=min(t[i-l],r+1-i);
		}
		while(t[i]+i<n && s2[t[i]]==s2[t[i]+i]){
			t[i]++;
		}
		if(t[i]+i-1>r ){
			l=i; r=t[i]+i-1;

		}
		if (r==n-1) return i;

	}
	return n;
}

int pom;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);


	cin>>n>>k;
	cin>>s1;

	s2=s1;

	cout<<s1;
	k--;
	pom=z();
	//cout<<pom<<" jkalf\n";
	while(k--){
		for(int i=n-pom;i<n;i++){
			cout<<s1[i];
		}
	}

	return 0;

}


