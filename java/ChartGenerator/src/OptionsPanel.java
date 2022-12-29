import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class OptionsPanel extends JPanel {
	JLabel titleLabel, aLabel, bLabel, cLabel, scaleLabel, functionLabel;
	JComboBox functionComboBox;
	JTextField aTextField, bTextField, cTextField, scaleTextField;
	JSlider aSlider, bSlider, cSlider, scaleSlider;
	JPanel aPanel, aSliderPanel, bPanel, bSliderPanel, cPanel, cSliderPanel, scalePanel, scaleSliderPanel, functionPanel;
	double a, b, c;
	Functions function;
	ChartPanel chartPanel;
	
	OptionsPanel(ChartPanel chartPanel)
	{
		setPreferredSize(new Dimension(300, 500));
		
		this.chartPanel = chartPanel;
		
		titleLabel = new JLabel("Math Graphs");
		titleLabel.setFont(new Font("MV Boli", Font.BOLD, 30));
		titleLabel.setBorder(BorderFactory.createEmptyBorder(20, 0, 20, 0));
		add(titleLabel);
		
		a = b = c = 0;
		function = Functions.LINEAR_FUNCTION;
		chartPanel.redrawPanel(a, b, c, function);

		aPanel = new JPanel();
		aPanel.setPreferredSize(new Dimension(225, 75));
		aPanel.setLayout(new GridLayout(2, 1));
		aLabel = new JLabel("Parameter 'a' value: ");
		
		aSliderPanel = new JPanel();
		aSlider = new JSlider(JSlider.HORIZONTAL, -10, 10, 0);
		aSlider.setMajorTickSpacing(10);
		aSlider.setMinorTickSpacing(1);
		aSlider.setPaintTicks(true);
		aSlider.setSnapToTicks(true);
		aSlider.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent e)
			{
				if(a != aSlider.getValue())
				{
					a = aSlider.getValue();
					aTextField.setText(String.valueOf((int)a));
					chartPanel.redrawPanel(a, b, c, function);
				}
			}
		});
		aSlider.setPreferredSize(new Dimension(175, 30));

		aTextField = new JTextField(String.valueOf(aSlider.getValue()));
		aTextField.setEditable(false);
		aTextField.setPreferredSize(new Dimension(25, 30));
		
		aSliderPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 0, 0));
		aSliderPanel.setPreferredSize(new Dimension(225, 30));
		aSliderPanel.add(aSlider);
		aSliderPanel.add(aTextField);
		
		aPanel.add(aLabel);
		aPanel.add(aSliderPanel);
		add(aPanel);
		
		
		
		bPanel = new JPanel();
		bPanel.setPreferredSize(new Dimension(225, 75));
		bPanel.setLayout(new GridLayout(2, 1));
		bLabel = new JLabel("Parameter 'b' value: ");
		
		bSliderPanel = new JPanel();
		bSlider = new JSlider(JSlider.HORIZONTAL, -10, 10, 0);
		bSlider.setMajorTickSpacing(10);
		bSlider.setMinorTickSpacing(1);
		bSlider.setPaintTicks(true);
		bSlider.setSnapToTicks(true);
		bSlider.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent e) {
				if(b != bSlider.getValue())
				{
					b = bSlider.getValue();
					bTextField.setText(String.valueOf((int)b));
					chartPanel.redrawPanel(a, b, c, function);
				}
			}
		});
		bSlider.setPreferredSize(new Dimension(175, 30));

		
		bTextField = new JTextField(String.valueOf(bSlider.getValue()));
		bTextField.setEditable(false);
		bTextField.setPreferredSize(new Dimension(25, 30));
		bSliderPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 0, 0));
		bSliderPanel.setPreferredSize(new Dimension(225, 30));
		bSliderPanel.add(bSlider);
		bSliderPanel.add(bTextField);
		bPanel.add(bLabel);
		bPanel.add(bSliderPanel);
		add(bPanel);
		
		
		
		
		cPanel = new JPanel();
		cPanel.setPreferredSize(new Dimension(225, 75));
		cPanel.setLayout(new GridLayout(2, 1));
		cLabel = new JLabel("Parameter 'c' value: ");
		
		cSliderPanel = new JPanel();
		cSlider = new JSlider(JSlider.HORIZONTAL, -10, 10, 0);
		cSlider.setMajorTickSpacing(10);
		cSlider.setMinorTickSpacing(1);
		cSlider.setPaintTicks(true);
		cSlider.setSnapToTicks(true);
		cSlider.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent e) {
				if(c != cSlider.getValue())
				{
					c = cSlider.getValue();
					cTextField.setText(String.valueOf((int)c));
					chartPanel.redrawPanel(a, b, c, function);
				}
			}
		});
		cSlider.setPreferredSize(new Dimension(175, 30));
		cSlider.setEnabled(false);
		
		cTextField = new JTextField(String.valueOf(cSlider.getValue()));
		cTextField.setEditable(false);
		cTextField.setPreferredSize(new Dimension(25, 30));
		cSliderPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 0, 0));
		cSliderPanel.setPreferredSize(new Dimension(225, 30));
		cSliderPanel.add(cSlider);
		cSliderPanel.add(cTextField);
		
		cPanel.add(cLabel);
		cPanel.add(cSliderPanel);
		add(cPanel);
		
		
		
		functionPanel = new JPanel();
		functionPanel.setLayout(new GridLayout(2, 1));
		functionLabel = new JLabel("Choose a function: ");
		functionComboBox = new JComboBox<Functions>(Functions.values());
		functionComboBox.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e)
			{
				function = (Functions)functionComboBox.getSelectedItem();
				
				if(function == Functions.LINEAR_FUNCTION)
				{
					cSlider.setEnabled(false);
					bLabel.setText("Parameter 'b' value: ");
					cLabel.setText("Parameter 'c' value: ");
				} else if(function == Functions.SQUARE_FUNCTION)
				{
					cSlider.setEnabled(true);
					bLabel.setText("Parameter 'b' value: ");
					cLabel.setText("Parameter 'c' value: ");
				} else if(function == Functions.POWER_FUNCTION)
				{
					cSlider.setEnabled(true);
					bLabel.setText("Vector 'p' value: ");
					cLabel.setText("Vector 'q' value: ");
				} else if(function == Functions.CIRCLE_FUNCTION)
				{
					cSlider.setEnabled(true);
					bLabel.setText("Vector 'p' value: ");
					cLabel.setText("Vector 'q' value: ");
				}
				
				chartPanel.redrawPanel(a, b, c, function);
			}
			
		});
		
		functionPanel.setPreferredSize(new Dimension(225, 75));
		functionPanel.add(functionLabel);
		functionPanel.add(functionComboBox);
		add(functionPanel);
	}
	
}
