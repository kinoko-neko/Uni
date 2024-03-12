#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,v;
    cin>>n>>v;
    long long wyn;
    if(n-1<=v) wyn=n-1;
    else{
        wyn= v + ((2+n-v)*(n-v-1))/2;
    }
    cout<<wyn;
    return 0;
}
