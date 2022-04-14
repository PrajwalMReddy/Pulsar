package temp.pulsar;

import org.codepulsar.pulsar.Error;
import temp.lang.*;
import temp.primitives.Primitive;
import temp.primitives.types.PBoolean;
import temp.primitives.types.PNull;
import temp.util.Disassembler;
import temp.util.ErrorReporter;

import java.util.ArrayList;

import static temp.lang.ByteCode.*;
import static temp.primitives.PrimitiveType.*;

public class Interpreter {
    // Input Data
    private final String sourceCode;
    private ArrayList<Instruction> instructions;

    // Data To Help In Interpreting
    private GlobalVariable globals;
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

        this.globals = bcc.getGlobals();
        this.locals = bcc.getLocals();

        this.errors = bcc.getErrors();
        this.staticErrors = bcc.getStaticErrors();

        this.values = bcc.getValues();

        ErrorReporter.report(this.errors, this.sourceCode);
        ErrorReporter.report(this.staticErrors, this.sourceCode);

        Disassembler.disassemble(this.instructions, bcc);

        System.out.println();
        execute();
    }

    private void execute() {
        while (this.ip < this.instructions.size()) {
            Instruction instruction = this.instructions.get(this.ip);

            switch (instruction.getOpcode()) {
                case OP_NEGATE -> unaryOperation(OP_NEGATE);
                case OP_NOT -> unaryOperation(OP_NOT);

                case OP_ADD -> binaryOperation(OP_ADD);
                case OP_SUBTRACT -> binaryOperation(OP_SUBTRACT);
                case OP_MULTIPLY -> binaryOperation(OP_MULTIPLY);
                case OP_DIVIDE -> binaryOperation(OP_DIVIDE);
                case OP_MODULO -> binaryOperation(OP_MODULO);

                case OP_COMPARE_EQUAL -> compareOperation(OP_COMPARE_EQUAL);
                case OP_COMPARE_GREATER -> compareOperation(OP_COMPARE_GREATER);
                case OP_COMPARE_LESSER -> compareOperation(OP_COMPARE_LESSER);

                case OP_CONSTANT -> push(this.values.get((int) instruction.getOperand()));
                case OP_NULL -> push(new PNull());

                case OP_NEW_GLOBAL -> {
                    String variableName = instruction.getOperand().toString();
                    if (this.globals.containsVariable(variableName)) {
                        runtimeError("Global Variable '" + variableName + "' Already Exists");
                    }

                    Primitive primitive = pop();
                    // TODO Come Back To This Later While Improving Globals
                    this.globals.addVariable(variableName, primitive, primitive.getPrimitiveType(), true, false);
                }
                case OP_LOAD_GLOBAL -> loadGlobal(instruction);
                case OP_STORE_GLOBAL -> {
                    Primitive value = pop();
                    String variableName = instruction.getOperand().toString();

                    if (!this.globals.containsVariable(variableName)) {
                        runtimeError("There Is No Global Variable Named '" + variableName + "'");
                    }

                    this.globals.reassignVariable(variableName, value);
                    push(value);
                }

                case OP_NEW_LOCAL -> {}
                case OP_GET_LOCAL -> {
                    int slot = (int) instruction.getOperand();
                    push(this.stack[slot]);
                }
                case OP_SET_LOCAL -> {
                    int slot = (int) instruction.getOperand();
                    this.stack[slot] = this.stack[this.sp - 1];
                }

                case OP_JUMP -> this.ip = (int) instruction.getOperand() - 1;
                case OP_JUMP_IF_TRUE -> conditionalJump(instruction, OP_JUMP_IF_TRUE);
                case OP_JUMP_IF_FALSE -> conditionalJump(instruction, OP_JUMP_IF_FALSE);

                case OP_PRINT -> System.out.println(pop());
                case OP_POP -> pop();

                // Supposed To Be Unreachable
                default -> runtimeError("Unhandled ByteCode Instruction: " + instruction.getOpcode());
            }

            this.ip++;
        }
    }

    private void unaryOperation(ByteCode code) {
        Primitive a = pop();

        if (a.isPrimitiveType(PR_NULL)) {
            runtimeError("Cannot Use Unary Operations On Null Values");
        }

        if (code == OP_NEGATE) {
            push(a.negate());
        } else if (code == OP_NOT) {
            push(a.not());
        }
    }

    private void binaryOperation(ByteCode code) {
        Primitive b = pop();
        Primitive a = pop();

        if (a.isPrimitiveType(PR_NULL) || b.isPrimitiveType(PR_NULL)) {
            runtimeError("Cannot Use Binary Operations On Null Values");
        }

        if (code == OP_ADD) {
            push(a.plus(b));
        } else if (code == OP_SUBTRACT) {
            push(a.minus(b));
        } else if (code == OP_MULTIPLY) {
            push(a.times(b));
        } else if (code == OP_DIVIDE) {
            push(a.div(b));
        } else if (code == OP_MODULO) {
            push(a.rem(b));
        }
    }

    private void compareOperation(ByteCode code) {
        Primitive b = pop();
        Primitive a = pop();

        if (code == OP_COMPARE_EQUAL) {
            push(new PBoolean(a.getPrimitiveValue() == b.getPrimitiveValue()));
        } else if (a.isPrimitiveType(PR_NULL) || b.isPrimitiveType(PR_NULL)) {
            runtimeError("Cannot Use Binary Operations On Null Values");
        } else if (code == OP_COMPARE_GREATER) {
            push(a.compareGreater(b));
        } else if (code == OP_COMPARE_LESSER) {
            push(a.compareLesser(b));
        }
    }

    private void conditionalJump(Instruction instruction, ByteCode code) {
        Primitive condition = pop();
        boolean value = false;

        if (condition.isPrimitiveType(PR_NULL)) {
            runtimeError("Cannot Use Null Values For Control Flow Conditions");
        } else {
            value = ((PBoolean) pop()).getValue();
        }

        push(new PBoolean(value));

        if (code == OP_JUMP_IF_TRUE && value) {
            this.ip = (int) instruction.getOperand() - 1;
        } else if (code == OP_JUMP_IF_FALSE && !value) {
            this.ip = (int) instruction.getOperand() - 1;
        }
    }

    private void loadGlobal(Instruction instruction) {
        String variableName = instruction.getOperand().toString();
        if (!this.globals.containsVariable(variableName)) {
            runtimeError("Global Variable '" + variableName + "' Does Not Exist");
        }

        push(this.globals.getValue(variableName));
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
