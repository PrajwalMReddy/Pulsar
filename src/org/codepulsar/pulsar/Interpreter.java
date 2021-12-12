package org.codepulsar.pulsar;

import java.util.ArrayList;

public class Interpreter {
    private final String sourceCode;
    private ArrayList<Instruction> instructions;

    public Interpreter(String sourceCode) {
        this.sourceCode = sourceCode;
        this.instructions = new ArrayList<>();
    }

    public void interpret() {
        Parser parser = new Parser(this.sourceCode);
        ArrayList<Instruction> instructions = parser.parse();

        System.out.println(instructions);

        if (parser.hasError) {
            for (Error error: parser.errors) {
                System.out.println(reportError(error));
            }
        } else {
            execute();
        }
    }

    private String reportError(Error error) {
        String errorMessage = error.getEtype();
        errorMessage += " | " + error.getMessage();
        errorMessage += ";\nOn Line " + error.getToken().getLine();
        return errorMessage;
    }

    private void execute() {
    }
}
