import java.util.HashMap;

public class Main{
	public static void main(String args[]){
		HashMap<String, Integer> zmienne = new HashMap<String, Integer>();
		Variable.variables=zmienne;
		
		Variable.addVariable("x",1);
		Expression e1= new Variable("x");
		System.out.println(e1.eval());
		System.out.println(e1.toString());
		
		Expression e2= new con(2);
		Expression e3= new add(e1,e2);
		Expression e4= new add(e3,e2);
		Expression e5= new mult(e4,e3);
		
		System.out.println(e2.eval());
		System.out.println(e2.toString());
		System.out.println(e3.eval());
		System.out.println(e3.toString());
		System.out.println(e4.eval());
		System.out.println(e4.toString());
		System.out.println(e5.eval());
		System.out.println(e5.toString());
		
	}
}




