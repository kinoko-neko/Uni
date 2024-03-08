#include<string>
#include<algorithm>
#include "plansza.hpp"
#include "gracz.hpp"
//#include "pozycja.hpp"
//#include "pionek.hpp"
using namespace std;
/*
k - król
w - wierza
g - goniec
z - złoty generał
s - srebny generał
j - skoczek
l - lanca
p - pionek
h - promowany goniec(koń)
d - promowana wierza(smok)
*/


plansza::plansza(){
    string r0 = "ljszkzsjl";
    string r1 = "owooooogo";
    string r2 = "ppppppppp";
    string r3 = "ooooooooo";
    string r7 = r1; reverse(r7.begin(),r7.end());

    k0.x=8; k0.y=3;
    k1.x=0; k1.y=3;

    bool czyj[9] = {1,1,1,1,1,0,0,0,0};
    koniec = false; //czy są oba króle

    vector<string> pl = {r0,r1,r2, r3,r3,r3, r2,r7,r0};

    for(int i=0;i<9;i++) pionki[i]=2;

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            board[i][j]= pionek(pl[i][j],czyj[i]);
        }
    }
}

pionek plansza::get_pionek(pozycja poz){
    return board[poz.x][poz.y];
}

bool plansza::czy_pion(pozycja poz){
    return pionki[poz.y];
}

pozycja plansza::krol(bool b) {return b? k1 : k0;}

void plansza::wstaw(pozycja poz, pionek p){
    if(p.get_symbol()=="p") pionki[poz.y]++;
    board[poz.x][poz.y]=p;
}

void plansza::przesun(pionek p, pozycja poz, gracz *g){
    if(p.get_symbol()=="p") pionki[poz.y]++;
    pionek p2=board[poz.x][poz.y];
    if(p2.get_symbol()!="_") g->dodaj_pionek(p2);
    board[poz.x][poz.y]=p;
    if(p.get_symbol()=="k"){
        if(p.g) k1=poz; else k0=poz;
    }
}

void plansza::usun(pozycja poz){
    if(board[poz.x][poz.y].get_symbol()=="p") pionki[poz.y]--;
    board[poz.x][poz.y]=pionek('o',false);
}

void plansza::promuj(pozycja poz){
    board[poz.x][poz.y].upgrade();
}

bool plansza::pion(pozycja poz1, pozycja poz2){
    int pomi = (poz1.x>poz2.x)? -1 : 1;
    for(int i=poz1.x+pomi;i!=poz2.x;i+=pomi){
        if(board[i][poz1.y].get_symbol()!="_") return true;
    }
    return false;
}

bool plansza::poziom(pozycja poz1, pozycja poz2){
    int pomi = (poz1.y>poz2.y)? -1 : 1;
    for(int i=poz1.y+pomi;i!=poz2.y;i++){
        if(board[poz1.x][i].get_symbol()!="_") return true;
    }
    return false;
}

bool plansza::skos(pozycja poz1, pozycja poz2){
    int pom1 = (poz1.x>poz2.x)? -1 : 1;
    int pom2 = (poz1.y>poz2.y)? -1 : 1;
    int y=poz1.y+pom2;
    for(int i=pom1+poz1.x;i!=poz2.x;i+=pom1){
        if(board[i][y].get_symbol()!="_") return true;
        y+=pom2;
    }
    return false;
}

string plansza::wypisz(){
    string ret="     |9|  |8|  |7|  |6|  |5|  |4|  |3|  |2|  |1|\n             \n ";
    for(int i=0;i<9;i++){
        ret = ret + "      ";
        for(int j=0;j<9;j++) {
            ret=ret+board[i][j].wypisz()+ "    ";
        }
        ret.push_back('|'); ret.push_back('a'+i); ret.push_back('|'); ret = ret +"\n\n"; ret.push_back(' ');
    }
    return ret;
}

std::pair<int,int> plansza::ruch(pozycja poz1, pozycja poz2){ //jak jest ruch z pozycji poz1 do poz2
    return {poz2.x-poz1.x,poz2.y-poz1.y};
}
