#include<iostream>
using namespace std;

int main(){

    int t,n;

    cin>>t;
    while(t--){
        cin>>n;
        long long int a,b;
        cin>>a; n--;
        while(n--){
            cin>>b;
            a|=b;
        }
        cout<<a<<"\n";

    }
}
