#include<bits/stdc++.h>
using namespace std;
int even[2002];
int odd[2002];

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n,temp;
    int od=0; int pa=0;
    cin>>n;

    for(int i=0;i<n;i++){
        cin>>temp;
        if(temp%2){
            odd[od]=temp; od++;
        }
        else{
            even[pa]=temp; pa++;
        }
    }
    sort(even,even+pa); sort(odd,odd+od);
    long long wyn=0LL;
    if(pa==od || pa==od-1 || pa==od+1){ cout<<0; return 0;}

    if(pa>od){
        for(int i=0;i<(pa-od-1);i++) wyn += even[i];
    }
    else{
        for(int i=0;i<(od-pa-1);i++) wyn += odd[i];
    }
    cout<<wyn;
    return 0;
}
