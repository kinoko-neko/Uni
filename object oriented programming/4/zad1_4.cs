using System;
using System.Collections;

interface Strumien{
	
	int next();
	bool eos();
	void reset();
}

class IntStream: Strumien, System.Collections.IEnumerable {
    public int akt;
    public IntStream() {
        this.akt=0;
    }
    public int next(){
        akt++;
        return akt;
    }
    public bool eos(){
        return akt==Int32.MaxValue;
    }
    public void reset(){
        this.akt=0;
    }
    
    public int Length{
    	get { return akt; }
    }
    
    public int this[int indeks]{
    	get{
    		return indeks;
    	}
    }
    
    override public string ToString(){
    	return akt.ToString();
    }
    
    class Enum : IEnumerator{
			int akt;
			public Enum(int akt2) { this.akt=akt2; }
			public bool MoveNext() { 
				if(akt==Int32.MaxValue) return false;
				akt++; return true; 
			}
			public object Current { 
				get{
					return akt;  
				}
			}
			public void Reset() { akt=0; }
		}
	
		public IEnumerator GetEnumerator(){
			return new Enum(akt);
		}
}

class PrimeStream: Strumien {
    public int nast,akt;
    public PrimeStream(){
        this.akt=2;
        this.nast=3;
    }    
    bool IsPrime(int x){
        for(int j=3;j*j<=x;j+=2){
            if( (x%j)==0 ) return false;
        }
        return true;
    }
    public int next(){
        int pom=akt;
        akt=nast;
        for(int i=nast;i<=Int32.MaxValue;i++){
            if(IsPrime(i)){
                nast=i; break;
            }
        }
        return pom;
    }
    public bool eos(){
        return akt==nast;
    }
    public void reset(){
    	akt=2;
    	nast=3;
    }
} 

class prog{
	public static void Main(){
		IntStream st= new IntStream();
		Console.WriteLine(st.next());
		Console.WriteLine(st.Length);
		Console.WriteLine(st);
		Console.WriteLine(st[15]);
		IntStream pc = new IntStream();
		foreach(int p in pc)
			Console.WriteLine(p);
		
	}
}
