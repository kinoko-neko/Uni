#include<bits/stdc++.h>
#define ll long long int
using namespace std;
ll t[505];
int n;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll pomi=LLONG_MAX;
    ll wyn=pomi;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>t[i]; pomi=min(pomi,t[i]);
    }
    ll pomi2=pomi;
    pomi=sqrt(pomi);

    for(int i=1;i<=pomi;i++){
        long long int temp=0;
        ll t2;
        for(int j=0;j<n;j++){
            t2=(t[j]+i)/(i+1);
            if( t2*i>t[j] ){ temp=LLONG_MAX; break;}
            //     if(t[j]/i>t[j]%i){ temp=INT_MAX; break;}
            temp+=t2;
        }
        wyn=min(wyn,temp);
    }
  //  cout<<"wyn: "<<wyn<<" \n";
    for(int k=1;k<=pomi;k++){
        ll siz=pomi2/k;
        ll t2;
        long long int temp=0;
        for(int j=0;j<n;j++){
            t2=(t[j]+siz)/(siz+1);
            if(t2*siz>t[j]){ temp=LLONG_MAX; break;}
        //    if(k==1) cout<<j<<" t[j]= "<<t[j]<<" t2= "<<t2<<"\n";
            temp+=t2;
            //if(t[j]/siz<t[j]%siz){ temp=INT_MAX; break;}
            //temp+=(t[j]+siz-1)/siz;
        }
        wyn=min(wyn,temp);
       // if(wyn==3 && temp==3) cout<<"sakjlkdsa "<<k<<" "<<siz<<"\n";
        if(siz>1){
            siz--;
            temp=0;
            for(int j=0;j<n;j++){
                t2=(t[j]+siz)/(siz+1);
                if(t2*siz>t[j]){ temp=LLONG_MAX; break;}
                temp+=t2;
                //  if(t[j]/siz<t[j]%siz){ temp=INT_MAX; break;}
               // temp+=(t[j]+siz-1)/siz;
            }
            wyn=min(wyn,temp);
        }
    }
    cout<<wyn;
    return 0;
}
