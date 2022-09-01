#include "Interpreter.h"


Pulsar::Interpreter::Interpreter(std::string sourceCode) {
    this->sourceCode = sourceCode;
    this->stack = std::vector<Primitive*>(STACK_MAX);

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
            case OP_CONSTANT: push(this->values[std::any_cast<int>(instruction.getOperand())]); break;

            case OP_NEGATE: unaryOperation(OP_NEGATE); break;
            case OP_NOT: unaryOperation(OP_NOT); break;

            case OP_ADD: binaryOperation(OP_ADD); break;
            case OP_SUBTRACT: binaryOperation(OP_SUBTRACT); break;
            case OP_MULTIPLY: binaryOperation(OP_MULTIPLY); break;
            case OP_DIVIDE: binaryOperation(OP_DIVIDE); break;
            case OP_MODULO: binaryOperation(OP_MODULO); break;

            case OP_COMPARE_EQUAL: compareOperation(OP_COMPARE_EQUAL); break;
            case OP_COMPARE_GREATER: compareOperation(OP_COMPARE_GREATER); break;
            case OP_COMPARE_LESSER: compareOperation(OP_COMPARE_LESSER); break;

            case OP_NEW_GLOBAL: {
                auto newName = std::any_cast<Token>(instruction.getOperand()).literal;
                Primitive* newPrimitive = pop();
                this->symbolTable->reassignGlobalVariable(newName, newPrimitive);
                break;
            }
            case OP_LOAD_GLOBAL: loadGlobal(instruction); break;
            case OP_STORE_GLOBAL: {
                auto storeName = std::any_cast<std::string>(instruction.getOperand());
                Primitive* storePrimitive = pop();
                this->symbolTable->reassignGlobalVariable(storeName, storePrimitive);
                push(storePrimitive);
                break;
            }

            case OP_NEW_LOCAL: break;
            case OP_GET_LOCAL: push(this->stack[std::any_cast<int>(instruction.getOperand())]); break;
            case OP_SET_LOCAL: this->stack[std::any_cast<int>(instruction.getOperand())] = this->stack[this->sp - 1]; break;

            case OP_JUMP: this->ip = std::any_cast<int>(instruction.getOperand()) - 1; break;
            case OP_JUMP_IF_TRUE: conditionalJump(OP_JUMP_IF_TRUE, instruction); break;
            case OP_JUMP_IF_FALSE: conditionalJump(OP_JUMP_IF_FALSE, instruction); break;

            // TODO
            // case OP_LOAD_FUNCTION: break;
            // case OP_CALL: break;
            // case OP_RETURN: break;

            case OP_PRINT: std::cout << pop()->toString() << std::endl; break;
            case OP_POP: pop(); break;

            // Supposed To Be Unreachable
            default: runtimeError("Unhandled ByteCode Instruction: " + Disassembler::opcodeToString(instruction.getOpcode()));
        }

        this->ip++;
    }
}

void Pulsar::Interpreter::unaryOperation(ByteCode code) {
    Primitive* a = pop();

    if (code == OP_NEGATE) {
        push(a->unaryNegate());
    } else if (code == OP_NOT) {
        push(a->unaryNot());
    }
}

void Pulsar::Interpreter::binaryOperation(ByteCode code) {
    Primitive* b = pop();
    Primitive* a = pop();

    if (code == OP_ADD) {
        push(a->plus(b));
    } else if (code == OP_SUBTRACT) {
        push(a->minus(b));
    } else if (code == OP_MULTIPLY) {
        push(a->times(b));
    } else if (code == OP_DIVIDE) {
        push(a->div(b));
    } else if (code == OP_MODULO) {
        push(a->rem(b));
    }
}

void Pulsar::Interpreter::compareOperation(ByteCode code) {
    Primitive* b = pop();
    Primitive* a = pop();

    if (code == OP_COMPARE_EQUAL) {
        push(new PBoolean(a->toString() == b->toString()));
    } else if (code == OP_COMPARE_GREATER) {
        push(a->compareGreater(b));
    } else if (code == OP_COMPARE_LESSER) {
        push(a->compareLesser(b));
    }
}

void Pulsar::Interpreter::conditionalJump(ByteCode code, Instruction instruction) {
    Primitive* condition = pop();
    bool value = std::any_cast<bool>(condition->getPrimitiveValue());
    push(new PBoolean(value));

    if (code == OP_JUMP_IF_TRUE && value) {
        this->ip = std::any_cast<int>(instruction.getOperand()) - 1;
    } else if (code == OP_JUMP_IF_FALSE && !value) {
        this->ip = std::any_cast<int>(instruction.getOperand()) - 1;
    }
}

void Pulsar::Interpreter::loadGlobal(Instruction instruction) {
    auto variableName = std::any_cast<std::string>(instruction.getOperand());
    push(this->symbolTable->getGlobalValue(variableName));
}

void Pulsar::Interpreter::push(Primitive* value) {
    if (this->sp > STACK_MAX) runtimeError("A Stack Overflow Has Occurred");

    this->stack[this->sp] = value;
    this->sp++;
}

Pulsar::Primitive* Pulsar::Interpreter::pop() {
    if (this->sp <= 0) runtimeError("A Stack Underflow Has Occurred");

    this->sp--;
    return this->stack[this->sp];
}

void Pulsar::Interpreter::runtimeError(std::string message) {
    Error error = { "Runtime Error", message, -1 };
    std::cout << "\n" << error.getErrorType() << " | " << error.getMessage() << std::endl;
    exit(1);
}
