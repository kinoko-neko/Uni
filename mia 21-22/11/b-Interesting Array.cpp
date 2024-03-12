#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define ss second
#define ff first
using namespace std;
const int N=100005;
const ll inf=1000000000000000008LL;
const int neutral= (int) ((1LL<<31)-1);
int t[N*4];
int t2[N][32];

int n,m,base=1;
vector< pair< pair<int,int> ,int> >q;

void make_base(){
	while(base<n) base*=2;
}

void buduj(){
	for(int i=n+base;i<base*2;i++) t[i]=neutral;
	int wsk=base/2;
	while(wsk){
		for(int i=wsk;i<wsk*2;i++)
			t[i]=t[i*2]&t[(i*2)+1];
		wsk/=2;
	}
}

int ask(int a, int b, int x=1,int low=0, int high=base-1){
	if(a>b) return neutral;
	if(a==low && b==high) return t[x];
	int mid=(low+high)/2;
	return ask(a,min(mid,b),x*2,low,mid) & ask(max(a,mid+1),b, (x*2) +1 ,mid+1,high);
}

bool sprawdzaj(){
	for(int i=0;i<m;i++){
		if(ask(q[i].ff.ff,q[i].ff.ss)!=q[i].ss) return false;
	}
	return true;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>m;
	int a,b,c,pomi;
	for(int i=0;i<m;i++){
		cin>>a>>b>>c;
		q.pb({{a-1,b-1},c});
		pomi=0;
		for(int j=1;j<=c;j*=2){
			if(j&c){
				t2[a-1][pomi]++;
				t2[b][pomi]--;
			}
			pomi++;
		}
	}
	make_base();
	pomi=1;
	for(int j=0;j<32;j++){
		if(t2[0][j]) t[base]+=pomi;
		for(int i=1;i<n;i++){
			t2[i][j]+=t2[i-1][j];
			if(t2[i][j]) t[base+i]+=pomi;
		}
		pomi*=2;
	}
	buduj();
	if(sprawdzaj()){
		cout<<"YES\n";
		for(int i=base;i<base+n;i++) cout<<t[i]<<" ";
	}
	else cout<<"NO\n";
	return 0;
}
