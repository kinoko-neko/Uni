import java.util.*;

public class Main{

	public static void main(String args[]){
		
		Vector<rank>hier= new Vector<rank>();
		ranklist x= new ranklist();
		ranklist.kol=hier;
		rank r1=new szeregowy("asdsas",x);
		rank r2=new plutonowy("eeeeee",x);
		rank r3=new kapral("safsdafasf",x);
		rank r4=new sierzant("sdaf",x);
		
		x.addrank(r1); x.addrank(r2);
		x.addrank(r3); x.addrank(r4);
		
		rank s1= new kapral("sads",x);
		System.out.println(s1.get_rank());
		System.out.println(r1.get_rank());
		
		OrdList<rank> lista= new OrdList();
		 
		lista.add_elem(r2);
		System.out.println(lista.toString());
		System.out.println(lista.get_first().toString());
		lista.add_elem(r4);
		System.out.println(lista.toString());
		System.out.println(lista.get_first().toString());
		lista.add_elem(r3);
		System.out.println(lista.toString());
		System.out.println(lista.get_first().toString());
		lista.add_elem(r1);
		System.out.println(lista.toString());
		System.out.println(lista.get_first().toString());
	}
}
