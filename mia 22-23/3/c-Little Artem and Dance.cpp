#include<bits/stdc++.h>
#define ll long long int
using namespace std;

int t[1000006];


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n,q;
    cin>>n>>q;
    int typ;
    ll a;

    ll d=0;
    ll p=0;
    ll np=0;
    bool m=true;

    while(q--){
        cin>>typ;
        if(typ==1){
            cin>>a;
            d+=a;
            if(abs(a%2)==1) m=!m;
            if(d>=n || d<-n) d%=n;
        }
        else{
            if(m){
                np++;
                p--;
            }
            else{
                p++;
                np--;
            }
            m=!m;
        }
  //      cout<<"parity "<<(int )m<<"\n";
    }
    ll pom;
  //  cout<<"fds "<<d<<" "<<p<<" "<<np<<"\n";
    for(int i=1;i<=n;i+=2){
        pom=(d+np+i)%n;
        while(pom<=0) pom+=n;
        t[(int)pom]=i;
    }
    for(int i=2;i<=n;i+=2){
        pom=(d+p+i)%n;
        while(pom<=0) pom+=n;
        t[(int)pom]=i;
    }
    for(int i=1;i<=n;i++) cout<<t[i]<<" ";
   // cout<<"mod "<<(-5)%2;
}
