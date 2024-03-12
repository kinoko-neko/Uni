#include<bits/stdc++.h>
using namespace std;
const int N= 500005;
int t[N*4];
int mins[N];
//vector<int>links[N];
int links[N];
bool er[N];

int n,k,base=1;

void tree_prep(){
    for(int i=0;i<N;i++) t[i]=1000000009;
    while(base<n) base<<=1;
}

void make_tree(){
    int pocz = base/2;
    while(pocz!=0){
        for(int i=pocz;i<pocz*2;i++) t[i]=min(t[i*2],t[(i*2)+1]);
        pocz/=2;
    }
}

void wyp(){
    int pocz=1;
    while(pocz<=base){
        for(int i=pocz;i<pocz*2;i++) cout<<t[i]<<" "; cout<<"\n"; pocz*=2;
    }
}
//int ask2(int x, int a, int )

int ask(int a){ //od zero
    a+=base+1; //bo pytamy się o przedział bez a;
    int b=a+k-1;
    int wyn=min(t[a],t[b]);
   // a/=2; b/=2;
   // if(a==b) return t[a];
    while(a/2 != b/2){
        if((a%2)==0) wyn=min(wyn,t[a+1]);
        if(b%2) wyn=min(wyn,t[b-1]);
        a/=2; b/=2;
    }
    return wyn;
}


void make_links(int a){
    for(int i=a;i<n-k;i++){
        if(er[i]) continue;
        int ile=0; int idx=-1;
        for(int j=i+1;j<=i+k;j++){
            if(t[i+base]>t[j+base]){
                idx=j; ile++;
                if(ile>1) break;
            }
        }
        if(ile==1) links[idx]=i;// links[idx].push_back(i);
    }
}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>k;
    tree_prep();
    for(int i=base;i<base+n;i++) cin>>t[i];
    make_tree();

    int temp=1000000009;
    bool err=false;
    int ferr=-1;
    int lerr=-1;

   /* wyp();
    int x=15;
    for(int i=7+base+1;i<=7+base+k;i++) x=min(x,t[i]);

    cout<<"pomi t[7+base] "<<t[7+base]<<" ask(7) "<<ask(7)<<" t[7+base+5] "<<t[base+7+5]<<" "<<k<<"\n"; */

    for(int i=0;i<n-k;i++){
        int pomi= ask(i);
     //   cout<<"i "<<i<<" pomi "<<pomi<<" t[i+base] "<<t[i+base]<<"\n";
        mins[i]= pomi;
        er[i]= (t[i+base]<=pomi);
        if(er[i]){
        //    cout<<"errrr "<<i<<" "<<pomi<<"\n";
            if(!err){ ferr=i; err=true;}
            lerr=i;
            temp=min(temp,t[i+base]);
        }
    }

    if(ferr==-1){ cout<<"YES"; return 0;} //nie ma błędów
    if(lerr+1>ferr+k) {cout<<"NO"; return 0;} // nie ma gdzie wstawić
    if(lerr+k+1>n-1){cout<<"NO"; return 0;} // nie ma skąd wziąć

    make_links(lerr+1);

   // err=false; //recykling zmiennej xd

  //  if(n==500000) {printf("dsajflkdsafldsa\n"); return 0;} do tąd szybko jest

  //  int temp=t[lerr+base],t[ferr+base]);

    for(int j=lerr+k+1;j<n;j++){
        if(temp<=t[j+base]) continue;
        for(int i=lerr+1;i<=ferr+k;i++){
            if(mins[i]>=t[j+base]) continue;
            if(links[j]>=i) continue;
            cout<<"YES";return 0;
        }
    }

    cout<<"NO"; return 0;
}
/*
 10 3

5 6 4 3 6 10 6 2 7 3
*/
