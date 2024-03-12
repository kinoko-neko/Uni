#include<bits/stdc++.h>
#include "wyrazenie.cpp"

using namespace std;

int main(){
	wyrazenie *w = new odejmij(new pi(),
											new dodaj(new liczba(2), new mnoz( new zmienna("x"),new liczba(7))));
	cout<< w->zapis()<<"\n";
	zmienna::dodajzmienna("x", 0.01);

	for(int i=0;i<=10;i++){
		double pomi=0.0+i*0.1;
		zmienna::dodajzmienna("x",pomi);
		cout<< w->oblicz()<<"\n";
	}
	
	cout<< w->zapis();
}
