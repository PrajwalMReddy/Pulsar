package org.codepulsar.pulsar;

import java.util.ArrayList;

public class Interpreter {
    private final String sourceCode;
    private ArrayList<Instruction> instructions;
    public GlobalVariable globals;

    public Interpreter(String sourceCode) {
        this.sourceCode = sourceCode;
        this.instructions = new ArrayList<>();
        this.globals = new GlobalVariable();
    }

    public void interpret() {
        Parser parser = new Parser(this.sourceCode);
        this.instructions = parser.parse();

        if (CommandsKt.getDebug()) {
            Disassembler.disassemble(this.instructions);
            System.out.println();
        }

        if (parser.hasErrors) {
            System.out.println("-- Errors --");
            for (Error error: parser.errors) {
                System.out.println(reportError(error) + "\n");
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
