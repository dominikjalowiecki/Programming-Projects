package zadanie;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.Reader;
import java.util.ArrayList;
import java.util.List;

public class Database {
	private static Database instance = null;
	private String fileName;
	
	private Database()
	{
		fileName = "database.txt";
	}
	
	public static Database getInstance()
	{
		if(instance == null)
			instance = new Database();
		
		return instance;
	}
	
	public void write(Person p)
	{
		try {
			FileWriter fw = new FileWriter(fileName, true);
			PrintWriter pw = new PrintWriter(fw);
			
			pw.println(p);
			
			pw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public Person read(int i)
	{		
		try {
			BufferedReader fr = new BufferedReader(new FileReader(fileName));
			
			String line;
			int numberOfLine = 0;
			line = fr.readLine();
			
			while(line != null && i <= Person.getLastIndex())
			{
				if(numberOfLine == i)
				{
					String[] params = line.split(", ");
					return new Person(params[0], params[1], Integer.parseInt(params[2]));
				}
				line = fr.readLine();
				++numberOfLine;
				
			}
			
			fr.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return null;		
	}
	
	public void readAll()
	{
		try {
			BufferedReader fr = new BufferedReader(new FileReader(fileName));
			
			String line;
			line = fr.readLine();
			
			while(line != null)
			{
				System.out.println(line);
				line = fr.readLine();
			}
			
			fr.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
