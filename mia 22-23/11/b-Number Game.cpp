#include<iostream>
using namespace std;
const int N=1000005;
bool s[1000006];

void sito(){
    for(int i=4;i<=N;i+=2) s[i]=true;
    for(int i=3;i*i<=N;i+=2){
        if(!s[i]){
            int j=i*i;
            while(j<=N){
                s[j]=true;
                j+=i;
            }
        }
    }

}

bool prim(int x){
    if(x<=N) return !s[x];
    for(int i=3;i*i<=x;i+=2){
        if(x%i==0) return false;
    }
    return true;
}

int main(){
    int q,n;
    cin>>q;
    sito();
    while(q--){
        cin>>n;
        if(n==2 || (n%2==1 && n>1) ) cout<<"Ashishgup\n";
        else if(__builtin_popcount(n)==1) cout<<"FastestFinger\n";
        else {
            if(n%4==0) cout<<"Ashishgup\n";
            else{
                n/=2;
                if(prim(n)) cout<<"FastestFinger\n";
                else cout<<"Ashishgup\n";
            }
        }
    }
    return 0;
}
