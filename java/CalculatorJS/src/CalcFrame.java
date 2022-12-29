import java.awt.Dimension;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class CalcFrame extends JFrame {
	JPanel calcPanel;
	
	public CalcFrame() {
		setup();
	}
	
	public CalcFrame(String title) {
		super(title);
		setup();
	}
	
	private void setup() {
		calcPanel = new CalculatorPanel();
		add(calcPanel);
		setPreferredSize(new Dimension(300, 300));
		pack();
		setVisible(true);
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}
