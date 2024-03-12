#include<bits/stdc++.h>
using namespace std;

int t[100][100];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int c,r,n,k;
    cin>>c>>r>>n>>k;
    for(int i=0;i<n;i++){
        int a,b;
        cin>>a>>b;
        t[a][b]=1;
    }
    for(int i=2;i<=r;i++){ t[1][i]+=t[1][i-1];}
    for(int i=2;i<=c;i++){ t[i][1]+=t[i-1][1];}
    for(int i=2;i<=c;i++){
        for(int j=2;j<=r;j++) t[i][j]+=t[i-1][j]+t[i][j-1]-t[i-1][j-1];
    }
    int wyn=0;
    if(k==1) wyn+=n;
    for(int i1=1;i1<=c;i1++){
        for(int j1=1;j1<=r;j1++){
            for(int i2=1;i2<=c;i2++){
                for(int j2=1;j2<=r;j2++){
                    if(i1>=i2 && j1>=j2) continue;
                    if( k<= t[i2][j2]-t[i2][j1-1]-t[i1-1][j2]+t[i1-1][j1-1] ) wyn++;
                }
            }
        }
    }

    cout<<wyn;
}
