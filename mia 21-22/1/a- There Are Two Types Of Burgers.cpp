#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n,a,b,c,c1,c2;
/*
void wczyt(){


	cin>>n;

	for(int i=0;i<n;i++)
		cin>>t[i][0]>>t[i][1]>>t[i][2];
}
*/
int wyn;
int main(){

	//wczyt();
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n;
	while(n--){
		cin>>a>>b>>c;
		cin>>c1>>c2;
		if(c1<c2){
			swap(c1,c2); swap(b,c);
		}
		a>>=1;
		if(b>a){
			wyn=a*c1; a=0;
		}
		else{
			wyn=b*c1; a-=b;
		}
	//	printf("%d %d %d %d %d %d\n",a,b,c,c1,c2,wyn);
		wyn+=min(a,c)*c2;
		cout<<wyn<<"\n";
	}

}
