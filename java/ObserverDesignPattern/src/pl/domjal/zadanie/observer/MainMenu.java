package pl.domjal.zadanie.observer;

public class MainMenu implements KeyObserver {
	KeyboardReader reader;
	
	public MainMenu()
	{
		reader = new KeyboardReader();
		reader.register(this);
		drawMenu();
		reader.loopProcess();
	}
	
	private void drawMenu()
	{
		System.out.println("1 - Option 1");
		System.out.println("2 - Option 2");
		System.out.println("3 - Option 3");
		System.out.println("X - Exit program");
	}
	
	public void notifyChooseOption(char c)
	{
		switch(c)
		{
			case '1':
				System.out.println("Option 1 chosen.");
				break;
			case '2':
				System.out.println("Option 2 chosen.");
				break;
			case '3':
				System.out.println("Option 3 chosen.");
				break;
			case 'x':
				reader.stopProcess();
				System.out.println("Program shutdown...");
				break;
			default:
				System.out.println("Invalid response...");
		}
	}
}
