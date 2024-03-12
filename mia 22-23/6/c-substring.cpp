#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=300005;

int st[N];
int num[N][27];//gdzie 26 to max
int n,m;
string s;
queue<int>q;
vector<int>v[N];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    cin>>s;
    int wyn=1;
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        st[b]++;
        v[a].pb(b);
    }

    for(int i=1;i<=n;i++){
     //   num[i][26]=1;
       // num[i][s[i-1]-'a']=1;
        if(st[i]==0) q.push(i);
    }

    int n2=n;
    while(!q.empty()){
        n2--;
        int x=q.front();
        q.pop();
        num[x][s[x-1]-'a']++;
        num[x][26]=max(num[x][26],num[x][s[x-1]-'a']);
        wyn=max(wyn,num[x][26]);

        for(int i=0;i<v[x].size();i++){
            int g=v[x][i];
            st[g]--;
            if(st[g]==0) q.push(g);
            for(int i=0;i<26;i++){
                num[g][i]=max(num[x][i],num[g][i]);
                num[g][26]=max(num[g][26],num[g][i]);
            }
        }
    }

    if(n2!=0) cout<<-1; else cout<<wyn;
}
