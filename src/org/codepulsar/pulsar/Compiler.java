package org.codepulsar.pulsar;

import java.util.ArrayList;

public class Compiler {
    private final String sourceCode;
    private ArrayList<Instruction> instructions;

    public Compiler(String sourceCode) {
        this.sourceCode = sourceCode;
        this.instructions = new ArrayList<>();
    }

    public void init() {
        Parser parser = new Parser(this.sourceCode);
        this.instructions = parser.parse();

        if (parser.hasErrors) {
            System.out.println("-- Errors --");
            for (Error error: parser.errors) {
                System.out.println(reportError(error) + "\n");
            }
        } else {
            compile();
        }
    }

    private String reportError(Error error) {
        String errorMessage = error.getErrorType();
        errorMessage += " | " + error.getMessage();
        errorMessage += ";\nOn Line " + error.getToken().getLine();
        return errorMessage;
    }

    private void compile() {
    }
}
