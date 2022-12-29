package zadanie;

public class Class1 {
	
	public void fun1()
	{
		Database db = Database.getInstance();
		
		Person p1 = new Person("Jan", "Kowalski", 32);
		db.write(p1);
		db.write(new Person("Adam", "Nowak", 56));
		
		db.readAll();
	}
	
}
