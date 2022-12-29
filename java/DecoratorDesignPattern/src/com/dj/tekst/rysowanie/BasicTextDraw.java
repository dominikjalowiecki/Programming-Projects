package com.dj.tekst.rysowanie;

public class BasicTextDraw extends TextDraw {
	public void print(String s)
	{
		s = s.substring(0, 1).toUpperCase() + s.substring(1);
		super.print(s);
	}
}
