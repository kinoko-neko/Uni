#include<bits/stdc++.h>
#define ll long long int
using namespace std;

priority_queue<ll, vector<ll>, greater<ll> >q;
ll v[100005];
ll t[100005];


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    int n;
    cin>>n;
    ll melted=0LL;
    ll acc=0LL;
    for(int i=0;i<n;i++) cin>>v[i];
    for(int i=0;i<n;i++) cin>>t[i];

    for(int i=0;i<n;i++){
        melted=0LL;
        while(!q.empty()){
            ll pom=q.top();
            if(pom>t[i]+acc) break;
            melted+=pom-acc;//bo acc liczyłem wcześniej
            q.pop();
        }
        if(!q.empty()){
            melted+=q.size()*t[i];
            if(v[i]>t[i]){
                melted+=t[i];
                q.push(v[i]+acc);
            }
            else{
                melted+=v[i];
            }
            acc+=t[i];
        }
        else{
            acc=0LL;
            if(v[i]>t[i]){
                melted+=t[i];
                q.push(v[i]-t[i]);
            }
            else{
                melted+=v[i];
            }
        }
        cout<<melted<<" ";
    }
}
