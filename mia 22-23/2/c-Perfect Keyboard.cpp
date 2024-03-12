#include<bits/stdc++.h>
using namespace std;

int t[26];
bool t2[26];
char t3[300];

void spr(){
    for(int i=0;i<26;i++){
        t[i]=0; t2[i]=false;
    }
    for(int i=0;i<300;i++) t3[i]=0;
}

int main(){
    int t5,n,pom,pom2;
    string s;
    cin>>t5;
    bool ok;
    while(t5--){
        cin>>s; n=s.size();
        int pocz=50;
        int kon=50;
        t[(int)(s[0]-'a')]=pocz;
        t2[s[0]-'a']=true;
        t3[pocz]=s[0];
        ok=true;
        char prev=s[0];
        for(int i=1;i<n;i++){
            pom=s[i]-'a';
            if(t2[pom]){
                pom2=t[prev-'a'];
                if(t3[pom2+1]!=s[i] && t3[pom2-1]!=s[i]){
                    cout<<"NO\n"; ok=false; break;
                }
            }
            else{
                if(t3[kon]==prev){
                    t[pom]=kon+1;
                    t2[pom]=true;
                    t3[kon+1]=s[i];
                    kon++;
                }
                else{
                    if(t3[pocz]==prev){
                        t2[pom]=true;
                        t3[pocz-1]=s[i];
                        t[pom]=pocz-1;
                        pocz--;
                    }
                    else{
                        ok=false;
                        cout<<"NO\n"; break;
                    }
                }
            }
            prev=s[i];
        }
        if(ok){
            cout<<"YES\n";
            for(int i=pocz;i<=kon;i++) cout<<t3[i];
            for(int i=0;i<26;i++)
                if(t[i]==0) cout<<(char)(i+'a');
            cout<<"\n";

        }
        spr();
    }
    return 0;
}


//abacaba

