#include<bits/stdc++.h>
#include "4.h"

int main(){
	
	prep();
	
	string s1,s2,s3;
	
	getline(cin,s1);
	
	s2=koduj(s1);
	cout<<s2<<"\n";
	
	s3=dekoduj(s2);
	cout<<s3;
}
