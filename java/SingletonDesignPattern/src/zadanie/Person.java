package zadanie;

public class Person {
	private String name, surname;
	private int age;
	static int lastIndex = -1;
	
	public Person(String name, String surname, int age)
	{
		this.name = name;
		this.surname = surname;
		this.age = age;
		++lastIndex;
	}
	
	public static int getLastIndex() {
		return lastIndex;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getSurname() {
		return surname;
	}

	public void setSurname(String surname) {
		this.surname = surname;
	}

	public int getAge() {
		return age;
	}

	public void setAge(int age) {
		this.age = age;
	}

	@Override
	public String toString()
	{
		return name + ", " + surname + ", " + age;
	}
	
}
