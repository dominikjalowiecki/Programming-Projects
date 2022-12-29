package exception;

public class GradeBookHasNoSubjectsException extends Exception {
	public GradeBookHasNoSubjectsException(String errorMessage) {
		super(errorMessage);
	}
}
