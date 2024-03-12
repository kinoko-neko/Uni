using System;
//using list;

class prog{
	public static void Main(){
		MyList<int> lista1=new MyList<int>();
		MyList<int> lista2=new MyList<int>();
		
		for(int i=0;i<10;i++) {
			lista1.push_front(i);
			lista2.push_back(i);
		}
		Console.WriteLine(lista1.is_empty());
		for(int i=9;i>=0;i--){
			
			if(lista2.pop_front()!=lista1.pop_back()){
				Console.WriteLine("onie");
			}
			
			Console.WriteLine("okeee");
		//	Console.WriteLine(lista1.pop_back());
			
		}
		Console.WriteLine("done");
	}
}
