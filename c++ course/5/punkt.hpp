#include<bits/stdc++.h>
#include "kolor.cpp"
using namespace std;

class punkt{
	protected:
	
	double x,y;
	
	public:
	
	punkt(double a,double b);
	double odleglosc(punkt a);
	bool wspolniniowe(punkt a, punkt b);
	
};

class punktnazw : public virtual punkt {
	protected:
	string nazwa;
	
	public:
	
	punktnazw();
	punktnazw(double a, double b, string name);
};

class punktkol : public virtual punkt {
	protected:
	transkolor kol;	
	
	public:
	
	punktkol();
	punktkol(double a, double b, transkolor k);
};

class punktkolnazw: public punktnazw, public punktkol {
	public:
	
	punktkolnazw();
	punktkolnazw(double a, double b, transkolor k, string name);
};

class wektor2d{
	public:
	double x,y;
	wektor2d(double a, double b);
};

class wektor3d{
	public:
	double x,y,z;
	wektor3d(double a, double b, double c);
};

class punkt2d : public punkt {
	public:
	
	punkt2d(double a, double b);
	void transpose(wektor2d v);
};

class punkt3d : public punkt2d {
	protected:
	double x,y,z;
	
	public: 
	
	punkt3d(double a, double b, double c);
	void transpose(wektor3d v);
	double odleglosc(punkt3d a);
	bool wspolliniowe(punkt3d a, punkt3d b);
};


