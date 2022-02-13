package org.codepulsar.pulsar;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class Compiler {
    private final String sourceCode;
    private ArrayList<Instruction> instructions;
    private LocalVariable locals;

    public Compiler(String sourceCode) {
        this.sourceCode = sourceCode;
        this.instructions = new ArrayList<>();
    }

    public void init() throws FileNotFoundException {
        Parser parser = new Parser(this.sourceCode);
        this.instructions = parser.parse();
        this.locals = parser.getLocals();

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
            compile();
        }
    }

    private void compile() throws FileNotFoundException {
        PrintWriter pw = new PrintWriter(Pulsar.fileIn + ".asm");
        pw.println("");
        pw.close();
    }

    private String reportError(Error error) {
        String errorMessage = error.getErrorType();
        errorMessage += " | " + error.getMessage();
        errorMessage += ";\nOn Line " + error.getToken().getLine();
        return errorMessage;
    }
}
