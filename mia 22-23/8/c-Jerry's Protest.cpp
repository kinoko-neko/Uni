#include<bits/stdc++.h>
using namespace std;

int t[2006];
long long int dif[10009]; //andrew-jerry
const int mid=5000;
long long int pref[10009];
int main(){
    int n;
    cin>>n;
    cout << fixed << setprecision(20);
    for(int i=0;i<n;i++) cin>>t[i];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i!=j){
                dif[t[i]-t[j]+mid]++;
      //          cout<<t[i]-t[j]<<"\n";
            }
        }
    }
    pref[0]=dif[0];
    for(int i=1;i<10009;i++) pref[i]=pref[i-1]+dif[i];
    long long int ile=0;
    for(int i=mid+1;i<10009;i++){
        for(int j=mid+1;j<10009;j++){
            int d=mid- ((i-mid)+(j-mid)); //
            if(d>0){
                ile+=(pref[i]-pref[i-1])*(pref[j]-pref[j-1])*pref[d-1];
            }
        }
    }
   // cout<<ile<<" licznik \n";
  //  cout<<(pref[10008]-pref[mid])*(pref[10008]-pref[mid])*pref[mid-1]<<" mian\n";
    long double licz= (long double )ile;
    long double mian= (long double)((pref[10008]-pref[mid])*(pref[10008]-pref[mid])*pref[mid-1]);
  //  cout<<licz<<" "<<mian<<"\n";
    cout<<licz/mian;
}
