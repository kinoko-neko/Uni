#include<bits/stdc++.h>
#include "zad2.cpp"
using namespace std;

int n4=23;

string naz;
int main(){

//test zmiennej
	zmienna yy;
	cout<<yy.get_nazwa()<<" "<<yy.get_wartosc()<<"\n";
	zmienna a= zmienna("eee");
	zmienna b=zmienna("macarena",18.29);
	cout<<a.get_nazwa()<<" "<<b.get_nazwa()<<"\n";
	cout<<a.get_wartosc()<<" "<<b.get_wartosc()<<"\n";
	a.set_wartosc(19.09);
	cout<<a.get_wartosc()<<" "<<b.get_wartosc()<<"\n";
	
	
//test zbior_zmiennych	
	
	zbior_zmiennych za=zbior_zmiennych(n4);
	
	//czy wstawianie działa i is
	for(int i=0;i<n4;i++){
		naz=(char)('a'+i);
		za.wstaw( zmienna(naz,(double)i) );
		if(za.is(naz)==false){
			cout<<i<<" "<<naz<<" oniasnojsdapo\n"; return 0; 
		}
	}
	
	//modyfikowanie i odczyt
	for(int i=0;i<n4;i++){
		naz=(char)('a'+i);
		za.set_wartosc(naz,(double)(i+2));
		cout<<za.get_wartosc(naz)<<"\n";
	}
	
	//kasowanie
	for(int i=0;i<n4;i++){
		naz=(char)('a'+i);
		if(za.is(naz)==false){
			cout<<"oniasnojsdapo\n";
		}
		za.usun(naz);
		if(za.is(naz)){
			cout<<"nie kasuje\n";
		}
	}
	
	
	//zbior_zmiennych pom= zbior_zmiennych(-10);
	cout<<"ok\n";
}
