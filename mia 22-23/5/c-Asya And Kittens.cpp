#include<bits/stdc++.h>
#define ll long long int
using namespace std;
const int N=150005;
int n;

int t[N];
int kr[N][2];
int prawy[N];
int ost;
int f(int x){
    if(t[x]!=x){
        t[x]=f(t[x]);
    }
    return t[x];
}

void un(int a, int b){
    a=f(a); b=f(b);
    t[b]=a;
    prawy[kr[a][1]]=kr[b][0];
    kr[a][1]=kr[b][1];
    ost=kr[a][0];
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        t[i]=i;
        kr[i][0]=i;
        kr[i][1]=i;
    }

    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        un(a,b);
    }
    cout<<ost<<" ";
    while(prawy[ost]!=0){
        ost=prawy[ost];
        cout<<ost<<" ";
    }
    return 0;
}
