import zadanie.Class1;
import zadanie.Class2;

public class Main {

	public static void main(String[] args) {
//		Singleton s = Singleton.getInstance();
//		s.print();
//		System.out.println(s == Singleton.getInstance());
		
		Class1 c1 = new Class1();
		Class2 c2 = new Class2();
		c1.fun1();
		c2.fun2();
	}

}
