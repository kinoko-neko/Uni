#include<bits/stdc++.h>
#include "kolor.hpp"
using namespace std;

kolor::kolor (){
	r=0.0; g=0.0; b=0.0;
}

kolor::kolor (double a, double b1, double c){
	if(min(a,min(b1,c)) <0.0 || max(a,max(b1,c))>255.0 ) throw "wartosci poza zakresem";
	r=a; g=b1; b=c; 
}
	
	//set i get
double kolor::get_r(){ return r;}
void kolor::set_r(double x){
	if(x<0.0 || x>255.0) throw "wartosc poza zakresem";
	r=x;
}

double kolor::get_g(){ return g;}
void kolor::set_g(double x){
	if(x<0.0 || x>255.0) throw "wartosc poza zakresem";
	g=x;
}

double kolor::get_b(){ return b;}
void kolor::set_b(double x){
	if(x<0.0 || x>255.0) throw "wartosc poza zakresem";
	b=x;
}
	
	
void kolor::lighten(double x){
	r+=x; g+=x; b+=x;
	r=max(r,0.0); g=max(g,0.0); b=max(b,0.0);
	r=min(r,255.0); g=min(g,255.0); b=min(b,255.0);
}

void kolor::darken(double x){
	r-=x; g-=x; b-=x;
	r=max(r,0.0); g=max(g,0.0); b=max(b,0.0);
	r=min(r,255.0); g=min(g,255.0); b=min(b,255.0);
}

void kolor::add(kolor a){//dodaj kolor
	this->r+=a.get_r(); this->r/=2;
	this->g+=a.get_g(); this->g/=2;
	this->b+=a.get_b(); this->b/=2;
}

//transkolor

transkolor::transkolor(){
	r=0.0; g=0.0; b=0.0; alfa=255.0;
}

transkolor::transkolor(double a,double b1, double c,double d=255.0){
	if(min(min(a,d),min(b1,c)) <0.0 || max(max(a,d),max(b1,c))>255.0 ) throw "wartosci poza zakresem";
	r=a; g=b1; b=c; alfa=d;
}

double transkolor::get_alfa(){return alfa;}
void transkolor::set_alfa(double x){
	if(x<0.0 || x>255.0) throw "wartosc poza zakresem";
}

//nazw kolor

nazwkolor::nazwkolor(){
	r=0.0; g=0.0; b=0.0; alfa=255.0; nazwa="";
}

nazwkolor::nazwkolor(double a, double b1,double c, string name=""){
	if(min(a,min(b1,c)) <0.0 || max(a,max(b1,c))>255.0 ) throw "wartosci poza zakresem";
	for(int i=0;i<name.size();i++){
		if(!(name[i]<='z' && name[i]>='a' ) && !(name[i]<='Z' && name[i]>='A')) throw "zla nazwa";
	}
	r=a; g=b1; b=c; alfa=255.0; nazwa=name;
}
nazwkolor::nazwkolor(double a, double b1,double c,double d, string name=""){
	if(min(min(a,d),min(b1,c)) <0.0 || max(max(a,d),max(b1,c))>255.0 ) throw "wartosci poza zakresem";
	for(int i=0;i<name.size();i++){
		if(!(name[i]<='z' && name[i]>='a' ) && !(name[i]<='Z' && name[i]>='A')) throw "zla nazwa";
	}
	r=a; g=b1; b=c; alfa=d; nazwa=name;
}

string nazwkolor::get_name(){ return nazwa;}
	
