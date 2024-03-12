#include<iostream>
#include<vector>
using namespace std;

int p[500000];
vector<int>v;
int t[200005];

int main(){

    int n,k; //k-wzorzec
    cin>>n>>k;
    for(int i=0;i<n;i++) cin>>t[i];
    int a,b;
    cin>>a;//pocz;
    b=a;
    for(int i=1;i<k;i++){
        int c; int x;
        cin>>c;
        x=c;
        c-=b;
        b=x;
        v.push_back(c);
    }

    if(k==1){
        cout<<n; return 0;
    }

    v.push_back(-2000000008);
    v.push_back(a+1);//nie ważne co to chodzi i to ze jak szukam wzorca to nie chce by poczatek mi sie zlapal jak usuwam pierwszy element ze wzorca

    for(int i=1;i<n;i++) v.push_back(t[i]-t[i-1]);

    p[0]=-1;
    int pom=-1;
    int wyn=0;
    for(int i=0;i<v.size();i++){
      //  if(i==7){
        //    cout<<i<<" "<<v[i]<<" "<<pom<<" "<<v[pom]<<" dsfds\n";
       // }
        while( pom>-1 && (v[i]!=v[pom])) pom=p[pom]; pom++;
        p[i+1]=pom;
        if(pom==k-1) wyn++;
    }
 //   for(int i=0;i<22;i++) cout<<v[i]<<" "; cout<<"\n";
   // for(int i=0;i<22;i++) cout<<p[i]<<" "; cout<<"\n";
   cout<<wyn;
}
