package temp.lang;

import java.util.ArrayList;

public class CompilerError {
    private ArrayList<Error> errors;

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

    public static class Error {
        private String errorType;
        private String message;
        private Token token;

        public Error(String errorType, String message, Token token) {
            this.errorType = errorType;
            this.message = message;
            this.token = token;
        }
    }
}
