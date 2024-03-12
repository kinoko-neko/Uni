#include<bits/stdc++.h>
#include "punkt.hpp"


using namespace std;

punkt::punkt(double a=0.0, double b=0.0){
	x=a; y=b;
}

double punkt::odleglosc(punkt a){
	double pom1=a.x-this->x;
	double pom2=a.y-this->y;
	
	pom1*=pom1; pom2*=pom2;
	
	return sqrt(pom1+pom2);
}

bool punkt::wspolniniowe(punkt a, punkt b){
	double o1=this->odleglosc(a),o2=a.odleglosc(b),o3=this->odleglosc(b);
	return ( ((o1+o2+o3)- 2*(max(o1,max(o2,o3) ) ))<=0.01 );//przyrównywanie na doublach
	
}
//punkt nazw

punktnazw::punktnazw(){
	x=0.0; y=0.0; nazwa="";
}

punktnazw::punktnazw(double a, double b, string name=""){
	if(name!="" && !(name[0]<='z' && name[0]>='a' ) && !(name[0]<='Z' && name[0]>='A') ) throw "zla nazwa";
	
	for(int i=1;i<name.size();i++){
		if(!(name[i]<='z' && name[i]>='a' ) && !(name[i]<='Z' && name[i]>='A') && !(name[i]>='0' && name[i]<='9')) throw "zla nazwa";
	}
	x=a; y=b; nazwa=name;
}

//punkt kol

punktkol::punktkol(){
	x=0.0; y=0.0; kol= transkolor();
}

punktkol::punktkol(double a, double b, transkolor k= transkolor()){
	x=a; y=b; kol=k;
}

//punktkolnazw

punktkolnazw::punktkolnazw(){
	x=0.0; y=0.0; kol=transkolor(); nazwa="";
}

punktkolnazw::punktkolnazw(double a, double b, transkolor k= transkolor(), string name=""){
	if(name!="" && !(name[0]<='z' && name[0]>='a' ) && !(name[0]<='Z' && name[0]>='A') ) throw "zla nazwa";
	
	for(int i=1;i<name.size();i++){
		if(!(name[i]<='z' && name[i]>='a' ) && !(name[i]<='Z' && name[i]>='A') && !(name[i]>='0' && name[i]<='9')) throw "zla nazwa";
	}
	
	x=a; y=b; kol=k; nazwa=name;
}

//wektor2d
wektor2d::wektor2d(double a=0.0, double b=0.0){
	x=a; y=b;
}

wektor3d::wektor3d(double a=0.0, double b=0.0, double c=0.0){
	x=a; y=b; z=c;
}
//punkt2d

punkt2d::punkt2d(double a=0.0, double b=0.0){
	x=a; y=b;
}

void punkt2d::transpose(wektor2d v){
	x+=v.x;
	y+=v.y;
}

//punkt3d

punkt3d::punkt3d(double a=0.0, double b=0.0, double c=0.0){
	x=a; y=b; z=c;
}

void punkt3d::transpose(wektor3d v){
	x+=v.x; y+=v.y; z+=v.z;
}

double punkt3d::odleglosc(punkt3d a){
	double pom1=a.x-(this->x);
	double pom2=a.y-(this->y);
	double pom3=a.z-(this->z);
	pom1*=pom1; pom2*=pom2; pom3*=pom3;
	
	return sqrt(pom1+pom2+pom3);
}

bool punkt3d::wspolliniowe(punkt3d a, punkt3d b){
	double o1=this->odleglosc(a),o2=a.odleglosc(b),o3=this->odleglosc(b);
	return ( ((o1+o2+o3)- 2*(max(o1,max(o2,o3) ) ))<=0.01 );//przyrównywanie na doublach
}
