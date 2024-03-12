#include<bits/stdc++.h>
#define pb push_back
#define ll long long
using namespace std;
const int N=200005;
const ll mod=1000000007;

vector<ll>v;
bool t[20];
ll x;

void dzielnikuj(ll x1){
	ll pom=1LL;
	while(!(x1&1)){
		pom<<=1;
		x1>>=1;

	}
	if(pom!=1LL) v.pb(pom);
	ll x2=x1;
	for(ll i=3;i*i<=x1;i+=2){
		if(x2%i==0){
			pom=1LL;
			while(x2%i==0){
				pom*=i;
				x2/=i;
			//	printf("jokl x1:%lld x2: %lld i:%lld\n",x1,x2,i);
			}
			v.pb(pom);
		}
	}
	if(x2>1) v.pb(x2);
}

ll mini;
ll w1,w2;
ll pom1,pom2;

void sprawdzaj(int x2){
	if(x2==v.size()){

		pom1=1; pom2=1;
		for(int i=0;i<x2;i++){
			if(t[i]){
			 	pom1*=v[i];
			}
			else{
				pom2*=v[i];
			}
		}
		if(mini>=max(pom1,pom2)){
			mini=max(pom1,pom2);
			w1=pom1;
			w2=pom2;
		}
	//	printf("dkalfj x2:%d\n",x2);
		return;
	}
	t[x2]=false; sprawdzaj(x2+1);
	t[x2]=true; sprawdzaj(x2+1);
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>x;
	dzielnikuj(x);
	mini=x;
	sprawdzaj(0);
	cout<<w1<<" "<<w2<<"\n";

	return 0;
}
