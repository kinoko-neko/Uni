#include<bits/stdc++.h>
#include "onp.cpp"
using namespace std;

void split(vector<string> &v, string s, string del = " "){
    v.clear();
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        v.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    v.push_back(s.substr(start, end - start));

}

int get_index(string s){
    vector<string>sym = {"+","-","*","/","log","%","^","min","max","sin","cos","abs","sgn","exp","floor","ln","ceil","!","atan","acot","fi","e","pi"};
    //
    int wsk=0;
    while(wsk<sym.size()){
        if(sym[wsk]==s) return wsk;
        wsk++;
    }
    return -1;
}

bool numer(string &s){
    for(int i=0;i<s.size();i++)
        if(s[i]<'0' || s[i]>'9') return false;
    return true;
}

double calc(vector<string>&exp){
    stack<kalkulator::symbol* >stos;
    int pom;
    for(int i=0;i<exp.size();i++){
        kalkulator::symbol *akt;
        kalkulator::symbol *w1, *w2;

        pom=get_index(exp[i]);

        switch (pom) {
            case -1 : {
                if(numer(exp[i])){
                    akt= new kalkulator::liczba((double)stod(exp[i]));
                }
                else akt= new kalkulator::zmienna(exp[i]);
                break;
            }
            case 0 : {
                w2 = stos.top(); stos.pop();
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::dodaj(w1,w2); break;
            }
            case 1 : {
                w2 = stos.top(); stos.pop();
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::odejmij(w1,w2); break;
            }
            case 2 : {
                w2 = stos.top(); stos.pop();
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::mnoz(w1,w2); break;
            }
            case 3 : {
                w2 = stos.top(); stos.pop();
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::dziel(w1,w2); break;
            }
            case 4 : {
                w2 = stos.top(); stos.pop();
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::logarytm(w1,w2); break;
            }
            case 5 : {
                w2 = stos.top(); stos.pop();
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::modulo(w1,w2); break;
            }
            case 6 : {
                w2 = stos.top(); stos.pop();
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::potenga(w1,w2); break;
            }
            case 7 : {
                w2 = stos.top(); stos.pop();
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::Min(w1,w2); break;
            }
            case 8 : {
                w2 = stos.top(); stos.pop();
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::Max(w1,w2); break;
            }
            case 9 : {
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::Sin(w1); break;
            }
            case 10 : {
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::Cos(w1); break;
            }
            case 11 : {
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::bez(w1); break;
            }
            case 12 : {
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::sgn(w1); break;
            }
            case 13 : {
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::Exp(w1); break;
            }
            case 14 : {
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::Floor(w1); break;
            }
            case 15 : {
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::ln(w1); break;
            }
            case 16 : {
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::Ceil(w1); break;
            }
            case 17 : {
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::frac(w1); break;
            }
            case 18 : {
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::Atan(w1); break;
            }
            case 19 : {
                w1 = stos.top(); stos.pop();
                akt = new kalkulator::Acot(w1); break;
            }
            case 20 :{
                akt = new kalkulator::fi(); break;
            }
            case 21 : {
                akt = new kalkulator::pi(); break;
            }
            case 22 : {
                akt = new kalkulator::e(); break;
            }
            default : throw "zły format\n";
        }
        stos.push(akt);

    }
    if(stos.size()!=1) throw "zły format\n";
    return stos.top()->oblicz();
}

int main(){
    string inp,nazwa;
    vector<string>v;
    vector<string>v2;
    while(true){
        getline(cin,inp);
        split(v,inp);
        v2.clear();
        if(v[0]=="print"){
            if(v.size()<2){
                clog<<"Niepoprawny format\n"; continue;
            }
            double pom;
            try{
                for(int i=1;i<v.size();i++) v2.push_back(v[i]);
                pom=calc(v2);
            }
            catch(...){
                clog<<"Niepoprawne wyrażenie\n"; continue;
            }
            cout<<pom<<"\n";
        }
        else if(v[0]=="set"){
            if(v.size()<3){
                clog<<"Niepoprawny format\n"; continue;
            }
            double pom;
            try{
                for(int i=3;i<v.size();i++) v2.push_back(v[i]);
                pom=calc(v2);
            }
            catch(...){
                clog<<"Niepoprawne wyrażenie :-(\n"; continue;
            }
            kalkulator::zmienna::assign(nazwa,pom);
        }
        else if(v[0]=="clear"){
            cout<<"Posprzątane zmienne ^^\n";
            kalkulator::zmienna::clear();
        }
        else if(v[0]=="exit"){
            cout<<"Miłego dnia :-)\n"; return 0;
        }
        else{
            clog<<"Niepoprawna komenda\n";
        }

    }
}
