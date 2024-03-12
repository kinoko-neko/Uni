#include<bits/stdc++.h>
#define x0 first.first
#define x1 second.first
#define y0 first.second
#define y1 second.second
#define ll long long int
using namespace std;

pair<pair<ll,ll>, pair<ll,ll> >w,b1,b2,p1,p2,p3;

ll m(ll x){
    if(x<0) x=-x;
    return x;
}

ll pole(pair<pair<ll,ll>, pair<ll,ll> >x){
    return m((x.x1-x.x0)*(x.y1-x.y0));
}

pair<pair<ll,ll>, pair<ll,ll> > intersect(pair<pair<ll,ll>, pair<ll,ll> >x,pair<pair<ll,ll>, pair<ll,ll> >y){
    pair<pair<ll,ll>, pair<ll,ll> > res;
    if((x.x1<y.x0) || (y.x1<x.x0) || (x.y0>y.y1) || (y.y0>x.y1)){
        res.x0=0; res.x1=0; res.y0=0; res.y1=0;
    }
    else{
        res.x0=max(x.x0,y.x0);
        res.x1=min(x.x1,y.x1);
        res.y0=max(x.y0,y.y0);
        res.y1=min(x.y1,y.y1);
    }
    if(res.y1<=res.y0 || res.x1<=res.x0){
        res.x0=0; res.x1=0; res.y0=0; res.y1=0;
    }

    return res;
}

void wczyt(pair<pair<ll,ll>, pair<ll,ll> >&x ){
    cin>>x.x0>>x.y0>>x.x1>>x.y1;
}

void wyp(pair<pair<ll,ll>, pair<ll,ll> >x){
    cout<<x.x0<<" "<<x.y0<<" "<<x.x1<<" "<<x.y1<<"\n";
}

int main(){
    wczyt(w); wczyt(b1); wczyt(b2);
    p1=intersect(w,b1);
    p2=intersect(w,b2);
    p3=intersect(p1,p2);
    ll pom1=pole(w);
    ll pom2=pole(p1)+pole(p2)-pole(p3);
   // cout<<"spr\n";
  //  wyp(w);
  //  wyp(p1);
  //  wyp(p2);
  //  wyp(p3);
   // cout<<pom1<<" "<<pom2<<"\n";
    if(pom1>pom2) cout<<"YES";
    else cout<<"NO";
}
