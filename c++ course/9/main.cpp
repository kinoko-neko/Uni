#include<bits/stdc++.h>
#include "wymierna.cpp"

using namespace obliczenia;
using namespace std;

void wyp(wymierna a){
	cout<<a.get_licz()<<" "<<a.get_mian()<<"\n";
}
int main(){

	wymierna w1 = wymierna(1,2);
	cout<<w1.get_licz()<<" "<<w1.get_mian()<<"\n"; 
//	wymierna w2	= wymierna(2,0);
	wymierna w3 = wymierna(2,3);
	w3*=w1;
	w1/=wymierna(3,2);
	cout<<w3.get_licz()<<" "<<w3.get_mian()<<"\n";
	cout<<w1.get_licz()<<" "<<w1.get_mian()<<"\n";
	wymierna w4 = wymierna(1,6);
	w4+=wymierna(2,3);
	cout<<w4.get_licz()<<" "<<w4.get_mian()<<"\n";
	w4*=wymierna(2,-3);
	cout<<w4.get_licz()<<" "<<w4.get_mian()<<"\n";
	wymierna w5 = !wymierna(3,2);
	cout<<w5.get_licz()<<" "<<w5.get_mian()<<"\n";
	wymierna w6= w5-w1;
	wyp(w5); wyp(w1); wyp(w6);
	wymierna w7= wymierna(1,2);
	cout<<w1<<"\n"<<w7<<"\n";
}
