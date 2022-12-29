import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.geom.Line2D;

import javax.swing.BorderFactory;
import javax.swing.JPanel;

public class ChartPanel extends JPanel
{
	final int SIZE = 600;
	final int WIDTH = SIZE;
	final int HEIGHT = SIZE;
	final int GAP = 20;
	final float CONVERSION_FACTOR = (float) 1 / GAP;
	double a = 0, b = 0, c = 0;
	Functions function;
	FunctionParameters parameters;
	
	Graphics2D g2d;
	
	ChartPanel()
	{
		setPreferredSize(new Dimension(WIDTH, HEIGHT));
		setBorder(BorderFactory.createEmptyBorder());
		
		parameters = new FunctionParameters();
	}
	
	@Override
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		g2d = (Graphics2D) g;
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		drawLines();
		
		g2d.setStroke(new BasicStroke(3));
		g2d.setColor(Color.RED);
		drawFunction(a, b, c, function);
	}
	
	public void redrawPanel(double a, double b, double c, Functions function)
	{
		this.a = a;
		this.b = b;
		this.c = c;
		this.function = function;
		
		repaint();
	}

	private void drawLines()
	{
		g2d.setStroke(new BasicStroke(1));
		g2d.setFont(new Font("MV Boli", Font.BOLD, 12));
		int counter = WIDTH / GAP / -2 + 1;
		for(int coord = GAP; coord < SIZE; coord += GAP)
		{
			
			if(coord == SIZE/2) {
				g2d.drawString(String.valueOf(counter), coord - 13, WIDTH/2 + 15);
				++counter;
				continue;
			}
			
			g2d.setColor(Color.GRAY);
			// Horizontal line
			g2d.drawLine(0, coord, WIDTH, coord);
			// Vertical line
			g2d.drawLine(coord, 0, coord, HEIGHT);
			
			g2d.setColor(Color.BLACK);
			// Horizontal numbers
			g2d.drawString(String.valueOf(counter), coord - 10, WIDTH/2 + 15);
			// Vertical numbers
			g2d.drawString(String.valueOf(-counter), HEIGHT/2 + 5, coord + 5);
			++counter;
		}
		
		g2d.setStroke(new BasicStroke(3));
		// Horizontal middle line
		g2d.drawLine(0, HEIGHT/2, WIDTH, HEIGHT/2);
		// Vertical middle line
		g2d.drawLine(WIDTH/2, 0, WIDTH/2, HEIGHT);
	}
	
	private void drawFunction(double a, double b, double c, Functions function)
	{
		double x;
		double y = 0, prevY = 0;
		boolean init = false;
		
		parameters.setA(a);
		parameters.setB(b);
		parameters.setC(c);
		
		int offset = 1;
		
		for(int i = 0; i <= WIDTH; i+=offset)
		{
			x = (i - (WIDTH/2));
			
			if(function.getIfIsMovable())
			{
				parameters.setX((Math.round(x * CONVERSION_FACTOR * 100.0) / 100.0 - b));
				y = (function.getValue(parameters) + c) / CONVERSION_FACTOR;
			} else {
				parameters.setX(Math.round(x * CONVERSION_FACTOR * 100.0) / 100.0);
				y = function.getValue(parameters) / CONVERSION_FACTOR;
			}
			
			if(y == Double.POSITIVE_INFINITY || y == Double.NEGATIVE_INFINITY)
			{
				init = false;
				continue;
			}
			
			if(y > HEIGHT/2) y = HEIGHT / 2;
			else if (y < -HEIGHT/2) y = -HEIGHT/2;
			
			if(!init)
			{
				prevY = y;
				init = true;
				continue;
			}
			
			if((prevY == HEIGHT / 2 || prevY == -HEIGHT / 2) && (y == HEIGHT / 2 || y == -HEIGHT / 2))
			{
				prevY = y;
				continue;
			}

			if(y <= HEIGHT/2 && y >= -(HEIGHT/2))
			{
				g2d.draw(new Line2D.Double(WIDTH/2 + (x-offset), HEIGHT/2 - prevY, WIDTH/2 + x, HEIGHT/2 - y));
			}
			prevY = y;
		}
		
		if(function.getIfIsAbsolute())
		{
			for(int i = 0; i <= WIDTH; i+=offset)
			{
				x = i - (WIDTH/2);
				
				if(function.getIfIsMovable())
					parameters.setX(Math.round(x * CONVERSION_FACTOR * 100.0) / 100.0 - b);
				else
					parameters.setX(Math.round(x * CONVERSION_FACTOR * 100.0) / 100.0);
				
				y = -((function.getValue(parameters) - c) / CONVERSION_FACTOR);
				
				if(y == Double.POSITIVE_INFINITY || y == Double.NEGATIVE_INFINITY)
				{
					init = false;
					continue;
				}
				
				if(y > HEIGHT/2) y = HEIGHT / 2;
				else if (y < -HEIGHT/2) y = -HEIGHT/2;
				
				if(!init)
				{
					prevY = y;
					init = true;
					continue;
				}
				
				if((prevY == HEIGHT / 2 || prevY == -HEIGHT / 2) && (y == HEIGHT / 2 || y == -HEIGHT / 2))
				{
					prevY = y;
					continue;
				}

				if(y <= HEIGHT/2 && y >= -(HEIGHT/2))
				{
					g2d.draw(new Line2D.Double(WIDTH/2 + (x-offset), HEIGHT/2 - prevY, WIDTH/2 + x, HEIGHT/2 - y));

				}
				prevY = y;
			}
		}

	}
}
