#include<bits/stdc++.h>
using namespace std;

int n;

int main(){

	cin>>n;
	if(n&1) cout<<'0';
	else cout<<(1<<(n>>1));

	return 0;

}
