#include<bits/stdc++.h>
#define ll long long int
using namespace std;

int n,k;
ll b,c,wyn=LLONG_MAX;
ll t[200005];

queue<int> kol[5];

ll prog(int res, ll x){
    if(x%5LL>res) x+=5;
    return (x/5)*5 + res;
}

ll cost(ll lim, ll x){
    ll pomi=lim-x;
    return (pomi/5LL)*b + (pomi%5LL)*c;
}

ll prep(int res){
    ll lim=prog(res,t[k-1]);
    ll ret=0;
    for(int i=0;i<k;i++){
        ret+=cost(lim,t[i]);
        kol[t[i]%5].push(t[i]);
    }
    return ret;
}

ll krok(ll lim){
    ll ret=-1; int wsk=9;
    for(int i=0;i<5;i++){
        if(!kol[i].empty()){
          int pom=kol[i].front();
          ll pom2=cost(lim,pom);
          if(pom2>ret){
                ret=pom2;
                wsk=i;
          }
        }
    }

    kol[wsk].pop();
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>k>>b>>c; b= min(b,5*c);
    for(int i=0;i<n;i++) {cin>>t[i]; t[i]+=1000000000LL;}
    sort(t,t+n);
    ll temp;
    for(int res=0;res<5;res++){
        temp=prep(res); wyn=min(wyn,temp); //cout<<"temp= "<< temp<<" ";
        for(int i=k;i<n;i++){
            temp-=krok(prog(res,t[i-1])); //kasuje najmniej korzystny do nowego progu i zwraca ile dodawał do starego
            temp+=(k-1)*b*((prog(res,t[i])-prog(res,t[i-1]))/5); //pozostałe muszą wzrosnąc o tyle o ile wzrósł nowy próg
            temp+=cost(prog(res,t[i]),t[i]);//koszt nowego
            kol[t[i]%5].push(t[i]);
            wyn=min(wyn,temp);
        }
        for(int i=0;i<5;i++){
            int siz=kol[i].size();
            while(siz>0){
                kol[i].pop(); siz--;
            }
        }
    }
    cout<<wyn;
    return 0;
}
