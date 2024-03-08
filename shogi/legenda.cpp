#include "legenda.hpp"
using namespace std;

legenda::legenda(){

    oznaczenia_vis=true;
    zasady_vis=true;
    instrukcja_vis=true;

    oznaczenia = " k - krol\n w - wieza\n g - goniec\n z - zloty general\n s - srebny general\n j - skoczek\n l - lanca\n p - pionek\n h - promowany goniec(kon)\n d - promowana wieza(smok)\n";

    zasady  =   " http://www.kgj.pjwstk.edu.pl/shogi/zasady.html\n";

    instrukcja =
        "q - wyjscie\n i 1 - pokaz instrukcje\n z 0 -schowaj zasady\n z 1 - pokaz zasady\n i 0 - schowaj instrukcje\n l 1 - pokaz legende\n l 0 - schowaj legende\n s num poz - przywolaj zbitego pionka  o numerze num na pozycje poz\n m poz1 poz2 - przesun pionek z\n pozycji poz1 na pozycje poz2\n";
}

void legenda::show_zasady(){ zasady_vis=true; }
void legenda::hide_zasady(){ zasady_vis=false;}
void legenda::show_instrukcja(){ instrukcja_vis=true;}
void legenda::hide_instrukcja(){ instrukcja_vis=false;}
void legenda::show_oznaczenia(){ oznaczenia_vis=true;}
void legenda::hide_oznaczenia(){ oznaczenia_vis=false;}

pair<string,string> legenda::wypisz(){

    string wypisz   =   "";
    string wypisz2 = "";
    if(zasady_vis) wypisz2   =  zasady;
    if(instrukcja_vis) wypisz = wypisz + instrukcja;
    if(oznaczenia_vis) wypisz = wypisz + oznaczenia;

    return {wypisz2,wypisz};
}
