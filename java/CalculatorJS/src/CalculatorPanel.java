import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class CalculatorPanel extends JPanel {
	private JTextArea resultArea;
	private String regexPattern1, regexPattern2, regexPattern3, regexPattern4;
	private StringBuilder calc;
	
	public CalculatorPanel() {
		regexPattern1 = "^-?([0-9]+\\.?[0-9]*(E{1}[0-9]+)?[\\+\\-\\*\\/]?)*$";
		regexPattern2 = "^-?[0-9]+\\.?[0-9]*(E{1}[0-9]+)?([\\+\\-\\*\\/]{1}[0-9]+\\.?[0-9]*)+$";
		regexPattern3 = "^(0{2}|.*[\\+\\-\\*\\/]{1}0{2})$";
		regexPattern4 = "^(0{1}|.*[\\+\\-\\*\\/]{1}0{1})$";
		
		calc = new StringBuilder();
		
		JPanel centralPanel = new JPanel();
		centralPanel.setLayout(new GridLayout(4, 3));
		JPanel rightPanel = new JPanel();
		rightPanel.setLayout(new GridLayout(4, 1));
		ActionListener listener = new CalcAction();
		
		addButton("1", listener, centralPanel);
		addButton("2", listener, centralPanel);
		addButton("3", listener, centralPanel);
		addButton("4", listener, centralPanel);
		addButton("5", listener, centralPanel);
		addButton("6", listener, centralPanel);
		addButton("7", listener, centralPanel);
		addButton("8", listener, centralPanel);
		addButton("9", listener, centralPanel);
		addButton("0", listener, centralPanel);
		addButton(".", listener, centralPanel);
		addButton("=", listener, centralPanel);
		
		addButton("+", listener, rightPanel);
		addButton("-", listener, rightPanel);
		addButton("*", listener, rightPanel);
		addButton("/", listener, rightPanel);
		
		resultArea = new JTextArea(1, 1);
		Font font = new Font("Segoe Script", Font.BOLD, 20);
		resultArea.setFont(font);
		resultArea.setEditable(false);
		JScrollPane sp = new JScrollPane(resultArea, JScrollPane.VERTICAL_SCROLLBAR_NEVER, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		
		this.setLayout(new BorderLayout(5, 5));
		this.add(sp, BorderLayout.NORTH);
		this.add(centralPanel, BorderLayout.CENTER);
		this.add(rightPanel, BorderLayout.EAST);
	}
	
	private void addButton(String label, ActionListener listener, JPanel panel) {
		JButton button = new JButton(label);
		button.addActionListener(listener);
		panel.add(button);
	}
	
	private class CalcAction implements ActionListener {
		ScriptEngineManager manager;
		ScriptEngine engine;

		public CalcAction() {
			manager = new ScriptEngineManager();
			engine = manager.getEngineByName("graal.js");
		}
		
		@Override
		public void actionPerformed(ActionEvent action) {
			String click = action.getActionCommand();
			
			if("=".equals(click) && calc.toString().matches(regexPattern2)) {
				if(calc.charAt(calc.length()-2) == '/' && calc.charAt(calc.length()-1) == '0')
				{
					calc.setLength(0);
					calc.append("0");
				} else
				{
					try {
						String res = engine.eval(resultArea.getText()).toString();
						Double eval = Double.valueOf(res);

						calc.setLength(0);
						calc.append(eval.toString());
					} catch (ScriptException e) {
						e.printStackTrace();
					}
				}
			} else {
				if(calc.toString().matches(regexPattern4) && click.matches("^([0-9]|-)$"))
					calc.setLength(calc.length() - 1);
				calc.append(click);
			}
			
			if(calc.toString().matches(regexPattern1) && !calc.toString().matches(regexPattern3))
			{
				resultArea.setText(calc.toString());
			} else
			{
				calc.setLength(calc.length() - 1);
			}
		}
	}
}
