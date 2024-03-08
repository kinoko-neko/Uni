#ifndef BLEDY_HPP
#define BLEDY_HPP
#include "pozycja.hpp"

class plansza;
class pozycja;
class gracz;

class bledy{
    std::string last_error; //pamięta ostatni błąd wykonany przez gracza

    public:

    bledy();
    bool czy_pozycja(std::string s);
    bool numer(std::string s);
    bool promocja(bool g, pozycja poz);
    bool sprawdz_ruch(bool g,pozycja poz1, pozycja poz2, plansza *b);
    bool sprawdz_wstawienie(gracz *g, int n, pozycja poz, plansza *b);
    std::string wypisz_blad();//wywolana tylko po bledzie i ma wypisac jaki to byl
};
#endif
