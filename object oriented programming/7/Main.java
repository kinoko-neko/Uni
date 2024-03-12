import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;

public class Main{
	public static void main(String[] args){
		
		if(args.length!=2){
			System.out.println("Zle dane"); return;
		}
		
		if(!args[1].equals("Trojkat") && !args[1].equals("Okrag")){
			System.out.println("zle dane"); return;
		}
		
		JFrame frame = new JFrame("Edycja Figury");

		if(args[1].equals("Trojkat")){
			TrojkatEdytor o = new TrojkatEdytor(frame,args[0]);
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
   		frame.setVisible(true);
   		frame.pack();
		}
		else{
			OkragEdytor o = new OkragEdytor(frame,args[0]);
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	frame.setVisible(true);
    	frame.pack();
		}
	}
}
