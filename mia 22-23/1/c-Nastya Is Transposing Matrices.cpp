#include<bits/stdc++.h>
using namespace std;

int a[500][500];
int b[500][500];

vector<int>av;
vector<int>bv;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n,m;
    cin>>n>>m;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cin>>a[i][j];
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cin>>b[i][j];
    }

    for(int i=0;i<n;i++){
        int n2=i; int m2=0;
        while(n2>=0 && m2<m){
            av.push_back(a[n2][m2]);
            bv.push_back(b[n2][m2]);
            n2--; m2++;
        }
        sort(av.begin(),av.end());
        sort(bv.begin(),bv.end());
        for(int j2=0;j2<av.size();j2++)
            if(av[j2]!=bv[j2]){
                cout<<"NO\n"; return 0;
            }
        av.clear();
        bv.clear();
    }

    for(int j=1;j<m;j++){
            int n2=n-1; int m2=j;
            while(n2>=0 && m2<m){
                av.push_back(a[n2][m2]);
                bv.push_back(b[n2][m2]);
                n2--; m2++;
            }
            sort(av.begin(),av.end());
            sort(bv.begin(),bv.end());
            for(int j2=0;j2<av.size();j2++)
                if(av[j2]!=bv[j2]){
                    cout<<"NO\n"; return 0;
                }
            av.clear();
            bv.clear();
    }

    cout<<"YES\n"; return 0;
}
