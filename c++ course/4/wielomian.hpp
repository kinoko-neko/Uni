#include<bits/stdc++.h>
#include<initializer_list>
using namespace std;
class wielomian{
	int n;
	double *w;
	
	public: 

	wielomian (int st, double wsp); // konstruktor jednomianu
	wielomian (int st, const double wsp[]); // konstruktor wielomianu
	wielomian (std::initializer_list<double> wsp); // lista współczynników
	wielomian (const wielomian &w); // konstruktor kopiujący
	wielomian (wielomian &&w); // konstruktor przenoszący
	wielomian& operator =(const wielomian &w); // przypisanie kopiujące
	wielomian& operator =(wielomian &&w); // przypisanie przenoszące
	~wielomian (); 
	friend istream& operator >> (istream &we, wielomian &w);
	friend ostream& operator << (ostream &wy, const wielomian &w);
	friend wielomian operator + (const wielomian &u, const wielomian &v);
	friend wielomian operator - (const wielomian &u, const wielomian &v);
	friend wielomian operator * (const wielomian &u, const wielomian &v);
	friend wielomian operator * (const wielomian &u, double c);
	wielomian& operator += (const wielomian &v);
	wielomian& operator -= (const wielomian &v);
	wielomian& operator *= (const wielomian &v);
	wielomian& operator *= (double c);
	double operator () (double x) const; // wartość wielomianu dla x
	double operator [] (int i) const; // do odczytu współczynnika
	double& operator [] (int i); // do zapisu współczynnika
	int get_stopien();
};
