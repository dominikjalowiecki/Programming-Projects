package exception;

public class SubjectDoesNotExistsException extends Exception {
	public SubjectDoesNotExistsException(String errorMessage) {
		super(errorMessage);
	}
}
