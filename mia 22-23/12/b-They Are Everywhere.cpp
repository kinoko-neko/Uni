#include<iostream>
#include<string>
#include<cmath>
using namespace std;
int typ[500];
bool t[500];
int ile;

int main(){
    int n;
    string s;
    cin>>n>>s;

    for(int i=0;i<n;i++){
        if(!t[(int)s[i]]){
            t[(int)s[i]]=true;
            ile++;
        }
    }

    int r=-1;
    int cnt=0;
    int wyn=n;

    for(int i=0;i<n;i++){

        if(r<i){
            r=i;
            typ[(int)s[r]]++; cnt=1;
        }

        while(cnt!=ile && r<n-1){
            r++;
            if(!typ[(int)s[r]]) cnt++;
            typ[(int)s[r]]++;
        }
        if(ile==cnt) wyn=min(wyn,r-i+1);
        typ[(int)s[i]]--;
        if(typ[(int)s[i]]==0) cnt--;
    }
    cout<<wyn;
}
