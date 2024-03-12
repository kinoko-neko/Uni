#include<iostream>
using namespace std;

int t[26];
int main(){
    string s;
    cin>>s;
    for(int i=0;i<s.size();i++) t[s[i]-'a']++;
    int ile=0;
    for(int i=0;i<26;i++) if(t[i]%2==1) ile++;
    if(ile==0) cout<<"First";
    else if(ile%2==1) cout<<"First";
    else cout<<"Second";
}
