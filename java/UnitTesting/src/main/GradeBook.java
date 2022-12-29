package main;

import java.util.HashMap;
import java.util.Map;

import exception.GradeBookHasNoSubjectsException;
import exception.SubjectAlreadyExistsException;
import exception.SubjectDoesNotExistsException;
import exception.SubjectHasNoMarksException;

public class GradeBook {
	Map<String, Subject> subjects;

	public GradeBook() {
		subjects = new HashMap<String, Subject>();
	}
	
	public void addSubject(Subject subject) throws NullPointerException, SubjectAlreadyExistsException {
		if(subject == null) throw new NullPointerException("subject cannot be null!");
		if(subjects.containsKey(subject.getName())) throw new SubjectAlreadyExistsException("subject already exists!");
		subjects.put(subject.getName(), subject);
	}
	
	public Subject getSubject(String subjectName) throws NullPointerException, SubjectDoesNotExistsException {
		if(subjectName == null) throw new NullPointerException("subjectName cannot be null!");
		if(subjects.get(subjectName) == null) throw new SubjectDoesNotExistsException("subject doesn't exists!");
		return subjects.get(subjectName);
	}
	
	public float getAverage() throws SubjectHasNoMarksException, GradeBookHasNoSubjectsException {
		if(subjects.size() == 0) throw new GradeBookHasNoSubjectsException("gradeBook has no subjects!");
		
		float average = 0.0f;
		
		for(Subject subject : subjects.values())
			average += subject.getAverage();
		average /= subjects.size();
		
		return average;
	}
}
