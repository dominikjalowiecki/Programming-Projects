package main;

import java.util.ArrayList;
import java.util.List;

import exception.InvalidMarkException;
import exception.SubjectHasNoMarksException;

public class Subject {
	private List<Integer> marks;
	private String name;
	
	public String getName() {
		return name;
	}

	public Subject(String name) throws NullPointerException {
		if(name == null) throw new NullPointerException("Name cannot be null!");
		this.name = name;
		marks = new ArrayList<Integer>();
	}
	
	public void addMark(int mark) throws InvalidMarkException {
		if(mark < 1 || mark > 6) throw new InvalidMarkException("Mark cannot be lower than 1 or higher than 6!");
		marks.add(mark);
	}
	
	public float getAverage() throws SubjectHasNoMarksException {
		if(marks.size() == 0) throw new SubjectHasNoMarksException("subject has no marks!");
		
		float average = 0.0f;
		
		for(Integer mark : marks)
			average += mark;
		average /= marks.size();
		
		return average;
	}
	
}
