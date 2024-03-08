#include "pozycja.hpp"
using namespace std;

pozycja::pozycja(string a){
    x=a[0]-'a';
    y=a[1]-'1'; y= 8-y;
}

pozycja::pozycja(){x=0; y=0;}
