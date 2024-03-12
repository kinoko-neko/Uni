#include<bits/stdc++.h>
#define pb push_back
using namespace std;

string sec;
bool ok;
char v1,v2;
char pom;
int n;

bool spr(int i){
	pom='0'+i;
	v1 = 'a';
	v2 = 'a';
	//printf("no nie %c\n",pom);
	for(int j=0;j<n;j++){
		if(sec[j]<pom){
			if(v1!='a'){
				if(v1>sec[j]) return false;
			}
			v1=sec[j];
		}
		if(sec[j]>pom){
			if(v2!='a'){
				if(v2>sec[j]) return false;
			}
			v2=sec[j];
		}
		if(sec[j]==pom){
			if(v2=='a' or v2==pom) v2=sec[j];
			else{
				if(v1>sec[j]) return false;
				v1=sec[j];
			}
		}
	}
	return true;
}

void wypisz(int i){
	ios_base::sync_with_stdio(0);
	cout.tie(0);

	bool pomi=true;
	pom='0'+i;

	for(int j=0;j<n;j++){
		if(sec[j]<pom){
			cout<<'1';
		}
		if(sec[j]>pom){
			cout<<'2';
			pomi=false;
		}
		if(sec[j]==pom){
			if(pomi) cout<<'2';
			else{
				cout<<'1';
			}
		}
	}
	cout<<"\n";
}

int t;
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>t;
	while(t--){
		ok=false;

		cin>>n;
		cin>>sec;

		for(int i=0;i<10;i++){
			if(spr(i)){
	//			printf("pokposakdf: %d\n",i);
				wypisz(i);
				ok=true;
				break;
			}
		}
		if(!ok){
			cout<<"-\n";
		}
	}
	return 0;
}
