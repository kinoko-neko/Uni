#include<bits/stdc++.h>

namespace kalkulator{

    class symbol{
        public:
        virtual double oblicz() =0;
    };

    class operand : public symbol{
        protected:
        double wartosc;

        public:
        virtual double oblicz()=0;
    };

    class liczba : public operand{
        public:
        liczba(double val) { wartosc=val; }
        double oblicz() {return wartosc;}
    };

    class zmienna : public operand{
        static std::vector< std::pair<std::string ,double> > zmienne;
        std::string nazwa;

        public:

        static int znajdz(std::string nazwa); //zwróć pozycje nazwy, jak nie ma to -1;
        static void clear() {zmienne.clear();}
        static void assign(std::string nazw, double wart){
            int pomi = zmienna::znajdz(nazw);
            if(pomi==-1)
                zmienne.push_back({nazw,wart});
            else
                zmienne[pomi].second=wart;
        }
        zmienna(std::string naz) : nazwa(naz) {}
        double oblicz();
    };

    class stala : public operand{
        protected:
        double wartosc;
        public:
        double oblicz() {return wartosc;}
    };

    class pi: public stala{
        public:
        pi();
    };

    class e: public stala{
        public:
        e();
    };

    class fi: public stala{
        public:
        fi();
    };

    class funkcja : public symbol{
        public:
        virtual double oblicz()=0;
    };

    class unar : public funkcja{
    protected:
        symbol *arg1;
        public:
        virtual double oblicz()=0;
    };

    class Sin : public unar{
        public:
        Sin(symbol *w){ arg1=w;}
        double oblicz();
    };

class Cos: public unar{
	public:
	Cos(symbol *w) { arg1=w;}
    double oblicz();
};

class bez: public unar{
	public:
	bez(symbol *w) { arg1=w;}
    double oblicz();
};

class sgn: public unar{
	public:
	sgn(symbol *w) { arg1=w;}
    double oblicz();
};

class Exp: public unar{
	public:
	Exp(symbol *w) { arg1=w;}
    double oblicz();
};

class Floor: public unar{
	public:
	Floor(symbol *w) { arg1=w;}
    double oblicz();
};

class ln: public unar{
	public:
	ln(symbol *w) { arg1=w;}
    double oblicz();
};

class Ceil : public unar{
public:
    Ceil(symbol *w) { arg1=w;}
    double oblicz();
};

class frac : public unar{
public:
    frac(symbol *w) { arg1=w;}
    double oblicz();
};

class Atan : public unar{
public:
    Atan(symbol *w) { arg1=w;}
    double oblicz();
};

class Acot : public unar{
public:
    Acot(symbol *w) { arg1=w;}
    double oblicz();
};

class binar: public funkcja{
	protected:
    symbol *arg1;
	symbol *arg2;
    public:
    virtual double oblicz()=0;
};

class dodaj: public binar{
	public:
	dodaj(symbol *w1, symbol *w2) {arg1=w1; arg2=w2;}
	double oblicz();
};

class odejmij: public binar{
	public:
	odejmij(symbol *w1, symbol *w2) {arg1=w1; arg2=w2;}
	double oblicz();
};

class mnoz: public binar{
	public:
	mnoz(symbol *w1, symbol *w2) {arg1=w1; arg2=w2;}
	double oblicz();
};

class dziel: public binar{
	public:
	dziel(symbol *w1, symbol *w2) {arg1=w1; arg2=w2;}
	double oblicz();
};

class logarytm: public binar{//podstawa potem logartytmowana
	public:
	logarytm(symbol *w1, symbol *w2) {arg1=w1; arg2=w2;}
	double oblicz();
};

class modulo: public binar{
	public:
	modulo(symbol *w1, symbol *w2) {arg1=w1; arg2=w2;}
	double oblicz();
};

class potenga: public binar{
	public:
	potenga(symbol *w1, symbol *w2) {arg1=w1; arg2=w2;}
	double oblicz();
};

class Min : public binar{
public:
    Min(symbol *w1, symbol *w2) {arg1=w1; arg2=w2;}
    double oblicz();
};

class Max : public binar{
public:
    Max(symbol *w1, symbol *w2) {arg1=w1; arg2=w2;}
    double oblicz();
};

}
