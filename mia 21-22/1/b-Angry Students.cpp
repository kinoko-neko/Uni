#include<bits/stdc++.h>
#define ll long long
using namespace std;


/*
void wczyt(){


	cin>>n;

	for(int i=0;i<n;i++)
		cin>>t[i][0]>>t[i][1]>>t[i][2];
}
*/
int wyn=0;

int t,n,ost=0;
char a;
int main(){

	//wczyt();
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a;
			if(a=='P'){
				if(ost) wyn=max(wyn,i-ost);
			}
			else ost=i;
		}
		cout<<wyn<<"\n"; wyn=0; ost=0;
	}

}
