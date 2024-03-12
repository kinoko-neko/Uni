import java.util.HashMap;

public interface Expression{
	public int eval();
	public String toString();
}

class con implements Expression{
	int wal;
	con (int x){ this.wal=x;}
	public int eval(){ return wal;}
	public String toString(){ return String.valueOf(wal);}
}

class Variable implements Expression  {
	String nazwa;
	int wal;
	static HashMap<String, Integer> variables = new HashMap<String, Integer>();
	
	Variable (String nazw){ this.nazwa=nazw;}
	
	public int eval() throws ArithmeticException{
		if (variables.get(nazwa) != null)
			return variables.get(nazwa);
		throw new ArithmeticException();
	}

	public static void addVariable(String nazw,int x){
		variables.put(nazw, x);
	}

	public String toString(){return nazwa;}

}

class add implements Expression   {
	Expression lewy,prawy;
	
	add (Expression l, Expression p){
		this.lewy=l;
		this.prawy=p;
	}
	public int eval() throws ArithmeticException{
		int pomi;
		try{
			pomi=lewy.eval()+prawy.eval();
		}
		catch(ArithmeticException e){
		 throw new ArithmeticException(); 
		}
		return pomi;
	}
	public String toString(){
		return "( "+lewy.toString()+" + " +prawy.toString() +" )";
	}
}

class mult implements Expression   {
	Expression lewy,prawy;
	
	mult (Expression l, Expression p){
		this.lewy=l;
		this.prawy=p;
	}
	public int eval() throws ArithmeticException {
		int pomi;
		try{
			pomi=lewy.eval()*prawy.eval();
		}
		catch(ArithmeticException e){
		 throw new ArithmeticException(); 
		}
		return pomi;
	}
	public String toString(){
		return "( "+lewy.toString()+" * " +prawy.toString() +" )";
	}
}
