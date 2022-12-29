package com.dj.tekst.rysowanie;

public class Cesar extends TextDecorator {
	final private int shift = 2;
	
	public Cesar(TextDraw t)
	{
		super(t);
	}
	
	public void print(String s)
	{
		String res = "";
		char c;
		
		s.toLowerCase();
		for(int i = 0, size = s.length(); i < size; i++)
		{
			c = s.charAt(i);
			
			if(c >= 'a' && c <= 'z')
				c = (char)((((c - 'a') + shift) % 26) + 'a');
			
			res += c;
		}
		
		textDraw.print(res);
	}
}
