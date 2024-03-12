#include<bits/stdc++.h>
#include "onp.hpp"
using namespace kalkulator;
std::vector<std::pair<std::string, double> > zmienna::zmienne;


//liczba::liczba(double val){ this->wartosc=val;}

int zmienna::znajdz(std::string nazw){
    for(int i=0;i< zmienne.size();i++){
		if(zmienne[i].first==nazw) return i;
	}
	return -1;
}

double zmienna::oblicz(){
    int pomi = zmienna::znajdz(nazwa);
	if(pomi==-1) throw "brak zmiennej";
	return zmienne[pomi].second;
}

pi::pi(){wartosc=3.14;}
e::e(){this->wartosc=2.71;}
fi::fi(){this->wartosc=1.61;}

//wyrażenia unarne

double Sin::oblicz(){return sin(arg1->oblicz()); }
double Cos::oblicz(){return cos(arg1->oblicz()); }
double bez::oblicz(){
	double pomi=arg1->oblicz();
	if(pomi<0) pomi=-pomi;
	return pomi;
}
double sgn::oblicz(){
    double pomi =arg1->oblicz();
    if(pomi<0.0) return -1.0;
    if(pomi>0.0) return 1.0;
    return 0.0;
}

double Exp::oblicz(){return exp(arg1->oblicz()); }

double Floor::oblicz(){
	double pomi=(arg1->oblicz());
	return floor(pomi);
}

double ln::oblicz(){
	double pomi=(arg1->oblicz());
	if(pomi==0.0) throw "log z 0";
	return log(pomi);
}

double Ceil::oblicz(){
	double pomi=(arg1->oblicz());
	return ceil(pomi);
}

double frac::oblicz(){
    double pomi=arg1->oblicz();
    return pomi - floor(pomi);
}

double Atan::oblicz(){
    double pomi=arg1->oblicz();
    return atan(pomi);
}

double Acot::oblicz(){
    double pomi=arg1->oblicz();
    return -atanf64(-pomi);
}

//wyrażenia binarne
double dodaj::oblicz(){return (arg1->oblicz())+(arg2->oblicz()); }

double odejmij::oblicz(){return (arg1->oblicz())-(arg2->oblicz()); }

double mnoz::oblicz(){return (arg1->oblicz())*(arg2->oblicz()); }

double dziel::oblicz(){
	double pomi = arg2->oblicz();
	if(pomi==0.0) throw "dzielenie przez 0";
	return (arg1->oblicz())/pomi;
}

double logarytm::oblicz(){ //podstawa potem logarytmowana
	double pom1 = (arg1->oblicz());
	double pom2 = (arg2->oblicz());
	if(pom1<=0.0 or pom1==1.0) throw "zla podstwawa logarytmu";
	if(pom2<=0.0) throw "zla liczba logarytmowana";
	return log2(pom2)/log2(pom1);
}

double modulo::oblicz(){
	double pomi = arg2->oblicz();
	if(pomi==0.0) throw "dzielenie przez 0";
	return fmod(arg1->oblicz(),pomi);
}
double potenga::oblicz(){return pow(arg1->oblicz(),arg2->oblicz()); }

double Min::oblicz(){ return std::min(arg1->oblicz(),arg2->oblicz());}
double Max::oblicz(){ return std::max(arg1->oblicz(),arg2->oblicz());}


