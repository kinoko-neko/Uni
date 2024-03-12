#include<bits/stdc++.h>
using namespace std;
const int N=200005;

int t1[N];
int t2[N];

int n;

//ile potionow, aktualna pozycja, i gdzie koncze predkosc
long long r,l,t,akt,akttime,potiony,pom,pom2,power;
vector<long long>pozycje;

long long pom3;
void yo_potion(){

	pom2=l-(t-l);//droga z potionem, (t-l) droga bez potiona

	pom=pom2/r;
	if(pom*r<pom2) pom++;
	potiony+=pom;	//ile potionow wypije

	power=pom*r-pom2;

	if(potiony<=100000){
		akttime+=(t-l)*2;
		pom3=akttime;
		for(int j=0;j<pom;j++){
			pozycje.push_back(pom3);
			pom3+=r;
		}
	}

	akttime+=pom2;
}


void roz(){

	if(power){
		long long pomi=l;
		l-=power;
		t-=power;
		akttime+=min(power,pomi);
		power-=min(power,pomi);
	}
	if(power) return;

	if(t>=2*l) {
		akttime+=2*l;
		return;
	}

	return yo_potion();
}


void wczyt(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	for(int i=0;i<n;i++){
		cin>>t1[i];
	}

	for(int i=0;i<n;i++){
		cin>>t2[i];
	}
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>r;

	wczyt();

	//printf("eeeee %d %lld\n" ,n,r);

	for(int i=0;i<n;i++){
		l=(long long)t1[i];
		t=(long long)t2[i];

		if(l>t){
			cout<<"-1"; return 0;
		}
		roz();
	}

	cout<<potiony<<"\n";
	if(potiony<=100000){
		for(int i=0;i<pozycje.size();i++){
			cout<<pozycje[i]<<" ";
		}
	}

	return 0;
}

/*
1 127635961043
2569599
5030359
*/
