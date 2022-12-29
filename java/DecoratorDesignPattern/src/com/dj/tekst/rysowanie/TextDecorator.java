package com.dj.tekst.rysowanie;

public abstract class TextDecorator extends TextDraw {
	TextDraw textDraw;
	
	public TextDecorator(TextDraw t)
	{
		textDraw = t;
	}
}
