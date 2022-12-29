package observer;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class B {
//	private List<Obs> obs = new ArrayList<Obs>();
	private Set<Obs> obs = new HashSet<Obs>();
	private String state = "";
	
	public void registerObserver(Obs o)
	{
		obs.add(o);
	}
	
	public void unregisterObserver(Obs o)
	{
		obs.remove(o);
	}
	
	public void setState(String state)
	{
		this.state = state;
		notifyToAll();
	}
	
	private void notifyToAll()
	{
		for(Obs o : obs)
			o.notifyState(state);
	}
	
}
