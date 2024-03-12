#include<bits/stdc++.h>
#include "4.h"
using namespace std;
char alfabet[250];
int liczby_num[10];
int alfabet_num[30];

void wstaw_znaki(){
	alfabet[7]='a';
	alfabet[41]='b';
	alfabet[50]='c';
	alfabet[14]='d';
	alfabet[1]='e';
	alfabet[49]='f';
	alfabet[17]='g';
	alfabet[40]='h';
	alfabet[4]='i';
	alfabet[79]='j';
	alfabet[23]='k';
	alfabet[43]='l';
	alfabet[8]='m';
	alfabet[5]='n';
	alfabet[26]='o';
	alfabet[52]='p';
	alfabet[71]='q';
	alfabet[16]='r';
	alfabet[13]='s';
	alfabet[2]='t';
	alfabet[22]='u';
	alfabet[67]='v';
	alfabet[25]='w';
	alfabet[68]='x';
	alfabet[77]='y';
	alfabet[44]='z';
	//cyfry
	alfabet[241]='1';
	alfabet[238]='2';
	alfabet[229]='3';
	alfabet[202]='4';
	alfabet[121]='5';
	alfabet[122]='6';
	alfabet[125]='7';
	alfabet[134]='8';
	alfabet[161]='9';
	alfabet[242]='0';
	
}

string znak_morsa(int x){
	string t="";
	int pom;
	while(x){
		pom=x%3;
		if(pom==1){
			t.push_back('.');
		}
		if(pom==2){
			t.push_back('-');
		}
		x/=3;
	}
	t.push_back(' ');
	return t;
}

void wstaw_numery(){
	for(int i=0;i<253;i++){
		char pom=alfabet[i];
		if(pom<='z' && pom>='a'){
			alfabet_num[pom-'a']=i;
		}
		else{
			liczby_num[pom-'0']=i;
		}
	}
}

void prep(){
	wstaw_znaki();
	wstaw_numery();
}

string dekoduj( string c){
	string t= "";
	
	int pom1=1, pom2=0;
	for(int i=0;i<c.size();i++){
		if(c[i]!='-' && c[i]!='.'){
			t.push_back(alfabet[pom2]);
			if(pom2==0) t.push_back(c[i]);
			pom2=0; pom1=1;
		}
		else{
			pom2+=pom1;
			if(c[i]=='-') pom2+=pom1;
			pom1*=3;
		}
	}
	if(pom2!=0){
		t.push_back(alfabet[pom2]);
	}
	return t;
}

string koduj(string c){
	string t ="";
	string pomi;
	for(int i=0;i<c.size();i++){
		if(c[i]<='z' && c[i]>='a'){
			pomi=znak_morsa(alfabet_num[c[i]-'a']);
			t.append(pomi);
		}
		else if (c[i]<='9' && c[i]>='0'){
			pomi=znak_morsa(liczby_num[c[i]-'0']);
			t.append(pomi);
		}
		else{
			t.push_back(' ');
		}
	}
	return t;
}
