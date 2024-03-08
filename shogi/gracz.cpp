#include "gracz.hpp"
#include "pionek.hpp"
using namespace std;

gracz::gracz(bool b){
    ktory = b;
    zbite = {};
}

int gracz::ile_pionkow() {return zbite.size();}

void gracz::dodaj_pionek(pionek p){
    p.downgrade();
    p.change_owner(ktory);
    zbite.push_back(p);
}

pionek gracz::zabierz_pionek(int n ){
    pionek ret = zbite[n];
    zbite.erase(zbite.begin() +(n));
    return ret;
}

pionek gracz::get_pionek(int n){
    return zbite[n];
}

string gracz::wypisz(){
    string wyp="zbite: ";
    for(int i=0;i<zbite.size();i++){ wyp=wyp+zbite[i].wypisz(); wyp.push_back(' ');}
  //  wyp.push_back('\n');
    return wyp;
}
