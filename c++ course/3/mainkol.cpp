#include<bits/stdc++.h>
#include "kolejka.cpp"

using namespace std;

int main(){
	kolejka k1;
	kolejka k2= kolejka(20);
	kolejka k3= {"aaa","safa","afddasa"};

	//kolejka k4= kolejka(-2); ok
//
	cout<<k3.dlugosc()<<"\n";// ok
	string pom2="";
	for(int i=0;i<10;i++){
		char pom1='a'+i;
		pom2.push_back(pom1);
		k2.wstaw(pom2);
	}
	cout<<k2.dlugosc()<<"\n";
	for(int i=0;i<10;i++){
		cout<<k2.usun()<<"\n";
	}
	for(int i=0;i<3;i++){
		cout<<k3.zprzodu()<<"\n";
	}
	kolejka k4= kolejka(k3);
	for(int i=0;i<3;i++){
		cout<<k4.usun()<<"\n";
	}
}
