import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class TrojkatEdytor implements ActionListener{
	
	Trojkat trojkat;
	protected Container kontener;
	private JTextField x;
	private JTextField y;
	private JTextField x1;
	private JTextField y1;
	private JTextField x2;
	private JTextField y2;
	private JTextField nazwa;
	private String plik;
	
	private void update(double x, double y, double x1, double y1, double x2, double y2, String name){
		trojkat.setX(x);
		trojkat.setY(y);
		trojkat.setX1(x1);
		trojkat.setY1(y1);
		trojkat.setX2(x2);
		trojkat.setY2(y2);
		trojkat.setNazwa(name);
	}
	
	public void actionPerformed(ActionEvent e){
		double px,py,px1,py1,px2,py2; 
		String pname;
		
		px = Double.parseDouble(x.getText());
		py = Double.parseDouble(y.getText());
		px1 = Double.parseDouble(x1.getText());
		py1 = Double.parseDouble(y1.getText());
		px2 = Double.parseDouble(x2.getText());
		py2 = Double.parseDouble(y2.getText());
		pname = nazwa.getText();
		
		update(px,py,px1,py1,px2,py2,pname);
		trojkat.zapisz(plik);
	}
	
	public TrojkatEdytor(JFrame okno, String s){
		trojkat = new Trojkat();
		this.plik=s;
		
		this.kontener = okno.getContentPane();
		
		JButton zapisz = new JButton("Zapisz");
		zapisz.addActionListener(this);
		
		this.x = new JTextField(Double.toString(this.trojkat.x),50);
		this.y = new JTextField(Double.toString(this.trojkat.y));
		this.x1 = new JTextField(Double.toString(this.trojkat.x1));
		this.y1 = new JTextField(Double.toString(this.trojkat.y1));
		this.x2 = new JTextField(Double.toString(this.trojkat.x2));
		this.y2 = new JTextField(Double.toString(this.trojkat.y2));
		this.nazwa = new JTextField(this.trojkat.nazwa);
		
		kontener.setLayout(new GridLayout(8,2));
		kontener.setPreferredSize(new Dimension (400,600) );
		
		kontener.add(new JLabel("Nazwa:"));
		kontener.add(this.nazwa);
		
		kontener.add(new JLabel("x:"));
		kontener.add(this.x);
		
		kontener.add(new JLabel("y:"));
		kontener.add(this.y);
		
		kontener.add(new JLabel("x1:"));
		kontener.add(this.x1);
		
		kontener.add(new JLabel("y1:"));
		kontener.add(this.y1);
	
		kontener.add(new JLabel("x2:"));
		kontener.add(this.x2);
		
		kontener.add(new JLabel("y2:"));
		kontener.add(this.y2);
		
		kontener.add(new JLabel(""));
		kontener.add(zapisz);
	}
}
