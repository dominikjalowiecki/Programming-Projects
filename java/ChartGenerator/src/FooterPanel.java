import java.awt.Dimension;

import javax.swing.JLabel;
import javax.swing.JPanel;

public class FooterPanel extends JPanel
{
	JLabel field;
	
	FooterPanel()
	{
		setPreferredSize(new Dimension(800, 30));
		
		field = new JLabel("Created by Dominik Jałowiecki");
		add(field);
	}
}
