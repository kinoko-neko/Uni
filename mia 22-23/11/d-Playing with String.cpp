#include<bits/stdc++.h>
using namespace std;

int t[5005];
bool mex[15005];
int siz[5005];
int main(){
    string s;

    cin>>s;
    int n=s.size();
    for(int i=1;i<=n;i++){
        memset(mex,0,n+5);
        for(int j=0;j<i;j++){
            int pom=t[max(0,j-1)]^t[max(0,i-j-2)];
            mex[pom]=true;
        }
        for(int j=0;j<=n+2;j++){
            if(!mex[j]){ t[i]=j; break;}
        }
    }
 //for(int i=0;i<7;i++) cout<<t[i]<<" "; cout<<"\n";
    int pom=0;
    for(int i=1;i<n-1;i++){
        if(s[i-1]==s[i+1]){
            int j=i;
            while(j+2<n && s[j+2]==s[j]) j++;
            siz[i]=j-i+1;
            pom^=t[j-i+1]; i=j+1;
        }
    }

    if(pom){
        cout<<"First\n";
        for(int i=1;i<n-1;i++){
            if(siz[i]){
                int pom2= pom^t[siz[i]];
           //     cout<<"pom2= "<<pom2<<"\n";
                for(int j=0;j<siz[i];j++){
                    int pom3=pom2^t[max(0,j-1)]^t[max(0,siz[i]-j-2)];
                    if(pom3==0){
                        cout<<i+j+1; return 0;
                    }
                }

            }
        }
    }
    else cout<<"Second";
}
