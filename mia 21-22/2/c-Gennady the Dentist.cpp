#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n,wyn,wsk;
ll bieg,krzyk;

ll t[4004][3];//darcie mordy, darcie-mordy-bieg,confidence
vector<int>gowniaki;

void dziecko(int x){
	gowniaki.push_back(x+1);
	wyn++;//dodaj do wyniku bo dziecko rozważone
	krzyk=t[x][0]; bieg=0;
	wsk=x+1;
	while(krzyk && wsk<n){
		if(t[wsk][2]>=0){
			t[wsk][2]-=(krzyk+bieg); krzyk--;
			if(t[wsk][2]<0) bieg+=t[wsk][1];
		}
		wsk++;
	}
	while(wsk<n){
		if(t[wsk][2]>=0){
			t[wsk][2]-=bieg;
			if(t[wsk][2]<0) bieg+=t[wsk][1];
		}
		wsk++;
	}
}

void wczyt(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n;

	for(int i=0;i<n;i++)
		cin>>t[i][0]>>t[i][1]>>t[i][2];
}

int main(){

	wczyt();

	for(int i=0;i<n;i++){
		if(t[i][2]>=0) dziecko(i);
	}

	cout<<wyn<<"\n";
	for(int i=0;i<gowniaki.size();i++)
		cout<<gowniaki[i]<<" ";
}
