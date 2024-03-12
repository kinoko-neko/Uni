#include<bits/stdc++.h>
#define ff first
#define ss second
using namespace std;
const int N=100005;
int t1[N];
int t2[N];
vector<pair<int,int> >v;

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,k,wyn = 0;

    cin>>n>>k;
    for(int i=0;i<n;i++) cin>>t1[i];

    for(int i=0;i<n;i++) {
        cin>>t2[i];
        if(t2[i]==0) v.push_back({i,t1[i]});
        else wyn+=t1[i];
    }

    int wsk,akt,best=0;
    int siz=1;
    if(v.size()!=0 ){ akt=v[0].ss; wsk=0;}

    int pomi=v.size();

    for(int i=0;i<pomi;i++){
        while(wsk+1<pomi){
          if(siz+(v[wsk+1].ff-v[wsk].ff)>k ) break;
          siz+=(v[wsk+1].ff-v[wsk].ff);
          wsk++;
          akt+= v[wsk].ss;
        }
        best=max(best,akt);
        akt-=v[i].ss;
        if(i+1<pomi) {
            siz-=v[i+1].ff-v[i].ff;
            if(wsk==i){
                siz=1;
                wsk=i+1;
                akt=v[i+1].ss;
            }
        }

    }
    cout<<best+wyn;
}
