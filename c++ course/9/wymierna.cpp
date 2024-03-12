#include<bits/stdc++.h>
#include "wymierna.hpp"
#define ll long long int
using namespace std;
using namespace obliczenia;

int wymierna::bz(int x){
	if(x<0) return -x; return x;
}

int wymierna::nwd(int a, int b){
	if(b==0) return a;
	return nwd(b,a%b);
}

long long int wymierna::nwd(long long int a, long long int b){
	if(b==0) return a;
	return nwd(b,a%b);
}

long long int wymierna::nww(int a, int b){
	return (long long int)(a/(nwd(a,b))) * ((long long int)b);
}

wymierna::wymierna(int n, int m=1){
	if(m==0) throw dzielenieprzez0();
	bool minus= (n<0) ^ (m<0); //ujemna tylko jak jedna z liczb jest ujemna;
	int d= nwd(bz(n), bz(m)); 
	if(minus) licz=-bz(n/d); else licz=bz(n/d);
	mian=bz(m/d);
}

int wymierna::get_licz(){ return licz;}
int wymierna::get_mian(){ return mian;}


wymierna& wymierna::operator+=(wymierna w){
	long long int l2,m2,d;
	m2=nww(mian,w.get_mian());
	l2= ( (long long int)licz * (m2/(long long int)mian )) + ((long long int)w.get_licz() * (m2/(long long int)w.get_mian() ));
	d=nwd(l2,m2);
	l2/=d; m2/=d;
	if(INT_MAX<max(l2,m2)) throw outofrange();
	licz=l2; mian=m2;
	return *this;
}

wymierna& wymierna::operator-=(wymierna w){
	long long int l2,m2,d;
	m2=nww(mian,w.get_mian());
	l2= ( (long long int)licz * (m2/(long long int)mian )) - ((long long int)w.get_licz() * (m2/(long long int)w.get_mian() ));
	d=nwd(l2,m2);
	l2/=d; m2/=d;
	if(INT_MAX<max(l2,m2)) throw outofrange();
	licz=l2; mian=m2;
	return *this;
}

wymierna& wymierna::operator*=(wymierna w){

	bool minus = (licz<0) ^ (w.get_licz()<0);
	licz=bz(licz);
	//skracanie
	
	int d1=nwd(licz,w.get_mian() );
	int d2=nwd(bz(w.get_licz()),mian);
	licz/=d1;
	long long int l2= bz(w.get_licz())/d2;
	long long int m2= w.get_mian()/d1;
	mian/=d2;
	
	long long int l1= l2* (ll)licz;
	long long int m1= (ll)mian * m2;
	if(max(l1,m1)> INT_MAX ) throw outofrange();
	licz=l1; mian=m1;
	if(minus) licz= -licz;
	return *this;
}

wymierna& wymierna::operator/=(wymierna w){
	if(w.licz==0) throw dzielenieprzez0();
	wymierna pomi = wymierna(w.mian, w.licz);
	wymierna pom2 = wymierna(licz,mian);
	pom2*=pomi;
	licz=pom2.get_licz(); mian=pom2.get_mian();
	return *this;	
} 
	

wymierna obliczenia::operator!(const wymierna &w){
	if(w.licz==0) throw dzielenieprzez0();
	if(w.licz>=0) return wymierna(w.mian, w.licz);
	return wymierna(-w.mian, -w.licz);
}

wymierna obliczenia::operator+(const wymierna &a, const wymierna &b){
	wymierna wyn= wymierna(a.licz,a.mian);
	wyn+=b;
	return wyn;
} 

wymierna obliczenia::operator-(const wymierna &a, const wymierna &b){
	wymierna wyn= wymierna(a.licz,a.mian);
	wyn-=b;
	return wyn;
}

wymierna obliczenia::operator*(const wymierna &a, const wymierna &b){
	wymierna wyn= wymierna(a.licz,a.mian);
	wyn*=b;
	return wyn;
}

wymierna obliczenia::operator/(const wymierna &a, const wymierna &b){
	wymierna wyn= wymierna(a.licz,a.mian);
	wyn/=b;
	return wyn;
}


int find(vector<pair<int, int> > &v, int p){
	for(int i=0;i<v.size();i++) {
		if(v[i].first==p) return v[i].second;
	}
	return -1;
}

ostream& obliczenia::operator << (ostream &wy, const wymierna &w){
//	wy<<w.k<<"\n";
	vector<pair<int,int> >pomi;
	string ret="";
	int temp=w.licz;
	int t2,pomi2,rest,roz;
	
	t2=temp/w.mian; 
	temp-= t2*w.mian;
	if(temp==0) { wy<<to_string(t2); return wy; }
	ret= to_string(t2); ret.push_back('.'); temp*=10;
	
	roz=ret.size()-1;
	
	while(true){
	//	if(temp<mian){ temp*=10; ret.push_back('0'); continue;}
		t2=temp/w.mian; roz++;
		temp-= t2*w.mian; rest=temp; temp*=10; ret.push_back(t2+'0');
		if(temp==0) { wy<<ret; return wy; }
		pomi2=find(pomi, rest);
		if(pomi2!=-1){
			for(int i=0;i<pomi2;i++) wy<<ret[i];
			wy<<'(';
			for(int i=pomi2;i<ret.size()-1;i++) wy<<ret[i];
			wy<<')'; return wy;
		}
		pomi.push_back({rest,roz}); 
	}
	return wy;
} 
	
//const char* wymierna_wyjatek::what(){ return what_arg;}


//dzielenieprzez0::dzielenieprzez0(const char* s ): wymierna_wyjatek(s){}
//outofrange::outofrange(const char* s ): wymierna_wyjatek(s){}



