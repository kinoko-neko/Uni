#include<bits/stdc++.h>
#define ff first
#define ss second
using namespace std;

int wart[100005];// lista dziór
int num[100005];

int fin(int a){
    if(num[a]==a) return a;
    return fin(num[a]);
}

void un(int a, int b){
    num[fin(a)]=fin(b);
}

vector<pair<int,pair<int,int> > >v; // odl z a do b; a; b;

int n,m,k;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m>>k;
    for(int i=0;i<=n;i++) num[i]=i;

    wart[0]=-1000000009;
    int n2=n;
    int wyn=n;
    for(int i=1;i<=n;i++){
        cin>>wart[i];
        v.push_back({wart[i]-wart[i-1]-1,{i-1,i}});
    }
    sort(v.begin(),v.end());
    int wsk=0;
    while(n2!=k){
        if(fin(v[wsk].ss.ff)!=fin(v[wsk].ss.ss)){
            wyn+=v[wsk].ff;
            un(v[wsk].ss.ff,v[wsk].ss.ss);
            n2--;
        }
        wsk++;
    }
    cout<<wyn;
    return 0;
}
