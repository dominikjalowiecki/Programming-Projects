package com.dj.pizza;

public class Cheese extends PizzaDecorator {
	public Cheese(Pizza p)
	{
		super(p);
	}
	
	public int getPrice()
	{
		return (pizza.getPrice() + 20);
	}
	
	public String getInfo()
	{
		return (pizza.getInfo() + "ser, ");
	}
}
