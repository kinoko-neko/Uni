#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
using namespace std;

const int N=10005;

int ojcz[N];
int kol[N];//jakie sa aktualnie

int n,smax;

void wczyt(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n;
	int a;
	for(int i=2;i<=n;i++){
		cin>>ojcz[i];
	}
	for(int i=1;i<=n;i++) cin>>kol[i];
}


int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	wczyt();
	int wyn=1;
	for(int i=2;i<=n;i++)
		if(kol[i]!=kol[ojcz[i]]) wyn++;

	cout<<wyn;
}
