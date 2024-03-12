#include<bits/stdc++.h>
#define pb push_back
#define ll long long
using namespace std;
const int N=100005;

int n,maxi;
vector<int>sec;
vector<int>prime[N];//dzielniki pierwsze i-tego elementu

bool sit[N];
int dp[N];
int dp2[N];

void dzielnikuj(int x){
	for(int i=0;i<n;i++){
		if(sec[i]%x==0) prime[i].pb(x);
	}
}

void ost_prime(){
	int pom1,pom2;
	for(int i=0;i<n;i++){
		pom1=sec[i];
		for(int j=0;j<prime[i].size();j++){
			pom2=prime[i][j];
			while(pom1%pom2==0){
				pom1/=pom2;
			}
		}
		if(pom1>1) prime[i].pb(pom1);
	}
}

void prep(){

//	if(sec[0]==1) dp2[1]=1;

	for(int i=0;i<n;i++){
	//	prime[i].pb(1);
		if(!(sec[i]&1)) prime[i].pb(2);
	}

	int j;
	int last_i=3;
	for(int i=3;i*i<=maxi;i+=2){
		last_i=i;
		if(!sit[i]){

			dzielnikuj(i);

			j=i*i;
			while(j*j<=maxi){
				sit[j]=true;
				j+=(i*2);
			}
		}
	}

	ost_prime();
	/*
	for(int i=last_i+2;i<=maxi;i+=2){
		if(!sit[i]){
			dzielnikuj(i);
		}
	}*/
}

void wczyt(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n;

	int a;
	for(int i=0;i<n;i++){
		cin>>a;
		maxi=max(a,maxi);
		sec.pb(a);
	}

}

void spr(){
	for(int i=0;i<n;i++){
		printf("%d:",sec[i]);
		for(int j=0;j<prime[i].size();j++){
			printf("%d,",prime[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	wczyt();

	/*
	if(n==1){
		cout<<1; return 0;
	}*/

	prep();
	int wyn=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<prime[i].size();j++){
			dp[i]=max(dp[i],dp2[prime[i][j]]+1);
		}
		if(dp[i]==0) dp[i]++;
		for(int j=0;j<prime[i].size();j++){
			dp2[prime[i][j]]=max(dp2[prime[i][j]],dp[i]);
		}
		wyn=max(wyn,dp[i]);
	}
	//spr();
	cout<<wyn;
	return 0;
}
