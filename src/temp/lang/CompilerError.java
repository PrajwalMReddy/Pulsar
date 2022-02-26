package temp.lang;

import java.util.ArrayList;

public class CompilerError {
    private final ArrayList<Error> errors;

    public CompilerError() {
        this.errors = new ArrayList<>();
    }

    public Error addError(String errorType, String message, Token token) {
        Error error = new Error(errorType, message, token);
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
        private final Token token;

        public Error(String errorType, String message, Token token) {
            this.errorType = errorType;
            this.message = message;
            this.token = token;
        }

        public String getErrorType() {
            return this.errorType;
        }

        public String getMessage() {
            return this.message;
        }

        public Token getToken() {
            return this.token;
        }
    }
}
