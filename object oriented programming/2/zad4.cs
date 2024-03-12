using System;
using System.Collections.Generic;

class LazyIntList{
	protected List<int> lista;
	protected int siz;
	//Random rnd;
	
	public LazyIntList(){ this.lista= new List<int>(); this.siz=0; 
//	this.rnd= new Random();
	}
	
	virtual public int element(int i){
		for(int j=siz;j<i;j++){
			lista.Add(j);
			//lista.Add(rnd.Next());
		}	
		if(i>siz) siz=i;
		return lista[i-1];
	}
	public int size(){
		return siz;
	}
	
}

class LazyPrimeList: LazyIntList{
	bool isprime(int x){
		for(int j=3;j*j<=x;j+=2){
    	if( (x%j)==0 ) return false;
    }
    return true;
	}
	override public int element(int i){
		if(siz==0 && i>0){
			lista.Add(2); siz=1;
		}
		if(siz==1 && i>1){
			lista.Add(3); siz=2;
		}
		
		for(int j=siz;j<i;j++){
			for(int j2=lista[j-1]+2;j2<Int32.MaxValue;j2+=2){//na bazie poprzedniego elementu listy
				if(isprime(j2)){
					lista.Add(j2); siz++; break;
				}
			}
		}
		return lista[i-1];
	}
}

class mojprog {
    public static void Main(){
    		
        LazyPrimeList l2= new LazyPrimeList();
        Console.WriteLine(l2.size());
        Console.WriteLine(l2.element(10));
        Console.WriteLine(l2.size());
        Console.WriteLine(l2.element(10));
        
        LazyIntList l3= new LazyIntList();
        Console.WriteLine(l3.size());
        Console.WriteLine(l3.element(10));
        Console.WriteLine(l3.size());
        Console.WriteLine(l3.element(10));
    }
}
