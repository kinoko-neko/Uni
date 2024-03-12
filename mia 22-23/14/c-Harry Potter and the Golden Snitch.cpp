#include<bits/stdc++.h>
#define x first.first
#define y first.second
#define z second
#define poz pair<pair<long double,long double>,long double>
using namespace std;

poz t[10005];
long double dst[10005];
int n;
poz start;
long double vz,vh;

long double odl(poz p1, poz p2){
    long double a=(p1.x-p2.x),b=(p1.y-p2.y),c=(p1.z-p2.z);
    return sqrt( a*a + b*b +c*c );
}


bool check1(poz cel,long double sz){
    long double sh=odl(start,cel);
    return (sz/vz)>= (sh/vh);
}

int bin1(){//zakladam ze sie da wybrac segment
    int l=0,p=n-1;
    int w=(l+p)/2;
    while(l!=p){
        if(check1(t[w+1],dst[w+1])) p=w; else l=w+1;
        w=(l+p)/2;
    }
    return l;
}

void bin2(int odc){
    cout << fixed << setprecision(15);
    poz l=t[odc],p=t[odc+1]; poz w;
    while(odl(l,p)>=0.0000001){
        w.x=(l.x+p.x)/2; w.y=(l.y+p.y)/2; w.z=(l.z+p.z)/2;
        if(check1(w,dst[odc]+odl(t[odc],w))) p=w; else l=w;
    }
    long double t=odl(start,l)/vh;
    cout<<t<<"\n"<<l.x<<" "<<l.y<<" "<<l.z;
}

int main(){


    cin>>n;
    cin>>t[0].x>>t[0].y>>t[0].z;
    for(int i=1;i<=n;i++){
        cin>>t[i].x>>t[i].y>>t[i].z;
        dst[i]=dst[i-1]+odl(t[i-1],t[i]);
    }
    cin>>vh>>vz;
    cin>>start.x>>start.y>>start.z;

    if(!check1(t[n],dst[n])) cout<<"NO";
    else{
        cout<<"YES\n";
        int segment=bin1();
     //   cout<<"ten segment "<<segment<<" check1() "<<(int)check1(t[3],)<<"\n";
        bin2(segment);
      //  poz wyn=bin2(segment);
    }
}
/*
4
0 0 0
0 1 0
1 1 0
1 0 0
0 0 0
10 5
0 0 8
*/
