#ifndef PLANSZA_HPP
#define PLANSZA_HPP
#include "pozycja.hpp"
#include "pionek.hpp"
//x- odpowiada sa to krówy wiersz; za która kolumne
class pionek;
class pozycja;
class gracz;

class plansza{
    pionek board[9][9];
    int pionki[9];//czy w danej kolumnie jest pionów
    pozycja k0,k1; //pozycje króli

    public:
    bool koniec;

    plansza();
    void wstaw (pozycja p1, pionek p);
    void przesun (pionek p1, pozycja p2, gracz *g);
    void usun (pozycja p);
    void promuj (pozycja poz);//promuj pionka na pozycji poz
    pozycja krol(bool b);
    std::pair<int,int> ruch(pozycja poz1, pozycja poz2); //jak jest ruch z pozycji poz1 do poz2
    bool czy_pion(pozycja p);//czy w danej kolumnie jest pion
    bool pion(pozycja poz1, pozycja poz2);
    bool poziom(pozycja poz1, pozycja poz2);
    bool skos(pozycja poz1, pozycja poz2);
    pionek get_pionek(pozycja p);//zwraca pionek z danej pozycji
    std::string wypisz();
};

#endif
