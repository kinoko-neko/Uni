
import java.io.*;

public class Okrag extends Figura{
	protected double r;
	
	public Okrag(double px, double py, double pradius, String pname){
		this.x = px;
		this.y = py;
		this.r = pradius;
		this.nazwa = pname;
	}
	
	public Okrag(){
		this.x = 0.0;
		this.y = 0.0;
		this.r = 0.0;
		this.nazwa = "";
	}
	
	public void setX(double v){
		this.x = v;
	}
	public void setY(double v){
		this.y = v;
	}
	public void setR(double v){
		this.r = v;
	}
	
	
	public void wczytaj(String s){
		try{
			FileInputStream plik = new FileInputStream(s);
			ObjectInputStream input = new ObjectInputStream(plik);
    
    	Okrag pom = (Okrag)input.readObject();
		
			this.x = pom.x;
			this.y = pom.y;
			this.r = pom.r;
			this.nazwa = pom.nazwa;
		
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
	
	public String toString(){
		return super.toString()+" r = "+Double.toString(this.r);
	}
}
