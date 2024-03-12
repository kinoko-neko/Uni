#include<bits/stdc++.h>
using namespace std;

int nwd(int a, int b){
    if(b==0){
        return a;
    }
    return nwd(b,a%b);
}


int main(){

    int q;
    cin>>q;
    while(q--){
        int n,x,y,z;
        cin>>n;
        if(n==1){
            cin>>x; cout<<"YES\n";
        }
        else if(n==2){
            cin>>x>>y; cout<<"YES\n";
        }
        else{
            cin>>x>>y;
            bool ans=true;
            for(int i=3;i<=n;i++){
                cin>>z;
                int d=nwd(x,z);
                if(y%d!=0 || d>y) ans=false;
                x=y; y=z;
            }
            if(ans) cout<<"YES\n"; else cout<<"NO\n";
        }
    }
}
