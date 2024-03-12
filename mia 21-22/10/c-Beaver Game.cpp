#include<iostream>
#define pb push_back
#define ll long long
using namespace std;

int n,m,k;
int x;
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>m>>k;

	if(m==1){
		cout<<"Marsel"; return 0;
	}

	if(!(n&1)) {cout<<"Marsel"; return 0;}
	if(1>=k) {
		cout<<"Timur";
		return 0;
	}

	for(int i=2;i*i<=m;i++){
		if(!(m%i)){
			x=m/i;
			if(x>=k or i>=k){
				cout<<"Timur"; return 0;
			}
		}
	}

	cout<<"Marsel";
	return 0;
}
