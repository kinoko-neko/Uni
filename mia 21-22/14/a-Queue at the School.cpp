#include<bits/stdc++.h>
using namespace std;
const int N=55;

int n,t;

int tab[N][2];

int akt,akt2;
string s;

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>t;
	cin>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='B') tab[i][0]=1; else tab[i][0]=0;
	}

	for(int i=0;i<t;i++){
		akt2=1-akt;
		tab[0][akt2]=tab[0][akt];
		for(int j=1;j<n;j++){

			if(tab[j-1][akt]>tab[j][akt]){
				tab[j][akt2]=tab[j-1][akt];
				tab[j-1][akt2]=tab[j][akt];
			}
			else{
				tab[j][akt2]=tab[j][akt];
			//	tab[j-1][akt2]=tab[j-1][akt];
			}

		}
		akt=akt2;
	}
	for(int i=0;i<n;i++){
		if(tab[i][akt]==0)
			cout<<'G';
		else
			cout<<'B';
	}
	return 0;
}
