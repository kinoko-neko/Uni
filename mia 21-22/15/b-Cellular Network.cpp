#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define ss second
#define ff first
using namespace std;
const int inf=2000000099;
const int N=100005;
int n,m;

int wyn=0;

int wynik[N];//odleglosc z lewej i odleglosc z prawej
int wieze[N];
int miasta[N];

void wczyt_tab(int t[], int roz){
	for(int i=0;i<roz;i++)
		cin>>t[i];
}

void wczyt(){
	cin>>n; cin>>m;
	wczyt_tab(miasta,n);
	wczyt_tab(wieze,m);
}

void wypisz(int t[],int siz){
	for(int i=0;i<siz;i++){
		printf("%d ",t[i]);
	}
	printf("\n");
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	wczyt();

	int wsk=0;
	for(int i=0;i<n;i++){
		if(wieze[wsk]>miasta[i]) { wynik[i]=inf; continue; }
		while( (wsk+1)<m && wieze[wsk+1]<=miasta[i]) wsk++; //dopóki wsk jest po lewej stronie miasta
		wynik[i]=miasta[i]-wieze[wsk];
	}
	//wypisz(wynik,n);

	wsk=m-1;
	for(int i=n-1;i>=0;i--){

		if(wieze[wsk]<miasta[i]) { wyn=max(wyn,wynik[i]); continue; }
		while( (wsk-1)>=0 && wieze[wsk-1]>=miasta[i]) wsk--;
		wyn=max(wyn,min(wynik[i],wieze[wsk]-miasta[i]));
	}
	cout<<wyn;
	return 0;
}

