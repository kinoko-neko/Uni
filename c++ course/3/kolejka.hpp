#include<bits/stdc++.h>

class kolejka{
	int rozmiar,pocz=0,ile=0;
	std::string *tab;

	public:	
	
	kolejka();
	kolejka(int siz);
	kolejka(std::initializer_list<std::string> lista);
	kolejka(kolejka & kol);
	kolejka(kolejka && kol);
	
	kolejka & operator =(kolejka & kol);
	kolejka & operator =(kolejka && kol);
	
	~kolejka();
	void wstaw(std::string napis);
	std::string usun();
	std::string zprzodu();
	int dlugosc();
};


