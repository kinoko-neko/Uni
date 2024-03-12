#include<bits/stdc++.h>
using namespace std;

namespace obliczenia {

class wektor {
	protected:
	
	double *tab = nullptr; // macierz liczb zmiennopozycyjnych
	const int k; // rozmiar tablicy: k pozycji

	public:

	int size();
	wektor (int siz); // wektro zerowy o okreslonym rozmiarze
	wektor (int siz, const double wsp[]); // konstruktor wielomianu 
	wektor (vector<double> v);
	wektor (std::initializer_list<double> wsp); // lista współczynników
	
	wektor (const wektor &w); // konstruktor kopiujący
	wektor (wektor &&w); // konstruktor przenoszący
	wektor& operator =(const wektor &w); // przypisanie kopiujące
	wektor& operator =(wektor &&w); // przypisanie przenoszące
	~wektor ();
	
	friend istream& operator >> (istream &we, wektor &w); 
	friend ostream& operator << (ostream &wy, const wektor &w);
	
	friend wektor operator-(const wektor &v); // zmiana znaku
	friend wektor operator+(const wektor &x, const wektor &y);
	friend wektor operator-(const wektor &x, const wektor &y);
	friend wektor operator*(const wektor &v, double d);
	friend wektor operator*(double d, const wektor &v);
	// iloczyn skalarny x*y
	friend double operator*(const wektor &x, const wektor &y); 
	double operator [] (int i) const; // do odczytu współczynnika
	double& operator [] (int i); // do zapisu współczynnika 
	
	wektor& operator+=(const wektor &v);
	wektor& operator-=(const wektor &v);
	wektor& operator*=(double d);
	
};

class macierz {
	wektor **tab = nullptr; // macierz wskaźników na wektory
	const int w, k; // rozmiar tablicy: w wierszy i k kolumn

	public:
	
	macierz (int n, int m); // macierz zerowa o określonym rozmiarze
	macierz (const macierz &w); // konstruktor kopiujący
	macierz (macierz &&w); // konstruktor przenoszący
	macierz (int siz, wektor* wsp[]); // konstruktor wielomianu 
	macierz	(vector<wektor* > v);
	macierz (std::initializer_list<wektor*> wsp); // lista współczynników
	
	macierz& operator =(const macierz &w); // przypisanie kopiujące
	macierz& operator =(macierz &&w); // przypisanie przenoszące
	~macierz ();

	friend istream& operator >> (istream &we, macierz &w);
	friend ostream& operator << (ostream &wy, const macierz &w);

	friend macierz operator-(const macierz &m); // zmiana znaku
	friend macierz operator+(const macierz &p, const macierz &q);
	friend macierz operator-(const macierz &p, const macierz &q);
	friend macierz operator*(const macierz &m, double d);
	friend macierz operator*(double d, const macierz &m);
	friend macierz operator*(const macierz &p, const macierz &q);
	friend macierz operator~(const macierz &m); // transpozycja
	
	wektor operator [] (int i) const; // do odczytu współczynnika
	wektor& operator [] (int i); // do zapisu współczynnika 
	
	macierz& operator+=(const macierz &m);
	macierz& operator-=(const macierz &m);
	macierz& operator*=(double d);  
};

}
