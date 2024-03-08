#ifndef LEGENDA_HPP
#define LEGENDA_HPP
#include <string>
//using namespace std;

class legenda{

    std::string zasady;
    bool zasady_vis;

    std::string instrukcja;
    bool instrukcja_vis;

    std::string oznaczenia;
    bool oznaczenia_vis;
    public:

    legenda();
    void show_zasady();
    void hide_zasady();
    void show_instrukcja();
    void hide_instrukcja();
    void show_oznaczenia();
    void hide_oznaczenia();
   std:: pair<std::string,std::string> wypisz();//zwaraca to co ma zostać wypisane w szczególności pusty string

};
#endif
