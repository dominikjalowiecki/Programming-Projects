package exception;

public class SubjectHasNoMarksException extends Exception {
	public SubjectHasNoMarksException(String errorMessage) {
		super(errorMessage);
	}
}
