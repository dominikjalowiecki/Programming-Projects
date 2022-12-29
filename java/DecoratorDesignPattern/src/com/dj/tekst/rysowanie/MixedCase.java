package com.dj.tekst.rysowanie;

public class MixedCase extends TextDecorator {
	public MixedCase(TextDraw t)
	{
		super(t);
	}
	
	public void print(String s)
	{
		String res = "";
		
		for(int i = 0, size = s.length(); i < size; i++)
			if(i % 2 == 1)
				res += s.substring(i, i + 1).toUpperCase();
			else
				res += s.substring(i, i + 1).toLowerCase();
		
		textDraw.print(res);
	}
}
