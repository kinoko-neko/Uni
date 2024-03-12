#include<bits/stdc++.h>
#include "cezar.hpp"
using namespace std;


wejscie::wejscie(string a){
	inp.open (a, ifstream::in);
	if(inp.fail()) throw ios_base::failure("blad otwierania");
}

string wejscie::nastlinia(){
	if(inp.eof()) throw "koniec pliku";
	string a; getline(inp,a);
	return a;
}

bool wejscie::eof(){ return inp.eof();}
wejscie::~wejscie(){ inp.close();}
	
wyjscie::wyjscie(string a){
	out.open (a, std::ofstream::out);
	if(out.fail() ) throw ios_base::failure("blad wyjscia");
}
	
void wyjscie::piszlinie(string a){
	out<<a<<"\n";
}

wyjscie::~wyjscie(){
	out.close();
}
