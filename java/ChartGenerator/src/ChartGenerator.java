import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.JFrame;

public class ChartGenerator extends JFrame
{
	ChartPanel chartPanel;
	OptionsPanel optionsPanel;
	FooterPanel footerPanel;
	
	ChartGenerator()
	{
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setResizable(false);
		setLayout(new BorderLayout());
		setTitle("Chart Generator");
		
		chartPanel = new ChartPanel();
		optionsPanel = new OptionsPanel(chartPanel);
		footerPanel = new FooterPanel();
		
		add(chartPanel, BorderLayout.WEST);
		add(optionsPanel, BorderLayout.EAST);
		add(footerPanel, BorderLayout.SOUTH);
		
		pack();
		setVisible(true);
	}
}
