#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define ss second
#define ff first
using namespace std;
const int inf=2000000099;
const int N=500008;
int n,mini,mini1,maxi1,maxi,a,k;

int t[N];

bool czy_max(int x){
	ll   pomi=0;
	for(int i=0;i<n;i++){
		pomi+=max(0,t[i]-x);
	}
	return pomi<=k;
}


ll suma,sr;

bool czy_min(int x){
	ll pomi=0;
	for(int i=0;i<n;i++){
		pomi+=max(0,x-t[i]);
	}
	return pomi<=k;
}

int szukaj_min(){
	int licznik=0;
	int w,lewy=mini1, prawy=min(mini1+k,(int)(sr))+1;
	while(lewy < prawy-1){
		w=(int)(((ll)lewy+(ll)prawy)/2LL);
	/*	if(n>200){
			printf("%d %d %d\n",lewy,w,prawy);
		}
		licznik++;
		if(licznik>6 && n>200) return 0;*/
		if(czy_min(w)) lewy=w; else prawy=w;
	}
	return lewy;
}

int szukaj_max(){
	int w,lewy=sr, prawy=maxi1;
	if(sr*n!=suma) lewy++;
	lewy=max(lewy,prawy-k);

	//cout<<lewy<<" asd "<<prawy<<"\n";
	while(lewy!=prawy){
		w=(int)(((ll)lewy+(ll)prawy)/2LL);
		if(czy_max(w)) prawy=w; else lewy=w+1;
	}
	return lewy;
}

void wypisz(){
	for(int i=0;i<n;i++) cout<<t[i]<<" ";
	cout<<"\n";
}
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);


	cin>>n>>k;
	cin>>t[0]; mini1=t[0]; maxi1=t[0]; suma=t[0];
	for(int i=1;i<n;i++) { cin>>t[i]; suma+=t[i]; mini1=min(mini1,t[i]); maxi1=max(maxi1,t[i]);}
//	sort(t,t+n);

	sr=suma/n;/*
	if(n>200){
		mini=szukaj_min();
		cout<<mini;
		return 0;
	}*/
	mini=szukaj_min();
	maxi=szukaj_max();
	//wypisz();
	//printf("sa %d %d\n",t[0],t[n-1]);
	//cout<<mini<<" "<<maxi<<" "<<maxi-mini;
	cout<<maxi-mini;
	return 0;
}


