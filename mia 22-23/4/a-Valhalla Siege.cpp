#include<bits/stdc++.h>
#define ll long long int
using namespace std;

ll t[200005];
int pocz=0;
int n,q;
ll k,akt;

int bin(){
    int l=pocz; int p=n+1; int w; //l jest zawsze martwy

    while(l!=p-1 ){
        w=(l+p)/2;
        if(t[w]>akt) p=w; else l=w;
    }
    return p;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>q;
    cin>>t[1];
    for(int i=2;i<=n;i++) {cin>>t[i]; t[i]+=t[i-1];}
  //  for(int i=0;i<=n;i++) cout<<t[i]<<" "; cout<<"\n";
    t[n+1]=INT_MAX;
    int st;
    while(q--){
        cin>>k;
        akt+=k;
        st=bin();
        if(st==n+1){
            cout<<n<<"\n"; akt=0;
            pocz=0;
        }
        else {
            cout<<n+1-st<<"\n";
            pocz=st-1;
        }
    }
}
