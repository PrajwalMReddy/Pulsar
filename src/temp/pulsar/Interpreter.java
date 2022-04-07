package temp.pulsar;

import org.codepulsar.pulsar.Error;
import org.codepulsar.pulsar.Parser;
import temp.lang.CompilerError;
import temp.lang.Instruction;
import temp.lang.LocalVariable;
import temp.primitives.Primitive;
import temp.util.Disassembler;
import temp.util.ErrorReporter;

import java.util.ArrayList;

public class Interpreter {
    // Input Data
    private final String sourceCode;
    private ArrayList<Instruction> instructions;

    // Data To Help In Interpreting
    private LocalVariable locals;
    private ArrayList<Primitive> values;

    // Output Data
    private CompilerError errors;
    private CompilerError staticErrors;

    // Other Necessary Data
    private final int STACK_MAX = 1024;
    private final Primitive[] stack;
    private int sp; // Stack Top
    private int ip; // Instruction Pointer

    public Interpreter(String sourceCode) {
        this.sourceCode = sourceCode;

        this.stack = new Primitive[STACK_MAX];
        this.sp = 0;
        this.ip = 0;
    }

    public void interpret() {
        ByteCodeCompiler bcc = new ByteCodeCompiler(this.sourceCode);
        this.instructions = bcc.compileByteCode();
        this.locals = bcc.getLocals();

        this.errors = bcc.getErrors();
        this.staticErrors = bcc.getStaticErrors();

        this.values = bcc.getValues();

        ErrorReporter.report(this.errors, this.sourceCode);
        ErrorReporter.report(this.staticErrors, this.sourceCode);

        Disassembler.disassemble(this.instructions, bcc);

        execute();
    }

    private void execute() {
        while (this.ip < this.instructions.size()) {
            Instruction instruction = this.instructions.get(this.ip);

            switch (instruction.getOpcode()) {
                case OP_NEGATE -> push(pop().negate());
                case OP_NOT -> push(pop().not());

                case OP_CONSTANT -> push(this.values.get((int) instruction.getOperand()));

                case OP_PRINT -> System.out.println(pop());
                case OP_POP -> pop();

                // Supposed To Be Unreachable
                default -> runtimeError("Unhandled ByteCode Instruction: " + instruction.getOpcode());
            }

            this.ip++;
        }
    }

    private void push(Primitive value) {
        if (this.sp >= STACK_MAX) {
            runtimeError("A Stack Overflow Has Occurred");
        }

        this.stack[this.sp] = value;
        this.sp++;
    }

    private Primitive pop() {
        this.sp--;
        return this.stack[this.sp];
    }

    private void runtimeError(String message) {
        Error error = new Error("Runtime Error", message, null);
        StringBuilder errorMessage = new StringBuilder();

        errorMessage.append("\n").append(error.getErrorType()).append(" | ").append(error.getMessage());
        System.out.println(errorMessage);

        System.exit(1);
    }
}
