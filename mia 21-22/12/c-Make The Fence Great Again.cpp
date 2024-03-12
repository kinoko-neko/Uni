#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define ss second
#define ff first
using namespace std;
const int N=300005;
const ll inf=1000000000000000008LL;

int t[N];//wysokosci
ll k[N];//koszta
ll dp[N][3];

int n,q,a,b;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>q;
	while(q--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>t[i]>>k[i];
		}
		for(int i=1;i<=n;i++){
			for( int j=0;j<3;j++){
				dp[i][j]=inf;
				for(int i2=0;i2<3;i2++){
					if(t[i-1]+i2!=t[i]+j){
						dp[i][j]=min(dp[i][j],dp[i-1][i2]);
					}
				}
				dp[i][j]+=j*k[i];
			}
		}
		cout<<min(min(dp[n][0],dp[n][1]),dp[n][2])<<"\n";
	}
}
