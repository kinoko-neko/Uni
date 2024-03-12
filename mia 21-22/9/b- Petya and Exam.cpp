#include<bits/stdc++.h>
#define pb push_back
#define ll long long
using namespace std;

string good,wzor,zap;
bool ok[27];
int gwiazdka=-1;
int n,m,t;
string pomi="c";
void prep(){
	for(int i=0;i<good.size();i++){
		ok[good[i]-'a']=true;
	}
}

void znajdz_gwiazdka(){
	for(int i=0;i<n;i++){
		if(wzor[i]=='*'){
			gwiazdka=i;
			return;
		}
	}
}

bool spr3(){
	for(int i=gwiazdka; i<=m-(n-gwiazdka);i++){
		if(ok[zap[i]-'a']) return false;
	}
	return true;
}

bool spr2(){
	for(int i=1;i<n-gwiazdka;i++){
		if(wzor[n-i]=='?'){
			if(!ok[zap[m-i]-'a']){
				return false;
			}
		}
		else{
			if(wzor[n-i]!=zap[m-i]){
				return false;
			}
		}
	}
	return true;
}

bool spr(int a, int b){

	for(int i=a;i<b;i++){
		if(wzor[i]=='?'){
			if(!ok[zap[i]-'a']){
				return false;
			}
		}
		else{
			if(wzor[i]!=zap[i]){
				return false;
			}
		}
	}
	return true;
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>good;
	cin>>wzor;
	n=wzor.size();

	znajdz_gwiazdka();
	prep();

	cin>>t;
	while(t--){
		cin>>zap;
		m=zap.size();
		if(gwiazdka>=0){
			if(zap.size()<n-1){
				cout<<"NO\n"; continue;
			}
			if(spr(0,gwiazdka) & spr2()){
				if(spr3()) {
					cout<<"YES\n";
				}
				else cout<<"NO\n";
				continue;
			}
			else{
		//		if(!spr(0,gwiazdka)) cout<<"jdsflajdfiosajg "<<gwiazdka<<"\n";
				cout<<"NO\n"; continue;
			}
		}
		else{
			if(zap.size()!=n){
				cout<<"NO\n"; continue;
			}
			if(spr(0,n)) {
				cout<<"YES\n";
			}
			else cout<<"NO\n";
			continue;
		}
	}
	return 0;
}
