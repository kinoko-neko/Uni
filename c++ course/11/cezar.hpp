#include<bits/stdc++.h>
using namespace std;

class wejscie{
	ifstream inp;
	
	public:
	
	wejscie(string a);
	string nastlinia();
	bool eof();
	~wejscie();
};

class wyjscie{
	ofstream out;
	
	public:
	wyjscie(string a);
	void piszlinie(string a);
	~wyjscie();
};
