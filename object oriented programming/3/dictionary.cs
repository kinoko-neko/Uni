using System;

public class dict<K,V> {
	
	int siz,ile;//ile-liczba elementów, //ile2-najdalszy indeks. (powstają dziury)
	K [] klucze;
	V [] wart;
	 	
	public dict(int roz=1){
		this.siz=roz; this.ile=0;
		klucze= new K[roz];
		wart= new V[roz]; 
	}
	 
	public int rozmiar(){return siz;} 
	public int ile_el(){ return ile;}
	
	public void wstaw(K klucz, V war){
		if(ile==siz) return;
		for(int i=0;i<ile;i++){
			if(klucze[i].Equals(klucz)) return;
		}
		klucze[ile]=klucz;
		wart[ile]=war; ile++;
	}
	
	public void usun(K klucz){
		for(int i=0;i<ile;i++){
			if(klucze[i].Equals(klucz)){
				for(int j=i+1;j<ile;j++){
					klucze[j-1]=klucze[j];
					wart[j-1]=wart[j];
				}
				ile--; return;
			}
		}
	}
	public bool znajdz(K klucz){
		for(int i=0;i<ile;i++){
			if(klucze[i].Equals(klucz)) return true;
		}
		return false;
	}
	public V wartosc(K klucz){
		for(int i=0;i<ile;i++){
			if(klucze[i].Equals(klucz)) return wart[i];
		}
		return default(V);
	}
	
}
