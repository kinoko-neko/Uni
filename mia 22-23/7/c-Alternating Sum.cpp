#include<bits/stdc++.h>
#define ll long long int
using namespace std;
const ll m=1000000009LL;

ll pot(ll x, int y){
    if(y==0) return 1LL;
    if(y==1) return x%m;
    ll pomi = pot(x,y/2);
    pomi*=pomi; pomi%=m;
    if(y%2==0) return pomi;
    return (pomi*x)%m;
}

ll odw(ll x){
    return pot(x,m-2);
}

ll geo(ll a1, ll q, ll n){
    if(q==1) return (a1*n)%m;
    return ( ((a1*((pot(q,n)-1+m)%m) )%m)* odw((q+m-1)%m))%m;
}

string s;
int main(){

    ll n,k,a,b;
    cin>>n>>a>>b>>k; cin>>s;
    ll q=pot(b,k)*odw(pot(a,k)); q%=m;
    ll wyn=0;
    for(int i=1;i<=k;i++){
        if(s[i-1]=='+'){
            wyn+=geo((pot(a,n+1-i)*pot(b,i-1))%m,q,(n+1)/k); wyn%=m;
        }
        else{
            wyn-=geo((pot(a,n+1-i)*pot(b,i-1))%m,q,(n+1)/k); wyn+=m; wyn%=m;
        }
    }
    wyn+=m; wyn%=m;
    cout<<wyn;
}
