#include <string>
#include <vector>
#include<ncurses.h>
#include "gra.hpp"
#include "legenda.hpp"
#include "rozgrywka.hpp"
#include "plansza.hpp"
#include "gracz.hpp"
#include "bledy.hpp"
#include "pionek.hpp"
#include "pozycja.hpp"
using namespace std;

gra::gra(){
    g1 = gracz(false) ;
    g2 = gracz(true) ;
    l = legenda();
    p = plansza();
    komunikat = "";
    r = rozgrywka(&p,&g1,&g2);

    //okna
    wl = newwin(34,38,0,0);
    wz = newwin(34,53,0,108);
    wg1 = newwin(3,len,24,x);
    wg2 = newwin(3,len,0,x);
    wp = newwin(21,len,3,x);
    wkom = newwin(4,len,30,x);
    wkol = newwin(3,30,27,x);

    refresh();
    box(wl,0,0);
    box(wg1,0,0);
    box(wg2,0,0);
    box(wp,0,0);
    box(wkom,0,0);
    box(wkol,0,0);
    box(wz,0,0);

    wrefresh(wl);
    wrefresh(wg1);
    wrefresh(wg2);
    wrefresh(wp);
    wrefresh(wkom);
    wrefresh(wkol);
    wrefresh(wz);
    update();
}

WINDOW* gra::get_okno(){ return wkom;}
vector<string> split(string s, string del = " "){
    vector<string> v;
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        v.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    v.push_back(s.substr(start, end - start));
    return v;
}

void gra::next_event(string inp){ //switch przyjmuje inta lub chara nie stringa
    if(p.koniec) {komunikat="Koniec gry wciśnij q by zakończyc\n."; update(); return;}
    komunikat = "";
    switch (inp[0]){

        case 'i':{ //widzialnosc instrukcji
            if(inp.size()<3){komunikat = "zly format komendy\n "; break;}
            if(inp[2]=='0') l.hide_instrukcja();
            else if(inp[2]=='1') l.show_instrukcja();
            else komunikat =  "bledna komenda\n "; break;
        }
        case 'l':{ //widzialnosc oznaczen
            if(inp.size()<3){komunikat = "zly format komendy\n "; break;}
            if(inp[2]=='0') l.hide_oznaczenia();
            else if(inp[2]=='1') l.show_oznaczenia();
            else komunikat =  "bledna komenda\n "; break;
        }
        case 'z':{//widzialnosc zasad
            if(inp.size()<3){komunikat = "zly format komendy\n "; break;}
            if(inp[2]=='0') l.hide_zasady();
            else if(inp[2]=='1') l.show_zasady();
            else komunikat =  "bledna komenda\n "; break;
        }
        case 's':{// s num poz - przywołaj zbitego pionka o numerze num na pozycje poz
            vector<string>pomi;
            pomi=split(inp);
            if(pomi.size()!=3) komunikat = "zly format komendy\n ";
            else komunikat=r.wstaw(pomi[1],pomi[2]); break;
        }
        case 'm':{//m poz1 poz2 (p)- przesun pionek z pozycje poz1 na pozycje poz2, opcjonalnie p by zrobić promocje
            vector<string>pomi;
            pomi=split(inp);
            if(pomi.size()==3) komunikat = r.przesun(pomi[1],pomi[2],"n");
            else if (pomi.size()==4) komunikat = r.przesun(pomi[1],pomi[2],pomi[3]);
            else komunikat = "zly format komendy\n "; break;
            //if(pomi.size()!=3) komunikat = "zły format komendy\n";
           // else komunikat=r.przesun(pomi[1],pomi[2]);
        }
        default:{
            komunikat = "prosze podaj komende\n ";
        }
    }
    update();
}

void wyp(char t[],string s){
    for(int i=0;i<s.size();i++) t[i]=s[i];
}
void cl(char t[],int roz){
    for(int i=0;i<roz;i++) t[i]='\0';
}

void gra::update(){

    pair<string,string> leg=l.wypisz();
    wclear(wl); box(wl,0,0);
    char tl[600]; cl(tl,600); wyp(tl,leg.second);
    mvwprintw(wl,1,1,tl);

    wclear(wz); box(wz,0,0);
    char tz[600]; cl(tz,600); wyp(tz,leg.first);
    mvwprintw(wz,1,1,tz);

    wclear(wkol); box(wkol,0,0);
    if(r.g) mvwprintw(wkol,1,1,"tura: gracz2"); else mvwprintw(wkol,1,1,"tura: gracz1");

    wclear(wg2); box(wg2,0,0);
    string pl1="gracz2: "+g2.wypisz();
    char tg2[30]; cl(tg2,30); wyp(tg2,pl1);
    mvwprintw(wg2,1,1,tg2);

    string pl=p.wypisz();

    wclear(wg1); box(wg1,0,0);
    string pl2="gracz1: "+g1.wypisz();
    char tg1[30]; cl(tg1,30); wyp(tg1,pl2);
    mvwprintw(wg1,1,1,tg1);

    wclear(wp); box(wp,0,0);
    char tp[800]; cl(tp,800);  wyp(tp,pl);
    mvwprintw(wp,1,1,tp);

    wclear(wkom); box(wkom,0,0);
    char tkom[50]; cl(tkom,50); wyp(tkom,komunikat);
    mvwprintw(wkom,1,1,tkom);

 //   move(50,30);
    refresh();

    wrefresh(wkom);

    wrefresh(wkol);
    wrefresh(wg2);
    wrefresh(wg1);
    wrefresh(wl);
    wrefresh(wz);
    wrefresh(wp);
}
