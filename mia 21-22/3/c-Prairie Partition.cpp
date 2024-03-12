#include<bits/stdc++.h>
using namespace std;
const int N=50;

int pot[N];
int potmin[N];
int mn[N]; //mn[i] = ile jest a że a<=2^i
int mn2[N];
int ile[N];//ile łańcuchów że max el to 2^i

int n,len;
int wsk_pot=-1, wsk_mn=-1;

void wypisz2(int t[], int siz){
	for(int i=0;i<siz;i++){
		cout<<t[i]<<" ";
	}
	cout<<"\n";
}

bool dopisanie(){
	int wsk1=len;

	for(int j=max(wsk_pot,wsk_mn);j>=0;j--){
		while(mn2[j]){
			if(j>wsk1) return false;

			if(ile[wsk1]>=mn2[j]){
				ile[wsk1]-=mn2[j]; mn2[j]=0;
			}
			else{
				mn2[j]-=ile[wsk1];
				wsk1--;
			}
		}
	}
	return true;
}

int temp9;
int lancuchuj(int m){
	int akt=0,len2=0;
	for(int i=wsk_pot;i>=0;i--){
		temp9=min(m,potmin[i]);
		if(akt<temp9){
			ile[i]=temp9-akt;
			akt=temp9;
			len2=max(len2,i);
		}
		else ile[i]=0;

		mn2[max(0,i-1)]+=pot[i]-akt;
	}
	return len2;
}

void prep(){
	for(int i=0;i<N;i++) mn2[i]=mn[i];
}

bool czy_lancuch(int m){
	prep();

	len=lancuchuj(m);//tworzy jak najdluższe m łańcuchow
	/*if(m==1){
		cout<<"m=1 jasfkl\n";
		wypisz2(ile,4);
		cout<<"ijaofld\n";
	}*/
	return dopisanie();
}

void make_pot(){
	potmin[0]=pot[0];
	for(int i=1;i<=wsk_pot;i++) potmin[i]=min(potmin[i-1],pot[i]);
}

void wczyt(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n;

	long long temp;
	bool czy_pot;
	int licznik;

	for(int i=0;i<n;i++){
		cin>>temp;

		czy_pot=true; licznik=-1;

		while(temp){
			if(temp&1 && temp!=1) czy_pot=false;
			licznik++;
			temp>>=1;
		}

		if(czy_pot) {
			pot[licznik]++;
			wsk_pot=max(wsk_pot,licznik);
		}
		else {
			mn[licznik]++;
			wsk_mn=max(licznik,wsk_mn);
		}

	}
}

bool ok;
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	wczyt();
	make_pot();
	/*
	wypisz2(pot,4);
	wypisz2(mn,4);
	wypisz2(potmin,4);
	*/
	for(int i=1;i<=min(n,pot[0]);i++){
		if(czy_lancuch(i)) {
			cout<<i<<" ";
			ok=true;
		}
	}

	if(!ok) cout<<"-1";

	return 0;
}

