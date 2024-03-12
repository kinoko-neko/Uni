#include<bits/stdc++.h>
#include "cezar.cpp"
using namespace std;

char szyfruj(char x, int shift){
	if(x<='z' && x>='a'){
		x-='a'; x+=shift; x%=26; x+='a';
	}
	if(x<='Z' && x>='A'){
		x-='A'; x+=shift; x%=26; x+='A';
	}
	return x;
}

int main(int argc, char *argv[]){
	if(argc!=4) {
		cout<< "zla liczba argumentow"; return 0;
	}
	
	wejscie inp (argv[1]);
	wyjscie out (argv[2]);
	int shift = atoi(argv[3])%26;
	
	string temp;
	while(!inp.eof()){
		temp=inp.nastlinia();
		for(int i=0;i<temp.size();i++) temp[i]=szyfruj(temp[i],shift);
		out.piszlinie(temp);
	}
	return 0;
}
