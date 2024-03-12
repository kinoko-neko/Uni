import java.util.*;

public class Main{

	public static void main(String args[]){
	
		MyList<Integer> l1= new MyList<Integer>();
		ArrayList<Integer> pom = new ArrayList<Integer>(Arrays.asList(1,2,3,4));
		l1.addAll(pom);
		if(l1.containsAll(pom)) System.out.println("okeee");
		else System.out.println("not good");
		
		l1.add(8);
		  
		for(Integer i: l1) System.out.println(i.toString());
		
		l1.retainAll(pom);
		if(l1.containsAll(pom)) System.out.println("okeee");
		else System.out.println("not good ");
		
		l1.removeAll(pom);
		if(l1.isEmpty()) System.out.println("not good");
		else System.out.println("okeee");
		
		
		
	}
}
