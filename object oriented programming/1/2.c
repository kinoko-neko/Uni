#include <stdio.h>
#include <stdlib.h>
#include "2.h"

int nwd(int a, int b){
	if(a<0) a=-a;
	if(b<0) b=-b;
	if(b==0) return a;
	return nwd(b,a%b);
}

int nww(int a, int b){
	int d=nwd(a,b);
	a/=d;
	return a*b;
}

void show(Ulamek *u){
	printf("%d/%d\n",u->licznik,u->mianownik);
}

void skroc(Ulamek * a){
	int d=nwd(a->licznik,a->mianownik);
	a->licznik/=d;
	a->mianownik/=d;
}

Ulamek * nowy_ulamek(int num, int denom){
	Ulamek * u= malloc(sizeof(Ulamek));
	int d=nwd(num,denom);
	u->licznik=num/d;
	u->mianownik=denom/d;
	return u;
}

void add1(Ulamek *a, Ulamek *b){
	int mian=nww(a->mianownik,b->mianownik);
	int pom= mian/(b->mianownik);
	b->licznik*=pom;
	pom=mian/(a->mianownik);
	b->licznik+= pom*(a->licznik);
	b->mianownik=mian;
	skroc(b);
}

Ulamek * add2(Ulamek *a, Ulamek *b){
	Ulamek * u= malloc(sizeof(Ulamek));
	int mian=nww(a->mianownik,b->mianownik);
	u->mianownik=mian;
	u->licznik=(mian/(a->mianownik))*(a->licznik) + (mian/(b->mianownik))*(b->licznik);
	skroc(u);
	return u;
}

void sub1(Ulamek *a, Ulamek *b){
	b->licznik*=(-1);
	add1(a,b);
}

Ulamek * sub2(Ulamek *a, Ulamek *b){
	Ulamek * u= malloc(sizeof(Ulamek));
	int mian=nww(a->mianownik,b->mianownik);
	u->mianownik=mian;
	u->licznik=(mian/(a->mianownik))*(a->licznik) - (mian/(b->mianownik))*(b->licznik);
	skroc(u);
	return u;
}

void mult1(Ulamek *a, Ulamek *b){
	b->licznik*=a->licznik;
	b->mianownik*=a->mianownik;
	skroc(b);
}

Ulamek * mult2(Ulamek *a, Ulamek *b){
	Ulamek * u= malloc(sizeof(Ulamek));
	u->licznik=(a->licznik)*(b->licznik);
	u->mianownik=(a->mianownik)*(b->mianownik);
	skroc(u);
	return u;
}

void div1(Ulamek *a, Ulamek *b){
	int pom=b->licznik;
	b->licznik=b->mianownik;
	b->mianownik=pom;
	
	b->licznik*=a->licznik;
	b->mianownik*=a->mianownik;
	skroc(b);
}

Ulamek * div2(Ulamek *a, Ulamek *b){
	Ulamek * u= malloc(sizeof(Ulamek));
	u->licznik=(a->licznik)*(b->mianownik);
	u->mianownik=(a->mianownik)*(b->licznik);
	skroc(u);
	return u;
}
