#include<bits/stdc++.h>
#define ll long long int
using namespace std;

ll t[100005];
int n;
int m=1000000007;
void prep(){
    t[0]=1LL;
    t[1]=1LL;
    for(int i=2;i<=n;i++){
        t[i]=t[i-1]+t[i-2];
        t[i]%=m;
    }
}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin>>s;
    n=s.size();
    prep();

    char prev='2';
    ll siz=0;
    ll wyn=1;
    for(int i=0;i<n;i++){
        if(s[i]=='w' || s[i]=='m'){
            cout<<0; return 0;
        }
        if(s[i]=='u' || s[i]=='n'){
            if(s[i]==prev){
                siz++;
            }
            else{
                wyn*=t[siz];
                wyn%=m;
                siz=1;
            }
        }
        else {
            if(prev=='u' || prev=='n'){
                wyn*=t[siz];
                wyn%=m;
                siz=0;
            }
        }
        prev=s[i];
    }
    if(prev=='u' || prev=='n'){
                wyn*=t[siz];
                wyn%=m;
                siz=0;
    }
    cout<<wyn;
}
