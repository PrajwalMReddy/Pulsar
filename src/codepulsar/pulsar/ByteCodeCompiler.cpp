#include "ByteCodeCompiler.h"


Pulsar::ByteCodeCompiler::ByteCodeCompiler(std::string sourceCode) {
    this->sourceCode = sourceCode;

    this->values = std::vector<std::any>();
    this->instructions = std::vector<Instruction>();
}

std::vector<Pulsar::Instruction> Pulsar::ByteCodeCompiler::compileByteCode() {
    Pulsar::Parser parser = Parser(this->sourceCode);
    this->program = parser.parse();
    this->symbolTable = parser.getSymbolTable();

    this->errors = parser.getErrors();
    if (this->errors->hasError()) return this->instructions;

    ASTPrinter astPrinter = ASTPrinter();
    astPrinter.print(this->program);

    Validator validator = Validator(this->program, this->symbolTable, this->errors);
    validator.validate();
    if (this->errors->hasError()) return this->instructions;

    TypeChecker checker = TypeChecker(this->program, this->symbolTable, this->errors);
    checker.check();
    if (this->errors->hasError()) return this->instructions;

    compile();
    return this->instructions;
}

void Pulsar::ByteCodeCompiler::compile() {
    if (this->program == nullptr) return;
    this->program->accept(*this);
}

std::any Pulsar::ByteCodeCompiler::visitAssignmentExpression(Assignment* expression) {
}

std::any Pulsar::ByteCodeCompiler::visitBinaryExpression(Binary* expression) {
}

std::any Pulsar::ByteCodeCompiler::visitCallExpression(Call* expression) {
}

std::any Pulsar::ByteCodeCompiler::visitGroupingExpression(Grouping* expression) {
}

std::any Pulsar::ByteCodeCompiler::visitLiteralExpression(Literal* expression) {
}

std::any Pulsar::ByteCodeCompiler::visitLogicalExpression(Logical* expression) {
}

std::any Pulsar::ByteCodeCompiler::visitUnaryExpression(Unary* expression) {
}

std::any Pulsar::ByteCodeCompiler::visitVariableExpression(VariableExpr* expression) {
}

std::any Pulsar::ByteCodeCompiler::visitBlockStatement(Block* statement) {
}

std::any Pulsar::ByteCodeCompiler::visitExpressionStatement(ExpressionStmt* statement) {
}

std::any Pulsar::ByteCodeCompiler::visitFunctionStatement(Function* statement) {
}

std::any Pulsar::ByteCodeCompiler::visitIfStatement(If* statement) {
}

std::any Pulsar::ByteCodeCompiler::visitPrintStatement(Print* statement) {
}

std::any Pulsar::ByteCodeCompiler::visitReturnStatement(Return* statement) {
}

std::any Pulsar::ByteCodeCompiler::visitVariableStatement(VariableDecl* statement) {
}

std::any Pulsar::ByteCodeCompiler::visitWhileStatement(While* statement) {
}

Pulsar::Instruction Pulsar::ByteCodeCompiler::makeConstant(std::string value, PrimitiveType type, int line) {
    if (type == PR_INTEGER) {
        this->values.emplace_back(PInteger(std::stoi(value)));
    } else if (type == PR_DOUBLE) {
        this->values.emplace_back(PDouble(std::stod(value)));
    } if (type == PR_CHARACTER) {
        this->values.emplace_back(PCharacter(value[1]));
    } if (type == PR_BOOLEAN) {
        this->values.emplace_back(PBoolean(value == "true" ? true : false));
    }

    return makeOpCode(OP_CONSTANT, this->values.size() - 1, line);
}

Pulsar::Instruction Pulsar::ByteCodeCompiler::makeOpCode(ByteCode opcode, int line) {
    return makeOpCode(opcode, nullptr, line);
}

Pulsar::Instruction Pulsar::ByteCodeCompiler::makeOpCode(ByteCode opcode, std::any operand, int line) {
    Instruction instruction = Instruction(opcode, operand, line);
    this->instructions.push_back(instruction);
    return instruction;
}

int Pulsar::ByteCodeCompiler::makeJump(ByteCode opcode, int line) {
    int size = this->instructions.size();
    makeOpCode(opcode, line);
    return size;
}

void Pulsar::ByteCodeCompiler::fixJump(ByteCode opcode, int offset) {
    Instruction oldJump = this->instructions[offset];
    int line = oldJump.getLine();
    Instruction jumpOpCode = Instruction(opcode, this->instructions.size(), line);
    this->instructions.at(offset) = jumpOpCode;
}

Pulsar::ByteCode Pulsar::ByteCodeCompiler::identifyUnaryOperator(std::string oper) {
    if (oper == "-") { return OP_NEGATE; }
    else if (oper == "!") { return OP_NOT; }
}

std::vector<Pulsar::ByteCode> Pulsar::ByteCodeCompiler::identifyBinaryOperator(std::string oper) {
    std::vector<ByteCode> codes = std::vector<ByteCode>();

    if (oper == "+") { codes.push_back(OP_ADD); }
    else if (oper == "-") { codes.push_back(OP_SUBTRACT); }
    else if (oper == "*") { codes.push_back(OP_MULTIPLY); }
    else if (oper == "/") { codes.push_back(OP_DIVIDE); }
    else if (oper == "%") { codes.push_back(OP_MODULO); }

    else if (oper == ">") { codes.push_back(OP_COMPARE_GREATER); }
    else if (oper == ">=") {
        codes.push_back(OP_COMPARE_LESSER);
        codes.push_back(OP_NOT);
    }

    else if (oper == "<") { codes.push_back(OP_COMPARE_LESSER); }
    else if (oper == "<=") {
        codes.push_back(OP_COMPARE_GREATER);
        codes.push_back(OP_NOT);
    }

    else if (oper == "==") { codes.push_back(OP_COMPARE_EQUAL); }
    else if (oper == "!=") {
        codes.push_back(OP_COMPARE_EQUAL);
        codes.push_back(OP_NOT);
    }

    return codes;
}

Pulsar::SymbolTable* Pulsar::ByteCodeCompiler::getSymbolTable() {
    return this->symbolTable;
}

Pulsar::CompilerError* Pulsar::ByteCodeCompiler::getErrors() {
    return this->errors;
}
