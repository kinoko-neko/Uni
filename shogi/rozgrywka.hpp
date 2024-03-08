#ifndef ROZGRYWKA_HPP
#define ROZGRYWKA_HPP
#include<bits/stdc++.h>
#include "bledy.hpp"

class plansza;
class gracz;
class rozgrywka{
    plansza *p;
    gracz *g1; gracz *g2;
    bledy e;
public:
    bool g;//który kracz ma kolejke

    rozgrywka()=default;
    rozgrywka(plansza *p1, gracz *g3, gracz *g4);
    std::string wstaw(std::string num, std::string poz);
    std::string przesun(std::string poz1, std::string poz2, std::string prom);
};

#endif
