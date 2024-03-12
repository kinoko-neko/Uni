
import java.io.*;

public abstract class Figura implements Serializable{
	protected double x,y;
	protected String nazwa;
	
	public String toString(){
		return nazwa+" ("+Double.toString(x)+" , "+Double.toString(y)+" )";
	}
	public void setNazwa(String name){
		this.nazwa=name;
	}
	public abstract void wczytaj(String s);
	public abstract void zapisz(String s);
}
