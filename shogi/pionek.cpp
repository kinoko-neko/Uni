#include "pionek.hpp"

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
  - pionek pusty inaczej puste pole (o)
*/
string toupper(string s){
    string ret= s;
    for(int i=0;i<s.size();i++) ret[i]=toupper(s[i]);
    return ret;
}

string tolower(string s){
    string ret= s;
    for(int i=0;i<s.size();i++) ret[i]=tolower(s[i]);
    return ret;
}

pionek::pionek(){
    symbol='o';
    symbol2='o';
    g=0; up=0;
}

pionek::pionek(char c, bool g1){
    symbol = c;
    g = g1;
    up = false;

    switch (c){
        case 'k':{
            ruchy = {{-1,-1},{-1,1},{1,-1},{1,1},{-1,0},{1,0},{0,-1},{0,1}};
            symbol2 = "k";
            ruchy_upgrade = ruchy; break;
        }
        case 'w':{
            symbol2 = "d";
            ruchy = {{0,1},{0,-1},{1,0},{-1,0},{0,2},{0,-2},{2,0},{-2,0},{0,3},{0,-3},{3,0},{-3,0},{0,4},{0,-4},{4,0},{-4,0},{0,5},{0,-5},{5,0},{-5,0},{0,6},{0,-6},{6,0},{-6,0},{0,7},{0,-7},{7,0},{-7,0},{0,8},{0,-8},{8,0},{-8,0}};
            ruchy_upgrade = {{0,1},{0,-1},{1,0},{-1,0},{0,2},{0,-2},{2,0},{-2,0},{0,3},{0,-3},{3,0},{-3,0},{0,4},{0,-4},{4,0},{-4,0},{0,5},{0,-5},{5,0},{-5,0},{0,6},{0,-6},{6,0},{-6,0},{0,7},{0,-7},{7,0},{-7,0},{0,8},{0,-8},{8,0},{-8,0}, {-1,-1}, {-1,1}, {1,-1}, {1,1}};
            break;
        }
        case 'g':{
            symbol2 = "h";
            ruchy = { {1,1},{-1,-1},{1,-1},{-1,1},{2,2},{-2,-2},{2,-2},{-2,2},{3,3},{-3,-3},{3,-3},{-3,3},{4,4},{-4,-4},{4,-4},{-4,4},{5,5},{-5,-5},{5,-5},{-5,5},{6,6},{-6,-6},{6,-6},{-6,6},{7,7},{-7,-7},{7,-7},{-7,7},{8,8},{-8,-8},{8,-8},{-8,8}};
            ruchy_upgrade = { {1,1},{-1,-1},{1,-1},{-1,1},{2,2},{-2,-2},{2,-2},{-2,2},{3,3},{-3,-3},{3,-3},{-3,3},{4,4},{-4,-4},{4,-4},{-4,4},{5,5},{-5,-5},{5,-5},{-5,5},{6,6},{-6,-6},{6,-6},{-6,6},{7,7},{-7,-7},{7,-7},{-7,7},{8,8},{-8,-8},{8,-8},{-8,8}, {1,0}, {-1,0}, {0,1}, {0,-1}}; break;
        }
        case 'z':{
            symbol2 = "z";
            ruchy = {{1,0}, {-1,0}, {0,-1}, {0,-1}, {-1,-1}, {-1,1}};
            ruchy_upgrade = {{1,0}, {-1,0}, {0,-1}, {0,-1}, {-1,-1}, {-1,1}}; break;
        }
        case 's':{
            symbol2 = "z";
            ruchy = {{-1,-1},{-1,1},{1,-1},{1,1},{-1,0}};
            ruchy_upgrade = {{1,0}, {-1,0}, {0,-1}, {0,-1}, {-1,-1}, {-1,1}}; break;
        }
        case 'j':{
            symbol2 = "z";
            ruchy = {{-2,-1},{-2,1}};
            ruchy_upgrade = {{1,0}, {-1,0}, {0,-1}, {0,-1}, {-1,-1}, {-1,1}};break;
        }
        case 'l':{
            symbol2 = "z";
            ruchy ={ {-1,0},{-2,0},{-3,0},{-4,0},{-5,0},{-6,0},{-7,0},{-8,0}};
            ruchy_upgrade = {{1,0}, {-1,0}, {0,-1}, {0,-1}, {-1,-1}, {-1,1}}; break;
        }
        case 'p':{
            symbol2 = "z";
            ruchy = {{-1,0}};
            ruchy_upgrade = {{1,0}, {-1,0}, {0,-1}, {0,-1}, {-1,-1}, {-1,1}}; break;
        }
        case 'o':{
            symbol = "_"; symbol2 ="_";
            ruchy = {};
            ruchy_upgrade = {};
        }
    }
    if(g){
        symbol = toupper(symbol);
        symbol2 = toupper(symbol2);
        for(int i=0;i<ruchy.size();i++){
            ruchy[i].first *= -1;
        }
        for(int i=0;i<ruchy_upgrade.size();i++){
            ruchy_upgrade[i].first *= -1;
        }
    }
}

string pionek::get_symbol(){ return up? tolower(symbol2) : tolower(symbol);}
string pionek::wypisz() {return up? symbol2 : symbol; }
void pionek::change_owner(bool g1){
    for(int i=0;i<ruchy.size();i++){
            ruchy[i].first *= -1;
        }
    for(int i=0;i<ruchy_upgrade.size();i++){
        ruchy_upgrade[i].first *= -1;
    }//by ruchy były w drugą stronę

    if(g1){
        symbol = toupper(symbol); symbol2 = toupper(symbol2);
        g=g1;
    }
    else{
        symbol = tolower(symbol); symbol2 = tolower(symbol2);
        g=g1;
    }
}

void pionek::upgrade(){    up=true;}
void pionek::downgrade(){ up=false;}

bool pionek::check_move(pair<int,int> p2){
    if(up){
        for(int i=0;i<ruchy_upgrade.size();i++)
            if(ruchy_upgrade[i]==p2) return true;
    }
    else{
        for(int i=0;i<ruchy.size();i++)
            if(ruchy[i]==p2) return true;
    }
    return false;
}

bool pionek::can_move(pozycja poz){ //czy dany pionek może się gdzieś poruszyć. (ważne przy wstawianiu)
    string symbol3 = tolower(symbol);
    if(symbol3=="j"){
        if(g) return poz.x <7;
            return poz.x>1;
    }
    if(symbol3=="l" || symbol3=="p"){
        if(g) return poz.x<8;
        return poz.x>0;
    }
    return true;
}
