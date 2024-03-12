#include<bits/stdc++.h>

using namespace std;

class kolor{
	protected:
	
	double r,g,b;
	
	public:
	
	kolor ();
	kolor (double a, double b1, double c);
	
	//set i get
	double get_r();
	void set_r(double x);
	double get_g();
	void set_g(double x);
	double get_b();
	void set_b(double x);
	
	void lighten(double x);
	void darken(double x);

	void add(kolor a);//dodaj kolor
};

class transkolor : public kolor{
	
	protected:
	
	double alfa;
	
	public:
	
	transkolor();
	transkolor(double a,double b1, double c,double d);
	double get_alfa();
	void set_alfa(double x);
};

class nazwkolor : public transkolor{
	protected:
	string nazwa;
	
	public: 
	
	nazwkolor();
	nazwkolor(double a, double b1,double c, string name);
	nazwkolor(double a, double b1,double c,double d, string name);
	string get_name();
};

