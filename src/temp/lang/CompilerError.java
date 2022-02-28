package temp.lang;

import java.util.ArrayList;

public class CompilerError {
    private final ArrayList<Error> errors;

    public CompilerError() {
        this.errors = new ArrayList<>();
    }

    public Error addError(String errorType, String message, int line) {
        Error error = new Error(errorType, message, line);
        this.errors.add(error);
        return error;
    }

    public boolean hasError() {
        return errorCount() != 0;
    }

    public int errorCount() {
        return this.errors.size();
    }

    public ArrayList<Error> getErrors() {
        return this.errors;
    }

    public static class Error {
        private final String errorType;
        private final String message;
        private final int line;

        public Error(String errorType, String message, int line) {
            this.errorType = errorType;
            this.message = message;
            this.line = line;
        }

        public String getErrorType() {
            return this.errorType;
        }

        public String getMessage() {
            return this.message;
        }

        public int getLine() {
            return line;
        }
    }
}
