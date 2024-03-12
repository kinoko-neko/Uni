#include<bits/stdc++.h>
using namespace std;
const int K=100;
unsigned long long int tab[K];
//int t2[K];
int main(){
    int t;
    cin>>t;
    while(t--){
        long long int n; int m;
        cin>>n>>m;
        for(int i=0;i<60;i++) tab[i]=0;
        long long int a,sum=0;
        for(int i=0;i<m;i++){
            cin>>a;
            tab[(int)log2(a)]++;
            sum+=a;
        }
        if(sum<n){
            cout<<"-1\n"; continue;
        }

        int wyn=0;
  //     for(int i=0;i<10;i++) cout<<tab[i]<<" "; cout<<"\n";
        for(int i=0;i<60;i++){

            if((1LL<<i)&n){
           //     cout<<i<<" "<<wyn<<" "<<tab[i]<<"\n";
                if(tab[i]){
                    tab[i]--;
                }
                else{
                    while(i<60 && tab[i]==0) {i++; wyn++;}
                    tab[i]--; i--;continue;
                }
            }

            tab[i+1]+=(tab[i]/2);

        }
       cout<<wyn<<"\n";
       // cout<<"wyn:"<<wyn<<"\n";
    }
}
