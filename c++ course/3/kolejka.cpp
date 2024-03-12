//#include<bits/stdc++.h>
#include "kolejka.hpp"

kolejka::kolejka(){
	tab= new std::string [1];
	rozmiar=1;// pocz=-1;
}
	
kolejka::kolejka(int siz){
	if(siz<0) throw std::invalid_argument("ujemny rozmiar");
	tab= new std::string [siz];
	rozmiar=siz; //pocz=-1;
}

kolejka::kolejka(std::initializer_list<std::string> lista){
	rozmiar=lista.size();
	
	tab= new std::string[rozmiar];
	for(auto x : lista){
    wstaw(x);
  }
  //ile=lista.size();
}

kolejka::kolejka(kolejka & kol){
	tab=NULL;
	
	rozmiar=kol.rozmiar;
	tab= new std::string [rozmiar];
	ile=kol.ile;
	pocz=kol.pocz;
	for(int i=0;i<rozmiar;i++) tab[i]=kol.tab[i];
}

kolejka:: kolejka(kolejka && kol){
	rozmiar=kol.rozmiar;
	ile=kol.ile;
	pocz=kol.pocz;
	tab=kol.tab;
	kol.tab=NULL;
}

kolejka & kolejka::operator =(kolejka & kol){
	if(&kol!=this){
		this->~kolejka();
		rozmiar=kol.rozmiar;
		tab= new std::string [rozmiar];
		ile=kol.ile;
		pocz=kol.pocz;
		for(int i=0;i<rozmiar;i++) tab[i]=kol.tab[i]; 
	}
	
	return *this;
}

kolejka & kolejka::operator =(kolejka && kol){
	if(&kol!=this){
		std::swap(this->ile,kol.ile);
		std::swap(this->rozmiar,kol.rozmiar);
		std::swap(this->pocz,kol.pocz);
		std::swap(this->tab,kol.tab);
	}
	return *this;
}
	
kolejka::~kolejka(){
	delete[] tab;
}

void kolejka::wstaw(std::string napis){
	try{
		if(ile==rozmiar) throw "Za dużo el";
	}
	catch(...){
		std::cout<<"przekroczono rozmiar kolejki\n";
	}
	tab[(pocz+ile)%rozmiar]=napis; ile++;
}

std::string kolejka:: usun(){
	try{
		if(ile==0) throw "kolejak pusta";
	}
	catch(...){
		std::cout<<"kolejka pusta\n";
	}
	std::string ret=tab[pocz];
	pocz++; if(pocz==rozmiar) pocz=0;
	ile--;
	return ret;
}

std::string kolejka:: zprzodu(){
	try{
		if(ile==0) throw "kolejka pusta";
	}
	catch(...){
		std::cout<<"kolejka pusta\n";
	}
	return tab[pocz];
}

int kolejka:: dlugosc(){
	return ile;
}
