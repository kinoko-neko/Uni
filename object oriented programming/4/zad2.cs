using System;
using System.Collections;

public class PrimeCollection: System.Collections.IEnumerable{	
	
	protected class elem{
		int akt;
		const int limit=Int32.MaxValue;
		public elem(int val=2){
			akt=val;
		}
		
		private bool isprime(int x){
			if( (x%2!=1) && x!=2) return false;
			for(int i=3;i*i<=x;i+=2){
				if((x%i)==0) return false;
			}
			return true;
		}
	
		public int get_akt(){ return akt; }
		public void set_akt(int val){ akt=val;}
		
		public bool przesun(){//zwaraca prawda gdy da sie przesunać i przesuwa akt
			if(akt==2){ akt=3; return true; }
			for(int i=akt+2;i<=limit;i+=2){
				if(isprime(i)){
					akt=i; return true;
				}
			}
			return false;
		}
		
	}
	
	elem lista;
	
	public PrimeCollection(){
		lista=new elem();
	}
	
	public int next(){
		if(lista.przesun()) return lista.get_akt();
		return 0;
	}
	
	class PrimeEnum : IEnumerator{
		elem lista;
		public PrimeEnum(elem lista) { this.lista=lista; }
		public bool MoveNext() { return lista.przesun(); }
		public object Current { 
			get{
				return lista.get_akt();  
			}
		}
		public void Reset() { lista.set_akt(2); }
	}
	
	public IEnumerator GetEnumerator(){
		return new PrimeEnum(lista);
	}
	
}

class prog{
	public static void Main(){
		PrimeCollection p6= new PrimeCollection();
		Console.WriteLine(p6.next());
		PrimeCollection pc = new PrimeCollection();
		foreach(int p in pc)
			Console.WriteLine(p);
		}
}

