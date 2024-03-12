
public class OrdList<T extends Comparable<T> >{
	
	class elem<T>{
		T wal;
		elem<T> next;
		
		elem (T x){
			this.wal=x;
			this.next=null;
		}
		
		elem (T x, elem<T> n){
			this.wal=x;
			this.next=n;
		}
	//	T get_val(){ return this.wal;}
		//void set_val(T x){this.wal=x;}
	//	elem<T> nast(){ return this.next;}
	}
	
	elem<T> pocz;
	
	void add_elem(T el){
	
		if(pocz==null){
			pocz=new elem<T>(el); return;
		}
		if(pocz.wal.compareTo(el)>0){
			elem<T> pom=new elem<T>(el,pocz);
			pocz=pom; return;
		}
		elem<T> pomi=pocz;
		while(pomi.next!=null && (pomi.next.wal.compareTo(el)<0 )){
			pomi=pomi.next;
		}
		pomi.next= new elem<T>(el,pomi.next);
	}
	
	T get_first() throws NullPointerException { 
		if(pocz==null) throw new NullPointerException();
		return pocz.wal;
	}
	
	public String toString(){ 
		elem<T> pom=pocz;
		String wyn="";
		while(pom!=null){
			wyn=wyn+ " " + pom.wal.toString();
			pom=pom.next;
		}
		return wyn;
	}
	
	OrdList (){
		this.pocz= null;
	}
}
