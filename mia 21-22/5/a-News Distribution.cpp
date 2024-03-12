#include<bits/stdc++.h>
using namespace std;

int n,m;

int f[500005];

int ile[500005];

void prep(){
	for(int i=1;i<=n;i++) f[i]=i;
}

int fin(int x){
	if(f[x]!=x) f[x]=fin(f[x]);
	return f[x];
}

void un(int a, int b){
	a=fin(a); b=fin(b);
	f[a]=b;
}

int a1,a2,k;
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>m;
	prep();
	while(m--){
		cin>>k;
		if(k){
			cin>>a1; k--;
		}
		while(k--){
			cin>>a2; un(a1,a2); a1=a2;
		}
	}
	for(int i=1;i<=n;i++) fin(i);
	for(int i=1;i<=n;i++) ile[f[i]]++;
	for(int i=1;i<=n;i++) cout<<ile[f[i]]<<" ";
	return 0;
}
