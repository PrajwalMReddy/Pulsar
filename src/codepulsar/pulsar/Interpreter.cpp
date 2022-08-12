#include "Interpreter.h"


Pulsar::Interpreter::Interpreter(std::string sourceCode) {
    this->sourceCode = sourceCode;
    this->stack = std::vector<std::any>(STACK_MAX);

    this->sp = 0;
    this->ip = 0;
}

void Pulsar::Interpreter::interpret() {
    Pulsar::ByteCodeCompiler bcc = ByteCodeCompiler(this->sourceCode);
    this->instructions = bcc.compileByteCode();

    this->symbolTable = bcc.getSymbolTable();
    this->values = bcc.getValues();

    this->errors = bcc.getErrors();
    ErrorReporter::report(this->errors, this->sourceCode);

    Disassembler disassembler = Disassembler(this->instructions, this->symbolTable, this->values);
    disassembler.disassemble();

    execute();
}

void Pulsar::Interpreter::execute() {
    while (this->ip < this->instructions.size()) {
        Instruction instruction = this->instructions[this->ip];

        switch (instruction.getOpcode()) {
            case OP_CONSTANT:

            case OP_NEGATE:
            case OP_NOT:

            case OP_ADD:
            case OP_SUBTRACT:
            case OP_MULTIPLY:
            case OP_DIVIDE:
            case OP_MODULO:

            case OP_COMPARE_EQUAL:
            case OP_COMPARE_GREATER:
            case OP_COMPARE_LESSER:

            case OP_NEW_GLOBAL:
            case OP_STORE_GLOBAL:
            case OP_LOAD_GLOBAL:

            case OP_NEW_LOCAL:
            case OP_SET_LOCAL:
            case OP_GET_LOCAL:

            case OP_JUMP:
            case OP_JUMP_IF_TRUE:
            case OP_JUMP_IF_FALSE:

            case OP_LOAD_FUNCTION:
            case OP_CALL:
            case OP_RETURN:

            case OP_PRINT:
            case OP_POP:

            // Supposed To Be Unreachable
            default: runtimeError("Unhandled ByteCode Instruction: " + Disassembler::opcodeToString(instruction.getOpcode()));
        }

        this->ip++;
    }
}

void Pulsar::Interpreter::push(std::any value) {
    if (this->sp > STACK_MAX) runtimeError("A Stack Overflow Has Occurred");

    this->stack[this->sp] = value;
    this->sp++;
}

Pulsar::Value Pulsar::Interpreter::pop() {
    this->sp--;
    return std::any_cast<Value>(this->stack[this->sp]);
}

void Pulsar::Interpreter::runtimeError(std::string message) {
    Error error = { "Runtime Error", message, -1 };
    std::cout << "\n" << error.getErrorType() << " | " << error.getMessage() << std::endl;
    exit(1);
}
