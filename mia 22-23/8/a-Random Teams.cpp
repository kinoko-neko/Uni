#include<bits/stdc++.h>
 using namespace std;

long long int komb(long long int x){
    if(x%2==1) return ((x-1)/2)*x;
    return (x/2)*(x-1);
}

int main(){
    long long int n,m,w1,w2,pom;
    long long int r;
    cin>>n>>m;
    r=n%m;

    pom=n-m+1;
    if(pom%2==1) w2= pom*((pom-1)/2); else w2=(pom/2)*(pom-1);
    w2=komb(pom);
    w1=r*komb((n/m)+1)+(m-r)*komb(n/m);

    cout<<w1<<" "<<w2;
}
