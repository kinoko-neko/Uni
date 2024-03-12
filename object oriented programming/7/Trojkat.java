
import java.io.*;

public class Trojkat extends Figura{
	protected double x1,y1,x2,y2;
	
	public Trojkat(double x, double y, double x1, double y1, double x2, double y2, String name){
		this.x = x;
		this.y = y;
		this.x1 = x1;
		this.y1 = y1;
		this.x2 = x2;
		this.y2 = y2;
		this.nazwa=name;
	}
	
	public void setX(double v){
		this.x = v;
	}
	public void setX1(double v){
		this.x1 = v;
	}
	public void setX2(double v){
		this.x2 = v;
	}
	public void setY(double v){
		this.y = v;
	}
	public void setY1(double v){
		this.y1 = v;
	}
	public void setY2(double v){
		this.y2 = v;
	}
	
	
	public Trojkat(){
		this.x = 0.0;
		this.y = 0.0;
		this.x1 = 0.0;
		this.y1 = 0.0;
		this.x2 = 0.0;
		this.y2 = 0.0;
		this.nazwa = "";
	}
	
	public String toString(){
		return "( "+Double.toString(x)+" ," +Double.toString(y)+" ) ( "
				+Double.toString(x1)+" , "+Double.toString(y1)+" ) ( "
				+Double.toString(x2)+" , "+Double.toString(y2)+" )";
	}
	
	public void wczytaj(String s){
		try{
			FileInputStream plik = new FileInputStream(s);
			ObjectInputStream input = new ObjectInputStream(plik);
    
  	  Trojkat pom = (Trojkat)input.readObject();
			
			this.x = pom.x;
			this.y = pom.y;
			this.x1 = pom.x1;
			this.y1 = pom.y1;
			this.x2 = pom.x2;
			this.y2 = pom.y2;
			this.nazwa= pom.nazwa;
		
			input.close();
			plik.close();
		}
		catch(Exception e){
		
		}
	}
	
	public void zapisz(String s){
		try{
			FileOutputStream plik = new FileOutputStream(s);
			ObjectOutputStream output = new ObjectOutputStream(plik);
		
			output.writeObject(this);
			output.close();
			plik.close();
		}
		catch(Exception e){
		
		}
	}
}
