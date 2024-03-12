#include<bits/stdc++.h>
#include "punkt.cpp"
using namespace std;

void wypisz(kolor k){
	cout<<k.get_r()<<" "<<k.get_g()<<" "<<k.get_b()<<"\n";
}

int main(){

	kolor k1= kolor();
	cout<<k1.get_r()<<"\n";
	kolor k2= kolor(1,2,3);
	//kolor k3= kolor(-1,0,0);
//	kolor k3= kolor(1, 290,3); 
	k2.set_g(16);
	wypisz(k2);
	k2.lighten(16);
	wypisz(k2);
	k2.darken(2);
	wypisz(k2);
	k2.add(k1);
	wypisz(k2);
	
	transkolor t1= transkolor(1,2,3,255);
	t1.add(k2);
	wypisz(t1);
	
	nazwkolor n1= nazwkolor(1,2,3,255,"andrzej"); 
//	nazwkolor er= nazwkolor(1,2,3,255,"09231");

	punktkolnazw p1 = punktkolnazw(1,2,t1,"A");
	punktkolnazw p2 = punktkolnazw(1,3,t1,"P1");
	cout<<p1.odleglosc(p2)<<"\n";
	
	punkt3d p3= punkt3d(1,2,3);
	punkt3d p4= punkt3d(2,4,6);
	punkt3d p5= punkt3d(2,6,9);
	
	cout<<(int)p3.wspolliniowe(p4,p5)<<"\n";
	
	p5.transpose(wektor3d(1,0,0));
	cout<<(int)p3.wspolliniowe(p4,p5)<<"\n";
}
