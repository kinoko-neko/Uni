#include<bits/stdc++.h>
#include<ncurses.h>
#include "gra.hpp"
using namespace std;

void my_getline(string& str, WINDOW *wkom){
  char ch;
  str.clear();
  while (true){
    ch= wgetch(wkom);
    if(ch == '\n') break;
    str.push_back(ch);
  }
}

int main(){

    initscr();
    cbreak();
    gra g = gra();
    WINDOW *winp = g.get_okno();;
    string inp;
    my_getline(inp,winp);
    while(inp[0]!='q'){
        g.next_event(inp);
        my_getline(inp,winp);
    }
 //   getch();
    endwin();
    cout<<"Thaks for playing, have a nice day! :D";
}
