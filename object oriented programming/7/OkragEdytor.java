import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class OkragEdytor implements ActionListener{
	
	private Okrag okrag;
	protected Container kontener;
	private JTextField x;
	private JTextField y;
	private JTextField radius;
	private JTextField nazwa;
	private String plik;
	
	private void update(double x, double y, double radius, String name){
		okrag.setX(x);
		okrag.setY(y);
		okrag.setR(radius);
		okrag.setNazwa(name);
	}
	
	public void actionPerformed(ActionEvent e){
		double px;
		double py;
		double pradius;
		String pname;
		
		px = Double.parseDouble(x.getText());
		py = Double.parseDouble(y.getText());
		pradius = Double.parseDouble(radius.getText());
		pname = nazwa.getText();
		
		update(px,py,pradius,pname);
		okrag.zapisz(plik);
	}
	
	public OkragEdytor(JFrame okno, String s){
		okrag= new Okrag();
		this.plik=s;
		
		this.kontener = okno.getContentPane();
		
		JButton zapisz = new JButton("Zapisz");
		zapisz.addActionListener(this);
		
		
		this.x = new JTextField(Double.toString(this.okrag.x),50);
		this.y = new JTextField(Double.toString(this.okrag.y));
		this.radius = new JTextField(Double.toString(this.okrag.y));
		this.nazwa = new JTextField(this.okrag.nazwa);
		
		kontener.setLayout(new GridLayout(5,2));
		kontener.setPreferredSize(new Dimension (400,400) );
		
		kontener.add(new JLabel("Nazwa:"));
		kontener.add(this.nazwa);
	
		kontener.add(new JLabel("x:"));
		kontener.add(this.x);
		
		kontener.add(new JLabel("y:"));
		kontener.add(this.y);
		
		kontener.add(new JLabel("Promien:"));
		kontener.add(this.radius);
		
		kontener.add(new JLabel(""));
		kontener.add(zapisz);
	}
}
