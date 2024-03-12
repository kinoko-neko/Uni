#include<bits/stdc++.h>
using namespace std;

int w1,n,d;
int t[100005];
long long int ile,wyn;
int main(){

    ios_base::sync_with_stdio();
    cin.tie(0);
    cout.tie(0);

    cin>>n>>d;

    for(int i=0;i<n;i++) cin>>t[i];

    for(int i=2;i<n;i++){
        while(t[i]-t[w1]>d && w1!=i-2) w1++;
        if(t[i]-t[w1]<=d) {
            ile=i-w1;
            wyn+=((ile-1LL)*ile)/2LL;
        }
    }
    cout<<wyn;
}
