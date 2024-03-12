#include<bits/stdc++.h>
using namespace std;

//long long int t[120][6];

int main(){
    long long int n,wyn;
    cin>>n;

    wyn=n*(n-1)*(n-2)*(n-3)*(n-4);
     wyn= (wyn/120LL) *wyn;
    cout<<wyn;
    /*
    t[0][0]=1LL;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=5 && j<=i;j++){
            t[i][j]=t[i-1][j]+i*t[i-1][j-1];
        }
    }
    cout<<t[n][5];*/
}
