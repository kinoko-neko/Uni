#include<bits/stdc++.h>
#define ll long long int
using namespace std;
const int N=150005;
int n,m;

int t[N];
int siz[N];
int friends[N];

int f(int x){
    if(t[x]!=x){
        t[x]=f(t[x]);
    }
    return t[x];
}

void un(int a, int b){
    a=f(a); b=f(b);
    t[b]=a;
    if(a!=b){
        t[b]=a;
        siz[a]+=siz[b];
    }
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        t[i]=i; siz[i]=1;
    }
    while(m--){
        int a,b;
        cin>>a>>b;
        friends[a]++;
        friends[b]++;
        un(a,b);
    }
//    cout<<"siz: ";
  //  for(int i=1;i<=n;i++) cout<<siz[i]<<" "; cout<<"\n";
    for(int i=1;i<=n;i++){
        if(friends[i]<siz[f(i)]-1){
            cout<<"NO\n"; return 0;
        }
    }
    cout<<"YES\n"; return 0;
}
