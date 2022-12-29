package test;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import exception.InvalidMarkException;
import exception.SubjectHasNoMarksException;
import main.Subject;


public class SubjectTest {

	Subject subject;
	private static final String SUBJECT_NAME = "Matematyka";
	
	@Before
	public void setUp() throws Exception {
		subject = new Subject(SUBJECT_NAME);
	}
	
	@Test(expected=NullPointerException.class)
	public void setUpNullPointerExceptionTest() {
		new Subject(null);
	}

	@Test
	public void addMarkTest() throws InvalidMarkException {
		subject.addMark(3);
	}
	
	@Test(expected=InvalidMarkException.class)
	public void addMarkInvalidMarkExceptionTest() throws InvalidMarkException {
		subject.addMark(7);
	}
	
	@Test
	public void getAverageTest() throws InvalidMarkException, SubjectHasNoMarksException {
		subject.addMark(3);
		subject.addMark(2);
		subject.addMark(5);
		
		float expectedAverage = (3 + 2 + 5) / (float) 3;
		
		assertEquals(expectedAverage, subject.getAverage(), 0.01);
	}
	
	@Test(expected=SubjectHasNoMarksException.class)
	public void getAverageSubjectHasNoMakrsExceptionTest() throws SubjectHasNoMarksException {
		subject.getAverage();
	}

}
