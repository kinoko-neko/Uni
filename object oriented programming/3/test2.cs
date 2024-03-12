using System;
//using list;

class prog{
	public static void Main(){
		dict<int,int> d1=new dict<int,int>(500);
		
		Console.WriteLine(d1.rozmiar());
		for(int i=0;i<100;i++) {
			d1.wstaw(i,i*2);
		//	Console.WriteLine("afahgu");
		}
	//	Console.WriteLine("sfadg");
		for(int i=0;i<100;i+=3){
			d1.usun(i);
			if(d1.znajdz(i)) Console.WriteLine("onieeee!!!");
		}
		for(int i=0;i<100;i+=6){
			d1.wstaw(i,-1);
		}
		for(int i=0;i<20;i++){
			Console.WriteLine(d1.wartosc(i));
		}
		
	
	}
}
