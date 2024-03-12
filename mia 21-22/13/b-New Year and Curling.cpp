#include<bits/stdc++.h>
#define pb push_back
#define para pair<pair<int,int>,int>
#define ss second
#define ff first
#define ll long long
using namespace std;

long double v[1005];//dla każdego x trzyma najwyższy y

int n;
ll r,x;
long double maxy;

long double policzy(int i){
	ll pom=4*r*r;
	ll pom2=(x-i)*(x-i);
	pom-=pom2;
	long double pom4=sqrt(pom);
	return pom4+v[i];
}

long double r2;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>r;
	r2=(long double)r;

	for(int j=0;j<n;j++){
		cin>>x;
		maxy=r2;

		int pomi=x;

		for(int i=max(1LL,x-r*2);i<=min(1000LL,x+r*2);i++){//wszytkie miejsca gdzie mogą być koło do styku
			if(v[i]>0.5){
			//	long double pom2=policzy(i);
				//if(pom2>maxy) pomi=i;
				maxy=max(maxy,policzy(i));
			}
		}
		v[x]=maxy;
		cout<<fixed<<setprecision(9)<<maxy<<" ";
	}

	return 0;
}
//4 4 1 2 3

