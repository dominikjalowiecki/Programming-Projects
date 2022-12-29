import com.dj.pizza.Cheese;
import com.dj.pizza.Ham;
import com.dj.pizza.Pizza;
import com.dj.tekst.rysowanie.BasicTextDraw;
import com.dj.tekst.rysowanie.Cesar;
import com.dj.tekst.rysowanie.TextDraw;
import com.dj.tekst.rysowanie.MixedCase;

public class Main {

	public static void main(String[] args) {
//		Pizza pizza = new Pizza();
//		System.out.println(pizza.getPrice());
//		System.out.println(pizza.getInfo());
//		
//		pizza = new Ham(pizza);
//		System.out.println(pizza.getPrice());
//		System.out.println(pizza.getInfo());
//		
//		pizza = new Cheese(pizza);
//		System.out.println(pizza.getPrice());
//		System.out.println(pizza.getInfo());
		
		TextDraw textDraw = new BasicTextDraw();
		textDraw.print("Test123");
		
		textDraw = new MixedCase(textDraw);
		textDraw.print("Test123");
		
		textDraw = new Cesar(textDraw);
		textDraw.print("Test123");
	}

}
