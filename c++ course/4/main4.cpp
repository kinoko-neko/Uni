#include<bits/stdc++.h>
#include "wielomian.cpp"
using namespace std;

int main(){
	
	double tab[4]={1.1,1.1,1.1,1.1};
	double tab_er[4]={1.1,1.1,1.1,0.0};
	
	//test konstruktorów
	wielomian w1,w4;
	wielomian w2= wielomian({1.0,2.0,3.0,4.0});
	wielomian w3= wielomian(3,tab);
	cin>>w4;
	wielomian w5=w3;
	try{
		wielomian w6= wielomian(3,tab_er);
	}
	catch(invalid_argument const& ex){
		cerr<<"zle arg\n";
	}
	//wypis
	cout<<w5<<"\n";
	
	//dostep indeksowany
	wielomian w7=w3;
	w7[0]=7.7;
	cout<<w7[0]<<" "<<w7[1]<<"\n";
	
	//wartosc
	cout<<w3(1)<<"\n";
	
	//DZIALANIA
	
	//dodawanie
	wielomian w8=w3;
	w8+=w3;
	wielomian w9=w3+w3;
	cout<<w8<<"  =   "<<w9<<"\n";
	
	//odejmowanie
	wielomian w10=w3;
	w10-=w3;
	wielomian w11=w3-w3;
	cout<<w10<<"\n"<<w11<<"\n";
	
	//mnozenie
	wielomian w12=w3;
	w12*=w3;
	wielomian w13=w3*w3;
	cout<<w12<<"\n"<<w13<<"\n";

	wielomian w14=w3;
	w14*=5;
	wielomian w15=w3*5;
	cout<<w14<<"\n"<<w15;
}
