using System;

class IntStream {
    public int akt;
    public IntStream() {
        this.akt=-1;
    }
    virtual public int next(){
        akt++;
        return akt;
    }
    virtual public bool eos(){
        return akt==Int32.MaxValue;
    }
    virtual public void reset(){
        this.akt=-1;
    }
}

class PrimeStream: IntStream {
    public int nast;
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
    override public int next(){
        int pom=akt;
        akt=nast;
        for(int i=nast;i<=Int32.MaxValue;i++){
            if(IsPrime(i)){
                nast=i; break;
            }
        }
        return pom;
    }
    override public bool eos(){
        return akt==nast;
    }
    override public void reset(){
    	akt=2;
    	nast=3;
    }
} 

class RandomStream: IntStream {
    Random rnd;
    public RandomStream(){
        this.rnd = new Random();
        this.akt= rnd.Next();
    }
    override public int next(){
        int pom=akt;
        akt=rnd.Next();
        return pom;
    }
    override public bool eos(){
        return false;
    }
}

class RandomWordStream{
	RandomStream znak_num;
	PrimeStream dl;
	public RandomWordStream(){
		znak_num= new RandomStream();
		dl= new PrimeStream();
	}
	
	public string next(){
		string ret="";
		char pomi; int pom2;
		
		int dl_akt= dl.next();
		for(int i=0;i<dl_akt;i++){
			pom2=znak_num.next();
			
			pom2%=26;
			while(pom2<0) pom2+=26;
			
			pomi=(char)(pom2+'a' );
			ret= ret+pomi;
		}
		return ret;
	}
	
	public bool eos(){ return dl.eos(); }
	public void reset(){ dl.reset();}
}

class mojprog {
    public static void Main(){
        RandomStream ps = new RandomStream();
        Console.WriteLine(ps.next()); // zwraca 2
        Console.WriteLine(ps.next()); // zwraca 3
        RandomWordStream rws = new RandomWordStream();
				Console.WriteLine(rws.next()); // zwraca losowy string o dł 2
				Console.WriteLine(rws.next()); // zwraca losowy string o dł 3
    }
}
