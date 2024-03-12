#include<bits/stdc++.h>
using namespace std;
const int N=105;

int n,m,wynik;

int t1[N];
int t2[N];

void wczyt(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n;
	for(int i=0;i<n;i++){
		cin>>t1[i];
	}

	cin>>m;
	for(int i=0;i<m;i++){
		cin>>t2[i];
	}
}

int mm(int x){
	if(x<0) return -x;
	return x;
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	wczyt();

	sort(t1,t1+n);
	sort(t2,t2+m);

	int wsk1=0,wsk2=0;

	while(wsk1<n && wsk2<m){
		if(mm(t1[wsk1]-t2[wsk2])<=1){
			wynik++;
			wsk1++; wsk2++;
		}
		else{
			if(t1[wsk1]<t2[wsk2]) wsk1++; else wsk2++;
		}
	}
	cout<<wynik;
	return 0;
}
