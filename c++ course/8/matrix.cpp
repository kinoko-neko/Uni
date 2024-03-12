#include<bits/stdc++.h>
#include "matrix.hpp"
using namespace std;
using namespace obliczenia; 

wektor::wektor (int siz) : k(siz){
	if(siz<0) throw "zly rozmiar";
	tab	=	new double[siz];
} // wektor zerowy o okreslonym rozmiarze

wektor::wektor (int siz, const double wsp[]) : k(siz){
	if(siz<0) throw "zly rozmiar";
	tab =	new double[siz];
	for(int i=0;i<siz;i++) tab[i]=wsp[i];
} // konstruktor wektora

wektor::wektor (vector<double> v): k(v.size()){
	tab =	new double[v.size()];
	for(int i=0;i<v.size();i++) tab[i]=v[i];
}

wektor::wektor (std::initializer_list<double> wsp): k(wsp.size()){ // lista współczynników
	tab	=	new	double[wsp.size()];
	int pomi=0;
	for(auto x : wsp){
    tab[pomi]=x; pomi++;
  }
}
	
wektor::wektor (const wektor &w):	k(w.k){ // konstruktor kopiujący
	tab	=	NULL;
	tab	=	new	double[w.k];
	for(int i=0;i<w.k;i++) tab[i]=w.tab[i];
}	

wektor::wektor (wektor &&w):	k(w.k){ // konstruktor przenoszący
	tab	=	w.tab;
	w.tab	=	NULL;
}

wektor& wektor::operator =(const wektor &w)	{ // przypisanie kopiujące
	if(k!=w.k){
		int *ptr;
		ptr	=	const_cast<int*>(&k);
		*ptr	=	w.k;
	}
	if(&w!=this){
		tab=NULL;	
		tab	=	new	double[w.k];
		for(int i=0;i<w.k;i++) tab[i]=w.tab[i];
	}
	return *this;
}	

wektor& wektor::operator =(wektor &&w){ // przypisanie przenoszące
	if(k!=w.k) {
		int *ptr;
		ptr	=	const_cast<int*>(&k);
		*ptr	=	w.k;
	}
	if(&w!=this){
		std::swap(this->tab,w.tab);
	}
	return *this;
}

wektor::~wektor (){
	delete[] tab; 
}

istream& obliczenia::operator >> (istream &we, wektor &w){
	int pomi;
	int *ptr =	const_cast<int*>(&w.k); 
	we>> (pomi);
	if (pomi<0) throw"rozmiar mniejszy od 1";
	*ptr	=	pomi;
	w.tab	=	new double[pomi];	
	for(int i=0;i<=pomi;i++) we>>w.tab[i];
	return we;
}  

ostream& obliczenia::operator << (ostream &wy, const wektor &w){
//	wy<<w.k<<"\n";
	for(int i=0;i<w.k;i++) wy<<w.tab[i]<<" ";
	return wy;
} 
	
wektor obliczenia::operator-(const wektor &v){ // zmiana znaku
	wektor w	=	v;
	for(int i=0;i<w.k;i++) w.tab[i]= -w.tab[i];
	return w;
}
wektor obliczenia::operator+(const wektor &x, const wektor &y){
	if(x.k!=y.k) throw	"różne rozmiary";
	wektor w	=	wektor(x.k);
	for(int	i=0;i<w.k;i++) w.tab[i]= x.tab[i]+y.tab[i];
	return w;
}

wektor obliczenia::operator-(const wektor &x, const wektor &y){
	if(x.k!=y.k) throw	"różne rozmiary";
	wektor w	=	wektor(x.k);
	for(int	i=0;i<w.k;i++) w.tab[i]= x.tab[i]-y.tab[i];
	return w;
}

wektor obliczenia::operator*(const wektor &v, double d){
	wektor w	=	wektor(v.k);
	for(int	i=0;i<w.k;i++) w.tab[i]= v.tab[i]*d;
	return w;
}

wektor obliczenia::operator*(double d, const wektor &v){
	wektor w	=	wektor(v.k);
	for(int	i=0;i<w.k;i++) w.tab[i]= v.tab[i]*d;
	return w;
}
	// iloczyn skalarny x*y
double obliczenia::operator*(const wektor &x, const wektor &y){
	if(x.k!=y.k) throw	"różne rozmiary";
	double wyn	=	0.0;
	for(int	i=0;i<x.k;i++) wyn+=x.tab[i]*y.tab[i];
}

int wektor::size() {return k; }

double wektor::operator [] (int i) const{
	if(i<0) throw invalid_argument("ujemny rozmiar\n");
	if(i>k) throw invalid_argument("wyjscie poza zakres\n");
	return tab[i];
} // do odczytu współczynnika

double& wektor::operator [] (int i){
	if(i<0) throw invalid_argument("ujemny rozmiar\n");
	if(i>k) throw invalid_argument("wyjscie poza zakres\n");
	return tab[i];
} // do zapisu współczynnika


wektor& wektor::operator+=(const wektor &v){
	if(k!=v.k) throw	"różne rozmiary";
	for(int	i=0;i<k;i++) tab[i] += v.tab[i];
	return *this;
}
wektor& wektor::operator-=(const wektor &v){
	if(k!=v.k) throw	"różne rozmiary";
	for(int	i=0;i<k;i++) tab[i] -= v.tab[i];
	return *this;
}
wektor& wektor::operator*=(double d){
	for(int	i=0;i<k;i++) tab[i] *= d;
	return *this;
}


macierz::macierz (int n, int m):	w(n), k(m){ // macierz zerowa o określonym rozmiarze	
	tab	=	new	wektor*[m];
}

macierz::macierz (const macierz &m):	w(m.w), k(m.k){ // konstruktor kopiujący
	tab	=	NULL;
	tab	=	new	wektor*[m.w];
	for(int i=0;i<=m.w;i++) tab[i]=m.tab[i];
}

macierz::macierz (macierz &&m): w(m.w),	k(m.k) { // konstruktor przenoszący
	tab	=	m.tab;
	m.tab	=	NULL;
}

macierz::macierz (int siz, wektor* wsp[]): k(siz), w((*wsp[0]).size()){ // konstruktor 
	if(siz<0) throw "zly rozmiar";
	tab	=	new wektor*[siz];
	int dl= wsp[0]->size();
	for(int i=0;i<siz;i++){
		int pomi	=	wsp[i]->size();
		if(pomi<0 or pomi!=dl) throw "złe długośći kolumn";
		tab[i]=wsp[i];
	}
}

macierz::macierz (std::initializer_list<wektor*> wsp): k(wsp.size()), w( (*wsp.begin())->size()){ // lista współczynników
	tab	=	new wektor* [wsp.size()];
	int dl=(*wsp.begin())->size();
	int pomi=0;
	for(auto x : wsp){
		if( x->size()<0 or x->size()!=dl) throw "złe długośći kolumn";
    tab[pomi]=x; pomi++;
  }
}

macierz::macierz (vector<wektor*> v): w(v.size()), k(v[0]->size()){
	tab	=	new	wektor* [v.size()];
	for(int i=0;i<v.size();i++) tab[i]=v[i];
}
	
macierz& macierz::operator =(const macierz &m){ // przypisanie kopiujące
	if(k!=m.k){
		int *ptr;
		ptr	=	const_cast<int*>(&k);
		*ptr	=	m.k;
		ptr	=	const_cast<int*>(&w);
		*ptr	=	m.w;
	}
	if(&m!=this){
		tab=NULL;	
		tab	=	new	wektor*[m.k];
		for(int i=0;i<=m.k;i++){
			 wektor *wiktor	=	new wektor(m.w);
			 *wiktor	=	*m.tab[i];
			 tab[i]	=	wiktor;
			// tab[i]=m.tab[i];
		}
	}
	return *this;
}

macierz& macierz::operator =(macierz &&m){ // przypisanie przenoszące
	if(k!=m.k) {
		int *ptr;
		ptr	=	const_cast<int*>(&k);
		*ptr	=	m.k;
		ptr	=	const_cast<int*>(&w);
		*ptr	=	m.w;
	}
	if(&m!=this){
		std::swap(this->tab,m.tab);
	}
	return *this;
}	
macierz::~macierz (){
	delete[] tab;
}
	
macierz obliczenia::operator-(const macierz &m){ // zmiana znaku
	macierz ret	=	m;
	int pomi=0;
	
	for(int i=0;i<m.k;i++){	
    *ret.tab[pomi] = -(*ret.tab[pomi]); pomi++;
  }
  return ret;
}

macierz obliczenia::operator+(const macierz &p, const macierz &q){
	if(p.k!=q.k or p.w!=q.w) throw "zle wymiary";
	macierz ret	=	p;
	for(int i=0;i<p.k;i++){
	//	wektor v	=	*p.tab[i]  + *q.tab[i];
    *ret.tab[i] += *q.tab[i];
  }
  return ret;
} 

macierz obliczenia::operator-(const macierz &p, const macierz &q){
	if(p.k!=q.k or p.w!=q.w) throw "zle wymiary";
	macierz ret	=	p;
	for(int i=0;i<p.k;i++){
	//	wektor v	=	*p.tab[i]  + *q.tab[i];
    *ret.tab[i] -= *q.tab[i];
  }
  return ret;
}

macierz obliczenia::operator*(const macierz &m, double d){
	macierz ret	=	m;
	for(int i=0;i<m.k;i++){
    *ret.tab[i] *= d;
  }
  return ret;
}

macierz obliczenia::operator*(double d, const macierz &m){
   macierz ret	=	m;
	for(int i=0;i<m.k;i++){
    *ret.tab[i] *= d;
  }
  return ret;
}

macierz obliczenia::operator~(const macierz &m){ // transpozycja
	vector<wektor* >v1;
	v1.clear();
	for(int i=0;i<m.k;i++){
		vector<double> v2;
		v2.clear();
		for(int j=0;j<m.w;j++){
			v2.push_back( (*m.tab[j])[i]);	
		}
		wektor wiktor	=	wektor(v2);
		v1.push_back(&wiktor);	
	}
	return macierz(v1);
}

macierz obliczenia::operator*(const macierz &p, const macierz &q){
	if(p.k != q.w) throw "zle wymiary";
	macierz pomi = ~p;
	vector<wektor* >v1;
	v1.clear();
	for(int i=0;i<q.k;i++){
		vector<double>v2;
		v2.clear();
		for(int j=0;j<p.w;j++){
			v2.push_back((*q.tab[i])*(*pomi.tab[j]));
		}
		wektor wiktor	=	wektor(v2);
		v1.push_back(&(wiktor));
	}
	return macierz(v1);
}


macierz& macierz::operator+=(const macierz &m){
	if(k!=m.k or w!=m.w) throw "zle wymiary";
	for(int i=0;i<k;i++){
		*tab[i] += *m.tab[i];
  }
  return *this;
}

macierz& macierz::operator-=(const macierz &m){
	if(k!=m.k or w!=m.w) throw "zle wymiary";
	for(int i=0;i<k;i++){
		*tab[i] += *m.tab[i];
  }
  return *this;
}

macierz& macierz::operator*=(double d){
	for(int i=0;i<k;i++){
		*tab[i] *= d;
  }
  return *this;
}

wektor macierz::operator [] (int i) const{
	if(i<0) throw invalid_argument("ujemny rozmiar\n");
	if(i>k) throw invalid_argument("wyjscie poza zakres\n");
	return *tab[i];
} // do odczytu współczynnika

wektor & macierz::operator [] (int i){
	if(i<0) throw invalid_argument("ujemny rozmiar\n");
	if(i>k) throw invalid_argument("wyjscie poza zakres\n");
	return *tab[i];
} // do zapisu współczynnika

istream& obliczenia::operator >> (istream &we, macierz &w){
	int pomi;
	int *ptr =	const_cast<int*>(&w.k); 
	we>> (pomi);
	if (pomi<0) throw"rozmiar mniejszy od 1";
	*ptr	=	pomi;
	ptr =	const_cast<int*>(&w.w);
	we>>pomi;
	if (pomi<0) throw"rozmiar mniejszy od 1";
	*ptr	=	pomi;
	
	w.tab	=	new wektor* [w.k];	
	for(int i=0;i<=w.k;i++){
		wektor wiktor = wektor(w.w);
		we>>wiktor;
		w.tab[i]=&wiktor;
	}
	return we;
}  

ostream& obliczenia::operator << (ostream &wy, const macierz &w){
	wy<<"n ="<<w.k<<" m="<<w.w<<"\n";
	for(int i=0;i<w.k;i++) wy<<(*w.tab[i])<<"\n";
	return wy;
}
