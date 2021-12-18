package org.codepulsar.pulsar;

import org.codepulsar.primitives.Primitive;

import java.util.ArrayList;
import java.util.HashMap;

public class Interpreter {
    private final String sourceCode;
    private ArrayList<Instruction> instructions;
    public static HashMap<String, Primitive> variableValues;

    public Interpreter(String sourceCode) {
        this.sourceCode = sourceCode;
        this.instructions = new ArrayList<>();
        this.variableValues = new HashMap<>();
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
