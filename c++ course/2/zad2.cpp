#include<bits/stdc++.h>
#include "zad2.hpp"

//ZMIENNA

//konstrukuktory do zmiennej
zmienna::zmienna(){
	wartosc=0.0;
	nazwa="_";
}

zmienna::zmienna(std::string name){
	nazwa=name;
	wartosc=0.0;
}

zmienna::zmienna(std::string name, double war){
	wartosc=war;
	nazwa=name;
}


//gettery + setter do zmiennej

std::string zmienna::get_nazwa(){ return nazwa; } 
double zmienna::get_wartosc(){ return wartosc; }
void zmienna::set_wartosc(double x) {wartosc=x;}


//ZBIOR_ZMIENNYCH	


zbior_zmiennych::zbior_zmiennych(int roz) :N(roz){
	try{
		if(roz<0){
			throw std::invalid_argument("rozmiar tablicy mniejszy od zero\n") ;
		}
		else{
		//	N=roz;
			tab= new zmienna[N];
		}
	}
	catch(std::invalid_argument){
		std::cout<<"rozmiar tablicy ujemny\n";
	}
}

zbior_zmiennych::~zbior_zmiennych(){
	delete[] tab;
}

void zbior_zmiennych::wstaw(zmienna x){
	for(int i=0;i<N;i++){
		if(tab[i].get_nazwa() == "_"){
			tab[i]=x; break;
		}
	}
}

bool zbior_zmiennych::is(std::string name){
	for(int i=0;i<N;i++){
		//std::cout<<"naz i nazwa[i]:"<<i<<" "<<name<<" "<<tab[i].get_nazwa()<<"\n";
		if( name==tab[i].get_nazwa() ) return true;
	}
	return false;
}

void zbior_zmiennych::usun(zmienna x){
	for(int i=0;i<N;i++){
		if(x.get_nazwa()==tab[i].get_nazwa()){
			tab[i]= zmienna(); return;
		}
	}
}

double zbior_zmiennych::get_wartosc(std::string name){
	for(int i=0;i<N;i++){
		if(name==tab[i].get_nazwa()) return tab[i].get_wartosc();
	}
}

void zbior_zmiennych::set_wartosc(std::string name, double war){
	for(int i=0;i<N;i++){
		if(tab[i].get_nazwa()==name){
			tab[i].set_wartosc(war); return;
		}
	}
}
