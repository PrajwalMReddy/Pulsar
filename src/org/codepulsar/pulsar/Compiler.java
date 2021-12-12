package org.codepulsar.pulsar;

import java.util.ArrayList;

public class Compiler {
    private final String sourceCode;

    public Compiler(String sourceCode) {
        this.sourceCode = sourceCode;
    }

    public void compile() {
        Parser parser = new Parser(this.sourceCode);
        ArrayList<Instruction> instructions = parser.parse();

        System.out.println(instructions);

        if (parser.hasError) {
            for (Error error: parser.errors) {
                System.out.println(reportError(error));
            }
        }
    }

    private String reportError(Error error) {
        String errorMessage = error.getEtype();
        errorMessage += " | " + error.getMessage();
        errorMessage += ";\nOn Line " + error.getToken().getLine();
        return errorMessage;
    }
}
