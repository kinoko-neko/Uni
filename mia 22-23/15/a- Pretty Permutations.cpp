#include<iostream>
using namespace std;

//n-2,n-1,n -> n-1,n,n-2
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        if(n&1){
            for(int i=2;i<n-2;i+=2)
                cout<<i<<" "<<i-1<<" ";

            cout<<n-1<<" "<<n<<" "<<n-2<<"\n";
        }
        else{
            for(int i=1;i<=n;i+=2){
                cout<<i+1<<" "<<i<<" ";
            }
            cout<<"\n";
        }
    }
}
