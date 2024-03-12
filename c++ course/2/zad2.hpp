#include<bits/stdc++.h>

class zmienna{
	std::string nazwa;
	double wartosc;
	
	public:
		zmienna();
		zmienna(std::string);
		zmienna( std::string name, double war);
		std::string get_nazwa();
		double get_wartosc();
		void set_wartosc(double x);
//		~zmienna();
};

class zbior_zmiennych{
	const int N;
	//int siz;
	zmienna *tab;
	
	public:
		zbior_zmiennych(int roz);
		void wstaw(zmienna x);
		bool is(std::string name);
		void usun(zmienna x);
		double get_wartosc(std::string name);
		void set_wartosc(std::string name, double wart);
		~zbior_zmiennych();
};
