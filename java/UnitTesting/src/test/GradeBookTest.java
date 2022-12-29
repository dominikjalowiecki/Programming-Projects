package test;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import exception.GradeBookHasNoSubjectsException;
import exception.InvalidMarkException;
import exception.SubjectAlreadyExistsException;
import exception.SubjectDoesNotExistsException;
import exception.SubjectHasNoMarksException;
import main.GradeBook;
import main.Subject;

public class GradeBookTest {
	
	GradeBook gradeBook;
	
	private static final String SUBJECT_NAME_1 = "Matematyka";
	private static final String SUBJECT_NAME_2 = "Geografia";
	private static final String SUBJECT_NAME_3 = "Historia";

	@Before
	public void setUp() throws Exception {
		gradeBook = new GradeBook();
	}
	
	@Test
	public void addSubjectTest() throws NullPointerException, SubjectAlreadyExistsException {
		Subject subject = new Subject(SUBJECT_NAME_1);
		gradeBook.addSubject(subject);
	}
	
	@Test(expected=NullPointerException.class)
	public void addSubjectNullPointerExceptionTest() throws NullPointerException, SubjectAlreadyExistsException {
		gradeBook.addSubject(null);
	}
	
	public void addSubjectSubjectAlreadyExistsExceptionTest() throws NullPointerException, SubjectAlreadyExistsException {
		Subject subject = new Subject(SUBJECT_NAME_1);
		gradeBook.addSubject(subject);
		assertThrows(SubjectAlreadyExistsException.class, () -> gradeBook.addSubject(subject));
	}
	
	@Test
	public void getSubjectTest() throws NullPointerException, SubjectAlreadyExistsException, SubjectDoesNotExistsException {
		Subject subject = new Subject(SUBJECT_NAME_1);
		gradeBook.addSubject(subject);
		assertTrue(subject.equals(gradeBook.getSubject(SUBJECT_NAME_1)));
	}
	
	@Test(expected=NullPointerException.class)
	public void getSubjectNullPointerExceptionTest() throws NullPointerException, SubjectDoesNotExistsException {
		gradeBook.getSubject(null);
	}
	
	public void getSubjectSubjectDoesNotExistsTest() {
		assertThrows(SubjectDoesNotExistsException.class, () -> gradeBook.getSubject(SUBJECT_NAME_1));
	}
	
	@Test
	public void getAverageTest() throws InvalidMarkException, NullPointerException, SubjectAlreadyExistsException, SubjectHasNoMarksException, GradeBookHasNoSubjectsException {
		Subject subject1 = new Subject(SUBJECT_NAME_1);
		Subject subject2 = new Subject(SUBJECT_NAME_2);
		Subject subject3 = new Subject(SUBJECT_NAME_3);
		
		subject1.addMark(3);
		subject1.addMark(3);
		subject1.addMark(4);
		
		subject2.addMark(5);
		subject2.addMark(4);
		subject2.addMark(3);
		
		subject3.addMark(2);
		subject3.addMark(2);
		subject3.addMark(5);
		
		float expectedAverage = (subject1.getAverage() + subject2.getAverage() + subject3.getAverage()) / 3;
		
		gradeBook.addSubject(subject1);
		gradeBook.addSubject(subject2);
		gradeBook.addSubject(subject3);
		
		assertEquals(expectedAverage, gradeBook.getAverage(), 0.01);
	}
	
	@Test(expected=GradeBookHasNoSubjectsException.class)
	public void getAverageGradeBookHasNoSubjectsException() throws SubjectHasNoMarksException, GradeBookHasNoSubjectsException {
		gradeBook.getAverage();
	}
}
