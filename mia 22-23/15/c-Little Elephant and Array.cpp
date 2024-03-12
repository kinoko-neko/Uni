#include<bits/stdc++.h>
using namespace std;

int t[100005];
vector<int> wys[100005];
int tree[400099];
int base=1;
int answ[100005];
vector<pair<int,int> >zap[100005];

void update(int x,int val){
    x+=base;
    tree[x]=val;
    x/=2;
    while(x!=0){
        tree[x]=tree[x*2]+tree[x*2 +1];
        x/=2;
    }
}

void wyp(){
    int pocz=1;
    while(pocz<=base){
        for(int i=pocz;i<pocz*2;i++){
            cout<<tree[i]<<" ";
        }
        cout<<"\n"; pocz*=2;
    }
}
int ask(int l, int r){
    l+=base; r+=base;
    int wyn=tree[l];
    if(l!=r) wyn+=tree[r];
    while(l/2 != r/2){
        if(!(l&1)) wyn+=tree[l+1];
        if(r&1) wyn+=tree[r-1];
        l/=2; r/=2;
    }
    return wyn;
}

int main(){

    int n,m;
    cin>>n>>m;
    while(base<n) base*=2;
    for(int i=0;i<n;i++) cin>>t[i];
    for(int i=0;i<m;i++) {
        int z,r;
        cin>>z>>r; z--; r--;
        zap[r].push_back({z,i});
    }
    for(int i=0;i<n;i++){

        if(t[i]<=n){
            wys[t[i]].push_back(i);

            int freq=wys[t[i]].size();
            if(freq>=t[i]){
                update(wys[t[i]][freq -t[i]],1);
                if(freq>t[i]){
                    update(wys[t[i]][freq-t[i]-1],-1);
                    if(freq>t[i]+1){
                        update(wys[t[i]][freq-t[i]-2],0);
                    }
                }

            }
        }
        for(int j=0;j<zap[i].size();j++){
            answ[zap[i][j].second]=ask(zap[i][j].first,i);
        }
     //   wyp();
    }
    for(int i=0;i<m;i++) cout<<answ[i]<<"\n";
}
