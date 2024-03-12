using System;

public class MyList<T> {
	
	class elem{
		public elem next,prev;
		public T val;
		
		public elem(T wart){
			this.prev=null;
			this.next=null;
			this.val=wart;
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
	
	public void push_front(T x){
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

	public T pop_back(){
		if(siz==0) return default(T);
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
	
	public T pop_front(){
		if(siz==0) return default(T);
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
	
	public bool is_empty(){ return siz==0;}
	
}
