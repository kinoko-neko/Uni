#include<iostream>
using namespace std;
const int N=200005;
int tab[N];

int main(){

    int t,n;

    cin>>t;
    string s;
    while(t--){
        int n,k; bool f=false;
        cin>>n>>k; cin>>s;
        for(int i=0;i<n-1;i++){
            if(k>0){
                bool jeden=(f==false && s[i]=='1') || (f==true && s[i]=='0');
                s[i]='1';
         //       cout<<"poz:"<<i<<" k:"<<k<<" flip: "<<(int)f<<" jeden: "<<(int)jeden<<"\n";
                if(jeden){
                    if(k%2==1){
                        tab[i]=1;
                        f=!f; k--;
                    }
                    else{
                        tab[i]=0;
                    }
                }
                else{
                    if(k%2==0){
                        tab[i]=1;
                        f=!f; k--;
                    }
                    else{
                        tab[i]=0;
                    }

                }
            }
            else{
                tab[i]=0;
                if((s[i]=='0' && !f) || (s[i]=='1' && f)) s[i]='0'; else s[i]='1';
            }
        }
        tab[n-1]=k;
     //   cout<<(int)f<<"\n";

     //   cout<<"poz:"<<5<<" k:"<<k<<" flip: "<<(int)f<<"\n";
        if((s[n-1]=='0' && !f) || (s[n-1]=='1' && f)) s[n-1]='0'; else s[n-1]='1';
        cout<<s<<"\n";
        for(int i=0;i<n;i++) cout<<tab[i]<<" "; cout<<"\n";

    }
}
