package observer;

public class A implements Obs {

	private String name;
	
	public A(String name)
	{
		this.name = name;
	}
	
	@Override
	public void notifyState(String s)
	{
		System.out.println(toString() + " - state: " + s);
	}
	
	@Override
	public String toString()
	{
		return name;
	}
}
