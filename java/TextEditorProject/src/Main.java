/*
 * From Bro Code's tutorial
 */

import javax.swing.SwingUtilities;

public class Main {

	public static void main(String[] args) {
		
		SwingUtilities.invokeLater(new Runnable() {
				@Override
				public void run() {
					TextEditor te = new TextEditor();
				}
			}
		);
		
	}

}
