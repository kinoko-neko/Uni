#include<bits/stdc++.h>
#define ll long long int
using namespace std;

ll a[200005];
ll b[200005];

ll wyn;
ll fmxmin; //minimalne maximum

vector<pair<ll,ll> >v;
vector<int>d;

int n;

ll t[200005];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int q;
    cin>>q;
    while(q--){
        cin>>n;
        for(int i=0;i<n;i++){ cin>>a[i]; }
        for(int i=0;i<n;i++){
            cin>>b[i];
            v.push_back({a[i],b[i]});
        }
        sort(v.begin(),v.end());
        ll wyn=v[n-1].first;
        ll sum=v[n-1].second;
        for(int i=n-2;i>=0;i--){
            wyn=min(wyn,max(v[i].first,sum));
            sum+=v[i].second;
        }
        wyn=min(wyn,sum);
        cout<<wyn<<"\n";
        v.clear();
    }

}
/*
 1
 4
1 2 3 4
3 3 3 3
*/
