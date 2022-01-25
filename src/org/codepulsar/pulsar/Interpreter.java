package org.codepulsar.pulsar;

import org.codepulsar.primitives.*;

import java.util.ArrayList;

import static org.codepulsar.pulsar.ByteCode.*;

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

        this.stack = new Primitive[STACK_MAX];
        this.sp = 0;
        this.ip = 0;
    }

    public void interpret() {
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
            execute();
        }
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

                case OP_CONSTANT -> push(Parser.values.get((int) instruction.getOperand()));
                case OP_NULL -> push(new PNull());

                case OP_NEW_GLOBAL -> {
                    String varName = instruction.getOperand().toString();
                    if (this.globals.containsKey(varName)) {
                        runtimeError("Redefinition Of Global Variable Is Not Allowed - " + varName);
                    }
                    this.globals.newVariable(varName, pop());
                }

                case OP_NEW_LOCAL -> {}

                // TODO Find And Handle Weird Edge Cases

                case OP_STORE_GLOBAL -> {
                    Primitive value = pop();
                    String varName = instruction.getOperand().toString();
                    if (!this.globals.containsKey(varName)) {
                        runtimeError("No Such Variable Named " + varName);
                    }
                    this.globals.reassignVariable(varName, value);
                    push(value);
                }

                case OP_SET_LOCAL -> {
                    int slot = (int) instruction.getOperand();
                    this.stack[slot] = this.stack[this.sp - 1];
                }

                case OP_LOAD_GLOBAL -> loadGlobal(instruction);

                case OP_GET_LOCAL -> {
                    int slot = (int) instruction.getOperand();
                    push(this.stack[slot]);
                }

                case OP_JUMP -> this.ip = ((int) instruction.getOperand()) - 1;
                case OP_JUMP_IF_TRUE -> conditionalJump(instruction, OP_JUMP_IF_TRUE);
                case OP_JUMP_IF_FALSE -> conditionalJump(instruction, OP_JUMP_IF_FALSE);

                case OP_PRINT -> System.out.println(pop());
                case OP_POP -> pop();

                default -> runtimeError("Unhandled ByteCode Instruction - " + instruction.getOpcode() +
                        "\nThis Is Not Your Fault And It Will Be Fixed Soon"); // Supposed To Be Unreachable
            }

            this.ip++;
        }
    }

    private void unaryOperation(ByteCode opcode) {
        if (opcode == OP_NOT) {
            Primitive value = pop();
            if (!(value instanceof PBoolean)) {
                runtimeError("Invalid Type For Unary Not - " + value.getClass());
            }
            boolean val = ((PBoolean) value).isValue();
            push(new PBoolean(!val));
        } else if (opcode == OP_NEGATE) {
            Primitive value = pop();
            if (value instanceof PDouble) {
                double val = ((PDouble) value).getValue();
                push(new PDouble(-val));
            } else if (value instanceof PInteger) {
                int val = ((PInteger) value).getValue();
                push(new PInteger(-val));
            } else {
                runtimeError("Invalid Type For Unary Negate - " + value.getClass());
            }
        }
    }

    private void binaryOperation(ByteCode opcode) {
        Primitive b = pop();
        Primitive a = pop();

        double newA = 0;
        double newB = 0;

        boolean isDouble = false;

        if (a instanceof PInteger) {
            newA = ((PInteger) a).getValue();
        } else if (a instanceof PDouble) {
            newA = ((PDouble) a).getValue();
            isDouble = true;
        } else {
            runtimeError("Invalid Type For A Binary Operation");
        }

        if (b instanceof PInteger) {
            newB = ((PInteger) b).getValue();
        } else if (b instanceof PDouble) {
            newB = ((PDouble) b).getValue();
            isDouble = true;
        } else {
            runtimeError("Invalid Type For A Binary Operation");
        }

        if (opcode == OP_ADD) {
            if (isDouble) {
                push(new PDouble(newA + newB));
            } else {
                push(new PInteger((int) (newA + newB)));
            }
        } else if (opcode == OP_DIVIDE) {
            if (newB == 0) {
                runtimeError("Division By Zero Error");
            }
            push(new PDouble(newA / newB));
        } else if (opcode == OP_MODULO) {
            if (isDouble) {
                push(new PDouble(newA % newB));
            } else {
                push(new PInteger((int) (newA % newB)));
            }
        } else if (opcode == OP_MULTIPLY) {
            if (isDouble) {
                push(new PDouble(newA * newB));
            } else {
                push(new PInteger((int) (newA * newB)));
            }
        } else if (opcode == OP_SUBTRACT) {
            if (isDouble) {
                push(new PDouble(newA - newB));
            } else {
                push(new PInteger((int) (newA - newB)));
            }
        }
    }

    private void compareOperation(ByteCode opcode) {
        Primitive b = pop();
        Primitive a = pop();

        double newA = 0;
        double newB = 0;

        boolean boolA = false;
        boolean boolB = false;

        boolean isBool = false;

        if (a instanceof PInteger) {
            newA = ((PInteger) a).getValue();
        } else if (a instanceof PDouble) {
            newA = ((PDouble) a).getValue();
        } else if (a instanceof PBoolean) {
            boolA = ((PBoolean) a).isValue();
            isBool = true;
        } else {
            runtimeError("Cannot Compare Null Values");
        }

        if (b instanceof PInteger) {
            newB = ((PInteger) b).getValue();
        } else if (b instanceof PDouble) {
            newB = ((PDouble) b).getValue();
        } else if (b instanceof PBoolean) {
            boolB = ((PBoolean) b).isValue();
            isBool = true;
        } else {
            runtimeError("Cannot Compare Null Values");
        }

        if (opcode == OP_COMPARE_EQUAL) {
            if (a.getClass() != b.getClass()) {
                push(new PBoolean(false));
            } else if (isBool) {
                push(new PBoolean(boolA == boolB));
            } else {
                push(new PBoolean(newA == newB));
            }
        } else if (opcode == OP_COMPARE_GREATER) {
            if (isBool) {
                runtimeError("Invalid Type For Inequality Comparison");
            } else {
                push(new PBoolean(newA > newB));
            }
        } else if (opcode == OP_COMPARE_LESSER) {
            if (isBool) {
                runtimeError("Invalid Type For Inequality Comparison");
            } else {
                push(new PBoolean(newA < newB));
            }
        }
    }

    private void conditionalJump(Instruction instruction, ByteCode opcode) {
        Primitive value = pop();
        push(value);

        if (!(value instanceof PBoolean)) {
            runtimeError("Invalid Control Flow Condition");
        }

        PBoolean newValue = (PBoolean) value;
        if (opcode == OP_JUMP_IF_TRUE) {
            if (newValue.isValue()) {
                this.ip = (int) instruction.getOperand();
            }
        } else if (opcode == OP_JUMP_IF_FALSE) {
            if (!newValue.isValue()) {
                this.ip = (int) instruction.getOperand();
            }
        }
    }

    private void loadGlobal(Instruction instruction) {
        String varName = instruction.getOperand().toString();

        if (!this.globals.containsKey(varName)) {
            runtimeError("No Such Variable Named " + varName);
        }

        Primitive value = this.globals.getValue(varName);

        if (value instanceof PInteger) {
            push(new PInteger(((PInteger) value).getValue()));
            return;
        } else if (value instanceof PDouble) {
            push(new PDouble(((PDouble) value).getValue()));
            return;
        } else if (value instanceof PBoolean) {
            push(new PBoolean(((PBoolean) value).isValue()));
            return;
        }

        push(value);
    }

    private void runtimeError(String message) {
        Error error = new Error("Runtime Error", message, null);
        System.out.println(reportError(error));
        System.exit(1);
    }

    private String reportError(Error error) {
        String errorMessage = error.getErrorType();
        errorMessage += " | " + error.getMessage();
        if (error.getToken() != null) {
            errorMessage += ";\nOn Line " + error.getToken().getLine();
        }
        return errorMessage;
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

    // Stack Debugger (Prints Out The Stack)
    private void debugStack(int till) {
        for (int i = 0; i < till; i++) {
            System.out.print(this.stack[i] + "  |  ");
        }
        System.out.println();
    }
}
