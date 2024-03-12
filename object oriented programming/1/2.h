typedef struct ulamek{
	int licznik,mianownik;
} Ulamek;

void show(Ulamek *u);
Ulamek * nowy_ulamek(int num, int denom);

void add1(Ulamek *a, Ulamek *b);
Ulamek * add2(Ulamek *a, Ulamek *b);

void sub1(Ulamek *a, Ulamek *b);
Ulamek * sub2(Ulamek *a, Ulamek *b);

void mult1(Ulamek *a, Ulamek *b);
Ulamek * mult2(Ulamek *a, Ulamek *b);

void div1(Ulamek *a, Ulamek *b);
Ulamek * div2(Ulamek *a, Ulamek *b);
