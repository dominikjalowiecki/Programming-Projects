package com.dj.pizza;

public abstract class PizzaDecorator extends Pizza {
	protected Pizza pizza;
	
	PizzaDecorator(Pizza p)
	{
		pizza = p;
	}
}
