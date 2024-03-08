#ifndef GRACZ_HPP
#define GRACZ_HPP
#include <vector>
#include <string>
class pionek;
class gracz{
    bool ktory;
    std::vector<pionek>zbite;

    public:

    gracz() = default;
    gracz(bool b);
    void dodaj_pionek(pionek p);
    int ile_pionkow();
    pionek get_pionek(int n); //nie zabiera pionka
    pionek zabierz_pionek(int n);// zabiera n-ty zbity pionek, najlepiej by przy usuwaniu zachowywal kolejnosc
    std::string wypisz();
};
#endif
