#include "rozgrywka.hpp"
#include "gracz.hpp"
#include "bledy.hpp"
#include "plansza.hpp"
#include "pozycja.hpp"
#include "pionek.hpp"
using namespace std;

rozgrywka::rozgrywka(plansza *p1, gracz *g3, gracz *g4){
    g = false;
    e = bledy();
    p=p1;
    g1=g3;
    g2=g4;
}

string rozgrywka::wstaw(string num, string poz){
    if(!e.numer(num) || !e.czy_pozycja(poz)) return "bledny format\n";
    int n = stoi(num);
    pozycja p1 = pozycja(poz);
    gracz *akt = g? g2 : g1;
    if(e.sprawdz_wstawienie(akt,n,p1,p)){
    //    cout<<"jfdjfdallklkfda\n";
        pionek pom = akt->zabierz_pionek(n-1);//zwraca zabrany pionek
        p->wstaw(p1,pom);
        g^=1;
        return "";
    }
    else return e.wypisz_blad();
  //  else return "błędny ruch\n";//moze last error sie zobaczy
}

string rozgrywka::przesun(string poz1, string poz2, string prom){
    if(!e.czy_pozycja(poz1) || !e.czy_pozycja(poz2)) return "bledny format\n";
    pozycja p1 = pozycja(poz1);
    pozycja p2 = pozycja(poz2);
    gracz *akt = g? g2 : g1;
    bool promuj = prom[0]=='p';
    pionek pion= p->get_pionek(p1);
 //   if(pion.get_symbol()=='⬜') return "na wybranym polu startowym nie ma pionka\n//";
    if(promuj){
        if(!e.promocja(g,p2)) return "nie mozna wykonać promocji na tym polu\n";
    }

    if(e.sprawdz_ruch(g,p1,p2,p)){
        if(promuj) p->promuj(p1);
        pionek bity = p->get_pionek(p2);
        p->przesun(pion,p2,akt);
        p->usun(p1);//zabierz pionka z p1

        if(bity.get_symbol()=="k") {
            if(g) return "Koniec gry gracz2 wygral\n";
            return "Koniec gry gracz1 wygral\n";
        }
        g^=1;
        return "";
    }
    else return e.wypisz_blad(); //moze last error
}
