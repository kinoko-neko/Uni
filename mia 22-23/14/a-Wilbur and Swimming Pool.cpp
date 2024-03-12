#include<iostream>
using namespace std;

int x[5];
int y[5];

int m(int s){
    if(s<0) s=-s; return s;
}

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>x[i]>>y[i];
    }
    if(n>2){
        for(int i=1;i<n;i++){
            if(y[0]!=y[i] && x[0]!=x[i]){
                cout<<m((y[0]-y[i])*(x[0]-x[i])); return 0;
            }
        }
        cout<<m((y[1]-y[2])*(x[1]-x[2])); return 0;
    }
    else{
        if( n<2 || y[0]==y[1] || x[0]==x[1]) cout<<-1;
        else{
            cout<<m((y[0]-y[1])*(x[0]-x[1]));
        }
    }
    return 0;
}
