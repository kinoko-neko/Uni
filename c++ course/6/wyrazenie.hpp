#include<bits/stdc++.h>
using namespace std;

class wyrazenie{
	public:
	
	virtual double oblicz() = 0;
	virtual std::string zapis() = 0; //nie wiem czemu dziela ale stack overflow nie klamie
};

class liczba : public wyrazenie{
	double wartosc;
	
	public:
	
	liczba(double val);
	double oblicz();
	std::string zapis();
}; 


class zmienna : public wyrazenie{

	static vector< pair<string ,double> > zmienne;
	std::string nazwa;
	
	public:
	
	static int znajdz(string nazwa);
	static void dodajzmienna(string nazw, double wart){
	int pomi = znajdz(nazw);
	if(pomi==-1)
		zmienne.push_back({nazw,wart});
	else
		zmienne[pomi].second=wart;
	}
	zmienna(string nazwa);
	double oblicz();
	std::string zapis();
	
};

class stala : public wyrazenie{
	protected:
	double wartosc;
	public: 
	double oblicz();
};

class pi: public stala{
	public:
	pi();
	string zapis();
};

class e: public stala{
	public:
	e();
	string zapis();
};

class fi: public stala{
	public:
	fi();
	string zapis();
};

class unar: public wyrazenie{
	protected:
	wyrazenie *arg1;
};

class Sin : public unar{
	public:
	Sin(wyrazenie *w);
	double oblicz();
	string zapis();
};

class Cos: public unar{
	public:
	Cos(wyrazenie *w);
	double oblicz();
	string zapis();
};

class bez: public unar{
	public:
	bez(wyrazenie *w);
	double oblicz();
	string zapis();
};

class przeciw: public unar{
	public:
	przeciw(wyrazenie *w);
	double oblicz();
	string zapis();
};

class Exp: public unar{
	public:
	Exp(wyrazenie *w);
	double oblicz();
	string zapis();
};

class odwrot: public unar{
	public:
	odwrot(wyrazenie *w);
	double oblicz();
	string zapis();
};

class ln: public unar{
	public:
	ln(wyrazenie *w);
	double oblicz();
	string zapis();
};

class binar: public unar{
	protected:
	wyrazenie *arg2;
};

class dodaj: public binar{
	public:
	dodaj(wyrazenie *w1, wyrazenie *w2);
	double oblicz();
	string zapis();
};

class odejmij: public binar{
	public:
	odejmij(wyrazenie *w1, wyrazenie *w2);
	double oblicz();
	string zapis();
};

class mnoz: public binar{
	public:
	mnoz(wyrazenie *w1, wyrazenie *w2);
	double oblicz();
	string zapis();
};

class dziel: public binar{
	public:
	dziel(wyrazenie *w1, wyrazenie *w2);
	double oblicz();
	string zapis();
};

class logarytm: public binar{//podstawa potem logartytmowana
	public:
	logarytm(wyrazenie *w1, wyrazenie *w2);
	double oblicz();
	string zapis();
};

class modulo: public binar{
	public:
	modulo(wyrazenie *w1, wyrazenie *w2);
	double oblicz();
	string zapis();
};

class potenga: public binar{
	public:
	potenga(wyrazenie *w1, wyrazenie *w2);
	double oblicz();
	string zapis();
}; 


