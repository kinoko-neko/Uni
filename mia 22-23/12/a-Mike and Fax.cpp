#include<iostream>
#include<string>
using namespace std;

string s;
int k;

int main(){

    cin>>s>>k;
    int n=s.size();
    int siz=n/k;
    if(siz*k!=n){
        cout<<"NO\n";
        return 0;
    }
    for(int i=0;i<k;i++){
        int l=siz*i;
        int r=l+siz-1;
        while(r>l){
            if(s[l]!=s[r]){
                cout<<"NO\n"; return 0;
            }
            l++;
            r--;
        }
    }
    cout<<"YES\n";
}
