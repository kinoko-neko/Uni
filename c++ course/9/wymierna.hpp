#include<bits/stdc++.h>
using namespace std;

namespace obliczenia{

class wymierna{
	int licz,mian;
	
	int bz(int x);
	int nwd(int a, int b);
	long long int nww(int a, int b);
	long long int nwd(long long int a, long long int b);
	public:
	
	//konstruktor i getter
	wymierna(int a, int b);
	int get_licz();
	int get_mian();
	
	//dzialania
	wymierna& operator+=(wymierna w);
	wymierna& operator-=(wymierna w);
	wymierna& operator*=(wymierna w);
	wymierna& operator/=(wymierna w);  
	
	//friends
	friend wymierna operator!(const wymierna &a);
	
	friend wymierna operator+(const wymierna &a, const wymierna &b); 
	friend wymierna operator-(const wymierna &a, const wymierna &b);
	friend wymierna operator*(const wymierna &a, const wymierna &b);
	friend wymierna operator/(const wymierna &a, const wymierna &b);
	
	friend ostream& operator<< (ostream &wyj, const wymierna &w);
};

}

class wymierna_wyjatek : public logic_error{

	const char* what_arg;
	public:
	wymierna_wyjatek(const char* s): logic_error(s) {}
	const char* what() { return what_arg;}
};

class dzielenieprzez0 : public wymierna_wyjatek{
	public:
	dzielenieprzez0(const char* s = "dzielenie przez 0"): wymierna_wyjatek(s){}
};

class outofrange : public wymierna_wyjatek{
	public:
	outofrange(const char* s="out of range"): wymierna_wyjatek(s){}
};
