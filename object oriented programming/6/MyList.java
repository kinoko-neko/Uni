import java.util.*;

public class MyList<T> implements Collection<T> {
	
	class elem  {
		public elem next,prev;
		public T val;
		
		public elem(T wart){
			this.prev=null;
			this.next=null;
			this.val=wart;
		}
		
	}
	
	protected class myit implements Iterator<T>{
		elem akt;
		
		protected myit() {this.akt=null;}
		protected myit(elem pocz) {this.akt=pocz;}
		public boolean hasNext(){
			if(akt==null) return false;
			return true;
		}
		
		public T next() throws NoSuchElementException {
			if (akt == null) throw new NoSuchElementException();
			T pomi= akt.val;
			akt = akt.next;
			return pomi;
		}
	}
	
	elem first,last;
	int siz;
	
	public MyList() {
		this.siz=0;
		this.first=null;
		this.last=null;
	}
	
	public void push_back(T x){
		elem pom= new elem(x);
		if(siz==0){
			this.first=pom;
			this.last=pom; 
		}
		else{
			pom.prev=this.last;
			this.last.next=pom;
			
			this.last=pom;
		}
		siz++;
	}
	
	public void push_front(T x) {
		elem pom= new elem(x);
		if(siz==0){
			this.first=pom;
			this.last=pom; 
		}
		else{
			this.first.prev=pom;
			pom.next=first;
			
			this.first=pom;
		}
		siz++;
	}

	public T pop_back() throws IllegalStateException {
		if(siz==0) throw new IllegalStateException();
		elem pom=last;
		if(siz!=1){
			last=last.prev;
			last.next=null;
		}
		else{
			last=null; first=null;
		}
		siz--;
		return pom.val;
	}
	
	public T pop_front() throws IllegalStateException{
		if(siz==0) throw new IllegalStateException();
		elem pom=first;
		if(siz!=1){
			first=first.next;
			first.prev=null;
		}
		else{
			last=null; first=null;
		}
		siz--;
		return pom.val;
	}
	
	public boolean isEmpty(){ return siz==0;}
	
	public void clear(){
		this.siz=0;
		this.first=null;
		this.last=null;
	}
	
	public boolean retainAll(Collection<?> c){
			boolean ret=false;
			for(T el: this){
				if(!c.contains(el)){
					ret=true;
					this.remove(el);
				}
			}
			return ret;
	}
	
	public boolean removeAll(Collection<?> c){
			boolean ret=false;
			
			while(this.first!=null && this.first.next!=null && c.contains(this.first.val) ){
				this.first=this.first.next; ret=true;
			}
			if(c.contains(first.val)){
				this.first=null; this.last=null; return true;
			}
			this.first.prev=null;
			elem pom=this.first.next;
			while(pom.next!=null){
				while(pom.next!=null && c.contains(pom.next.val)) {pom.next= pom.next.next; pom.next.prev=pom; ret=true;}
				if(pom.next!=null) pom=pom.next;
			}
			this.last=pom;
			return ret;
	}
	
	public boolean contains(Object el){
		elem pomi=first;
		while(pomi!=null){
			if(pomi.val.equals(el)) return true;
			pomi=pomi.next;
		}
		return false;
	}
	
	public boolean containsAll(Collection<?> c){
		for(Object el: c){
			if(!this.contains(el)) return false;
		}
		return true;
	}
	
	public boolean addAll(Collection<? extends T> c){
		for(T el : c){
			this.push_back(el);		
		}
		return true;
	}
	
	public boolean remove(Object o){
		boolean ret=false;
		
		while(!this.isEmpty() && this.first.equals(o)){
			this.pop_front(); ret=true;
		}
		
		while(!this.isEmpty() && this.last.equals(o)){
			this.pop_back(); ret=true;
		}
		
		if(this.isEmpty()) return ret;
		
		elem pomi=this.first;
		
		while(pomi.next!=null){
			if(pomi.next.val.equals(o)){ pomi.next=pomi.next.next; ret=true;}
			else{
				pomi.next.prev=pomi;
				pomi=pomi.next;
			}
		}
		return ret;
	} 
	
	public boolean add(T el){
		boolean ret=this.contains(el);
		if(!ret){
			this.push_back(el); return true;
		}
		return false;
	}
	
	public int size(){
		return this.siz;
	}
	
	public Object[] toArray(){
		Object[] tab = new Object[this.size()];
		int licznik=0;
		elem pomi=this.first;
		while(pomi!=null){
			tab[licznik]=pomi.val;
			licznik+=1; pomi=pomi.next;
		}
		return tab;
	}
	
	public <T2> T2[] toArray(T2[] a){
		T2[] tab= (T2[]) new Object[this.size()];
		int licznik=0;
		elem pomi=this.first;
		while(pomi!=null){
			tab[licznik]=(T2)pomi.val;
			licznik+=1; pomi=pomi.next;
		}
		return tab;
	}
	
	
	public Iterator<T> iterator(){
		return new myit(this.first);
	}
}
