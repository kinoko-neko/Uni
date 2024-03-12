#include<bits/stdc++.h>
#define ll long long int
using namespace std;

int main(){

    ll m,n;
    cin>>m>>n;

    ll wyn=0;
    bool sk=false;
    for(int i=1;i*i<=n && i<=m;i++){
        if(i*i==n) sk=true;
        ll pom=n/i;
        if(pom<=m && pom*i==n) wyn++;
    }
    wyn*=2;
    if(sk) wyn--;
    cout<<wyn;
    return 0;
}
