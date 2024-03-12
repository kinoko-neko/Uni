#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

vector<int64_t> rozklad(int64_t n){
	vector<int64_t>ret;
	
	if(n>=-1 && n<=1){
		ret.push_back(n); return ret;
	}
	
	if(n<0) {n*=-1; ret.push_back(-1);}
	
	while(!(n&1)){
		ret.push_back(2); n/=2;
	}
	
	for(int64_t i=3;i*i<=n && n!=1;i+=2){
		while(n%i==0){
			n/=i; ret.push_back(i);
		}
	}
	if(n!=1) ret.push_back(n);
	return ret;
}

void wypisz(int64_t x){
	cout<<'*'<<x;	
}

int main (int arg, char* argv[] ) {
	if(arg==1){
		cerr<<"brak argumentów"; return 0;
	}
	
	int64_t liczba;	
	vector<int64_t>wyn;
	
	for(int i=1;i<arg;i++){
		liczba=stoll(argv[i],nullptr,10);
		wyn=rozklad(liczba);
		
		cout<<liczba<<" = ";
		int64_t pomi=wyn.back(); wyn.pop_back();
		for(auto &x: wyn){
			cout<<x<<"*";
		}		
		cout<<pomi<<"\n";
	}
	return 0;
}
