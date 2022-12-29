package exception;

public class SubjectAlreadyExistsException extends Exception {
	public SubjectAlreadyExistsException(String errorMessage) {
		super(errorMessage);
	}
}
