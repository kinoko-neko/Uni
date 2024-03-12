#include<bits/stdc++.h>
#define ll long long int
using namespace std;
ll wyn=0;
ll p;
int k;
ll mn;

vector<int> v;
void gen( int siz){
    if(k==0) return;
    if(siz==0){
        k--;
        int vs=v.size()-1;
        ll p1=v[0]; ll p2=v[vs];
        for(int i=1;i<=vs;i++){
            p1*=10; p1+=v[i];
            p2*=10; p2+=v[vs-i];
        }
        wyn += p1*mn +p2; wyn%=p;
        return;
    }

    for(int i=0;i<10;i++){
        v.push_back(i);
        gen(siz-1);
        v.pop_back();
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    cin>>k>>p;
    mn=10LL;
    int roz=1;
    while(k){
        for(int i=1;i<10 && k>0;i++){
            v.push_back(i);
            gen(roz-1);
            v.pop_back();
        }
       // cout<<roz<<" sds\n";
        mn*=10;
        roz++;
    }
    cout<<wyn;
    return 0;
}
