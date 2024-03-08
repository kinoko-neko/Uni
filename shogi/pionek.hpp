#ifndef PIONEK_HPP
#define PIONEK_HPP
#include "pozycja.hpp"
#include <vector>
#include <string>
class pozycja;

class pionek{
    std::vector<std::pair<int,int> >ruchy;//ruchy przez całą plansze są traktowane jak zwykłe czyli troche tych ruchów jest
    std::vector<std::pair<int,int> >ruchy_upgrade;
    std::string symbol; std::string symbol2;
 //   bool g;//którego jest gracza;
    bool up;

    public:

    bool g;//którego jest gracza
    pionek();
    pionek(char typ, bool g1);
    bool check_move(std::pair<int,int> p);//mówi czy dany ruch jest możliwy dla tego pionka;
    void change_owner(bool g1);
    void upgrade();
    void downgrade();
    std::string get_symbol();
    std::string wypisz();
    bool can_move(pozycja poz);
};
#endif
