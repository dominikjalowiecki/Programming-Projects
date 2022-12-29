package zadanie;

public class Class2 {
	
	public void fun2()
	{
		Database db = Database.getInstance();
		
		db.write(new Person("Julia", "Nowak", 19));
		
//		System.out.println(db.read(0));
//		System.out.println(db.read(2));
		System.out.println(db.read(Person.getLastIndex()));
//		System.out.println(db.read(-5));
//		System.out.println(db.read(45));
	}

}
