#include "wyrazenie.hpp"
#include<bits/stdc++.h>

using namespace std;
vector<pair<string, double> > zmienna::zmienne;

//liczba

liczba::liczba(double val){ this->wartosc=val;}
double liczba::oblicz(){ return wartosc;}
std::string liczba::zapis(){return std::to_string(wartosc);}

//zmienna
int zmienna::znajdz(string nazw){
	for(int i=0;i< zmienna::zmienne.size();i++){
		if(zmienna::zmienne[i].first==nazw) return i;
	}
	return -1;
}



zmienna::zmienna(std::string nazwa){this->nazwa=nazwa; }

double zmienna::oblicz(){
	int pomi = znajdz(nazwa);
	if(pomi==-1) throw "brak zmiennej";
	return zmienna::zmienne[pomi].second;
}

string zmienna::zapis(){return nazwa;}

//stale

double stala::oblicz(){return this->wartosc;}//mniej pisania 

pi::pi(){wartosc=3.14;}
string pi::zapis(){return "pi";}

e::e(){this->wartosc=2.71;}
string e::zapis(){return "e";}

fi::fi(){this->wartosc=1.61;}
string fi::zapis(){return "fi";}

//wyrazenia unarne


Sin::Sin(wyrazenie *w){this->arg1=w;}
double Sin::oblicz(){return sin(arg1->oblicz()); }
string Sin::zapis(){return "sin("+arg1->zapis()+")";}

Cos::Cos(wyrazenie *w){this->arg1=w;}
double Cos::oblicz(){return cos(arg1->oblicz()); }
string Cos::zapis(){return "cos("+arg1->zapis()+")";}

bez::bez(wyrazenie *w){this->arg1=w;}
double bez::oblicz(){
	double pomi=arg1->oblicz();
	if(pomi<0) pomi=-pomi;
	return pomi; 
}
string bez::zapis(){return "|"+arg1->zapis()+"|";}

przeciw::przeciw(wyrazenie *w){this->arg1=w;}
double przeciw::oblicz(){return -(arg1->oblicz()); }
string przeciw::zapis(){return "-("+arg1->zapis()+")";}

Exp::Exp(wyrazenie *w){this->arg1=w;}
double Exp::oblicz(){return exp(arg1->oblicz()); }
string Exp::zapis(){return "e^("+arg1->zapis()+")";}

odwrot::odwrot(wyrazenie *w){this->arg1=w;}
double odwrot::oblicz(){
	double pomi=(arg1->oblicz()); 
	if(pomi==0.0) throw "dzielenie przez 0";
	return 1/pomi;
}
string odwrot::zapis(){return "1/("+arg1->zapis()+")";}

ln::ln(wyrazenie *w){this->arg1=w;}
double ln::oblicz(){
	double pomi=(arg1->oblicz()); 
	if(pomi==0.0) throw "log z 0";
	return log(pomi);
}

string ln::zapis(){return "ln("+arg1->zapis()+")";}

//wyrazenia binarne

dodaj::dodaj(wyrazenie *w1, wyrazenie *w2){this->arg1=w1; this->arg2=w2;}
double dodaj::oblicz(){return (arg1->oblicz())+(arg2->oblicz()); }
string dodaj::zapis(){return "("+arg1->zapis()+"+"+arg2->zapis()+")";}

odejmij::odejmij(wyrazenie *w1, wyrazenie *w2){this->arg1=w1; this->arg2=w2;}
double odejmij::oblicz(){return (arg1->oblicz())-(arg2->oblicz()); }
string odejmij::zapis(){return "("+arg1->zapis()+"-"+arg2->zapis() +")";}

mnoz::mnoz(wyrazenie *w1, wyrazenie *w2){this->arg1=w1; this->arg2=w2;}
double mnoz::oblicz(){return (arg1->oblicz())*(arg2->oblicz()); }
string mnoz::zapis(){return arg1->zapis()+"*"+arg2->zapis();}

dziel::dziel(wyrazenie *w1, wyrazenie *w2){this->arg1=w1; this->arg2=w2;}
double dziel::oblicz(){
	double pomi = arg2->oblicz();
	if(pomi==0.0) throw "dzielenie przez 0";	
	return (arg1->oblicz())/pomi; 
}
string dziel::zapis(){return arg1->zapis()+"/"+arg2->zapis();}

logarytm::logarytm(wyrazenie *w1, wyrazenie *w2){this->arg1=w1; this->arg2=w2;}
double logarytm::oblicz(){ //podstawa potem logarytmowana
	double pom1 = (arg1->oblicz());
	double pom2 = (arg2->oblicz()); 
	if(pom1<=0.0 or pom1==1.0) throw "zla podstwawa logarytmu";
	if(pom2<=0.0) throw "zla liczba logarytmowana";
	return log2(pom2)/log2(pom1);
}
string logarytm::zapis(){return "log("+arg1->zapis()+","+arg2->zapis()+")";}

modulo::modulo(wyrazenie *w1, wyrazenie *w2){this->arg1=w1; this->arg2=w2;}
double modulo::oblicz(){
	double pomi = arg2->oblicz();
	if(pomi==0.0) throw "dzielenie przez 0";
	return fmod(arg1->oblicz(),pomi); 
}
string modulo::zapis(){return arg1->zapis()+"%("+arg2->zapis() +")";}

potenga::potenga(wyrazenie *w1, wyrazenie *w2){this->arg1=w1; this->arg2=w2;}
double potenga::oblicz(){return pow(arg1->oblicz(),arg2->oblicz()); }
string potenga::zapis(){return arg1->zapis()+"^("+arg2->zapis() +")";}
