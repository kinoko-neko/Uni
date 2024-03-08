#ifndef POZYCJA_HPP
#define POZYCJA_HPP
#include <string>
//f3 - mała litera liczba; litery-wierszy; liczby-kolumny
class pozycja{
    public:
    int x, y;
    pozycja();
    pozycja(std::string a);
};
#endif
