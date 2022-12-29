package com.dj.pizza;

public class Ham extends PizzaDecorator {
	public Ham(Pizza p)
	{
		super(p);
	}
	
	public int getPrice()
	{
		return (pizza.getPrice() + 11);
	}
	
	public String getInfo()
	{
		return (pizza.getInfo() + "szynka, ");
	}
}
