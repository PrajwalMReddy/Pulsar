package org.codepulsar.pulsar;

import org.codepulsar.primitives.Primitive;

import java.util.ArrayList;

public class Interpreter {
    private final String sourceCode;
    private ArrayList<Instruction> instructions;
    public GlobalVariable globals;
    public LocalVariable locals;

    private final int STACK_MAX = 1024;
    private final Primitive[] stack;
    private int sp; // Stack Top
    private int ip; // Instruction Pointer

    public Interpreter(String sourceCode) {
        this.sourceCode = sourceCode;
        this.instructions = new ArrayList<>();
        this.globals = new GlobalVariable();
        this.locals = new LocalVariable();

        this.stack = new Primitive[STACK_MAX];
        this.sp = 0;
        this.ip = 0;
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
        String errorMessage = error.getErrorType();
        errorMessage += " | " + error.getMessage();
        if (error.getToken() != null) {
            errorMessage += ";\nOn Line " + error.getToken().getLine();
        }
        return errorMessage;
    }

    private void execute() {
        while (this.ip < this.instructions.size()) {
            Instruction instruction = this.instructions.get(this.ip);

            switch (instruction.getOpcode()) {
                case OP_CONSTANT, OP_NULL -> push(Parser.values.get((int) instruction.getOperand()));
                case OP_POP -> pop();
                case OP_PRINT -> System.out.println(pop());
            }

            this.ip++;
        }
    }

    private void runtimeError(String message) {
        Error error = new Error("Runtime Error", message, null);
        System.out.println(reportError(error));
        System.exit(1);
    }

    private void push(Primitive value) {
        this.stack[this.sp] = value;
        this.sp++;
    }

    private Primitive pop() {
        this.sp--;
        return this.stack[this.sp];
    }

    // Stack Debugger (Prints Out The Stack)
    private void debugStack(int till) {
        for (int i = 0; i <= till; i++) {
            System.out.print(this.stack[i] + "  |  ");
        }
        System.out.println();
    }
}
