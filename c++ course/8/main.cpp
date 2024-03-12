#include<bits/stdc++.h>
#include "matrix.cpp"

using namespace std;
using namespace obliczenia;


int main(){

	double t1[5] = {1,2,4,5,2};
	
	wektor w1	=	wektor(2);
	wektor w2	= wektor(5,t1);
	wektor w3	=	wektor({21,5,6,3.56,3}); 
	wektor w4 = w3*4;
	cout<<w4<<"\n";
	cout<< w4+w3<<"\n";
	cout<< w4*w3<<"\n";
	cout<< w4[1]<<" ";
	w4[1]=53;
	cout<<w4[1]<<"\n";
	w3+=w4;
	cout<<w3<<"\n";
	
	wektor w5	=	wektor({1,0});
	wektor w6 = wektor({0,1});
	
	wektor* t2[2]	=	{&w5,&w6};
	macierz m1	=	macierz(2,2);
	macierz	m2	=	macierz(2,t2);
	macierz m3	=	macierz({&w6,&w5});

	cout<<m2<<"\n";
	cout<<m3<<"\n";
	cout<<"kopiowanie\n";
	macierz m3_c	=	m3;
	cout<<m3_c<<"\n";
	m3*=2;
	cout<<m3<<"\n";
	cout<<m3_c<<"\n";
	cout<<"mnozenie\n";
	macierz m4	=	m3*2;	
	cout<<m4<<"\n";
	cout<<"ujemna\n";
	macierz m5	=	-m4;
	cout<<m5<<"\n";
	cout<<m4<<"\n";
	cout<<m5[1][0]<<"\n"; 
	macierz m6	=	m5 -m4; 
	cout<<m6<<"\n";
	macierz m7	=	m5	+m4;
	cout<<m7<<"\n";  
	//cout<<m2;
}
