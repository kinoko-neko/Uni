import java.util.*;

public interface rank extends Comparable<rank>{
	int get_rank();
	
	int compareTo(rank r);
} 

class ranklist{
	static Vector<rank> kol;
	
	ranklist (){
		kol= new Vector<rank>();
	}
	
	static void addrank(rank ranga){
		kol.add(ranga);//nie zmieniam kolejności zakladam że kolejność dokładanie rang to będzie właściwa kolejność
	}
	
	public int get_rank(rank ranga){
		for(int i=0;i<kol.size();i++){
			if(ranga.getClass() == kol.get(i).getClass()) return i;
		}
		return -1;//nie ma rangi
	}
}

class szeregowy implements rank{

	String dane;
	ranklist hier;

	szeregowy (String s, ranklist x){ this.dane=s; this.hier=x;}	
	
	public int get_rank(){
		return hier.get_rank(this);
	}
	
	public int compareTo(rank r){
		return Integer.compare(this.get_rank(), r.get_rank());
	}
	
	public String toString(){ return dane;}
}

class kapral implements rank{

	String dane;
	ranklist hier;

	kapral (String s, ranklist x){ this.dane=s; this.hier=x;}
	
	public int get_rank(){
		return hier.get_rank(this);
	}
	
	public int compareTo(rank r){
		return Integer.compare(this.get_rank(), r.get_rank());
	}
	
	public String toString(){ return dane;}
}

class plutonowy implements rank{

	String dane;
	ranklist hier;

	plutonowy (String s, ranklist x){ this.dane=s; this.hier=x;}	
	
	public int get_rank(){
		return hier.get_rank(this);
	}
	
	public int compareTo(rank r){
		return Integer.compare(this.get_rank(), r.get_rank());
	}
	
	public String toString(){ return dane;}
}

class sierzant implements rank{

	String dane;
	ranklist hier;

	sierzant (String s, ranklist x){ this.dane=s; this.hier=x;}
	
	public int get_rank(){
		return hier.get_rank(this);
	}
	
	public int compareTo(rank r){
		return Integer.compare(this.get_rank(), r.get_rank());
	}
	
	public String toString(){ return dane;}
}
