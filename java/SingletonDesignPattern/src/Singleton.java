public class Singleton {
	private static Singleton instance = null;
	
	private Singleton()
	{
	}
	
	public void print()
	{
		System.out.println("Whatever");
	}
	
	public static Singleton getInstance()
	{
		if(instance == null)
			instance = new Singleton();
		
		return instance;
	}
}
