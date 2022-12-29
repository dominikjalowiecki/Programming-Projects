package pl.domjal.zadanie.observer;

import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class KeyboardReader {
	Set<KeyObserver> obs = new HashSet<KeyObserver>();
	boolean loop;
	char input;
	
	public void register(KeyObserver o)
	{
		obs.add(o);
	}
	
	public void unregister(KeyObserver o)
	{
		obs.remove(o);
	}
	
	public void loopProcess()
	{
		loop = true;
		Scanner s = new Scanner(System.in);

		while(loop)
		{
			input = s.next().charAt(0);
			notifyToAll();
		}		
	}
	
	public void stopProcess()
	{
		loop = false;
	}
	
	private void notifyToAll()
	{
		for(KeyObserver o : obs)
			o.notifyChooseOption(input);
	}
}
