#include "ByteCodeCompiler.h"


Pulsar::ByteCodeCompiler::ByteCodeCompiler(std::string sourceCode) {
    this->sourceCode = sourceCode;

    this->values = std::vector<Value>();
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
    expression->getValue()->accept(*this);

    if (expression->isGlobalAssignment()) {
        return makeOpCode(OP_STORE_GLOBAL, expression->getIdentifier(), expression->getLine());
    } else {
        return makeOpCode(OP_SET_LOCAL, -1, expression->getLine()); // TODO Change -1
    }
}

std::any Pulsar::ByteCodeCompiler::visitBinaryExpression(Binary* expression) {
    expression->getLeft()->accept(*this);
    expression->getRight()->accept(*this);

    for (ByteCode op: identifyBinaryOperator(expression->getOperator())) {
        makeOpCode(op, expression->getLine());
    }

    return nullptr;
}

// TODO
std::any Pulsar::ByteCodeCompiler::visitCallExpression(Call* expression) {
}

std::any Pulsar::ByteCodeCompiler::visitGroupingExpression(Grouping* expression) {
    return expression->getExpression()->accept(*this);
}

std::any Pulsar::ByteCodeCompiler::visitLiteralExpression(Literal* expression) {
    std::string value = expression->getValue();
    return makeConstant(value, expression->getType(), expression->getLine());
}

std::any Pulsar::ByteCodeCompiler::visitLogicalExpression(Logical* expression) {
    expression->getLeft()->accept(*this);
    int line = expression->getLine();
    ByteCode jumpType;

    if (expression->getOperator() == "&&") { jumpType = OP_JUMP_IF_FALSE; }
    else if (expression->getOperator() == "||") { jumpType = OP_JUMP_IF_TRUE; }

    int offset = makeJump(jumpType, line);
    makeOpCode(OP_POP, line);

    expression->getRight()->accept(*this);
    fixJump(jumpType, offset);

    return nullptr;
}

std::any Pulsar::ByteCodeCompiler::visitUnaryExpression(Unary* expression) {
    expression->getExpression()->accept(*this);
    ByteCode op = identifyUnaryOperator(expression->getOperator());
    return makeOpCode(op, expression->getLine());
}

std::any Pulsar::ByteCodeCompiler::visitVariableExpression(VariableExpr* expression) {
    if (expression->isGlobalVariable()) {
        return makeOpCode(OP_LOAD_GLOBAL, expression->getName(), expression->getLine());
    } else {
        return makeOpCode(OP_GET_LOCAL, -1, expression->getLine()); // TODO Change -1
    }
}

std::any Pulsar::ByteCodeCompiler::visitBlockStatement(Block* statement) {
    for (Statement* stmt: *statement->getStatements()) {
        stmt->accept(*this);
    }

    return nullptr;
}

std::any Pulsar::ByteCodeCompiler::visitExpressionStatement(ExpressionStmt* statement) {
    statement->getExpression()->accept(*this);
    makeOpCode(OP_POP, statement->getLine());
    return nullptr;
}

// TODO
std::any Pulsar::ByteCodeCompiler::visitFunctionStatement(Function* statement) {
}

std::any Pulsar::ByteCodeCompiler::visitIfStatement(If* statement) {
    statement->getCondition()->accept(*this);
    int ifOffset = makeJump(OP_JUMP_IF_FALSE, statement->getLine());
    makeOpCode(OP_POP, statement->getLine());
    statement->getThenBranch()->accept(*this);

    int elseOffset = makeJump(OP_JUMP, statement->getThenBranch()->getLine());
    fixJump(OP_JUMP_IF_FALSE, ifOffset);
    makeOpCode(OP_POP, statement->getThenBranch()->getLine());

    if (statement->hasElse()) {
        statement->getElseBranch()->accept(*this);
    }

    fixJump(OP_JUMP, elseOffset);
    return nullptr;
}

std::any Pulsar::ByteCodeCompiler::visitPrintStatement(Print* statement) {
    statement->getExpression()->accept(*this);
    makeOpCode(OP_PRINT, statement->getLine());
    return nullptr;
}

std::any Pulsar::ByteCodeCompiler::visitReturnStatement(Return* statement) {
    if (statement->hasValue()) {
        statement->getValue()->accept(*this);
    }

    makeOpCode(OP_RETURN, statement->getLine());
    return nullptr;
}

std::any Pulsar::ByteCodeCompiler::visitVariableStatement(VariableDecl* statement) {
    statement->getInitializer()->accept(*this);

    if (statement->isGlobalVariable()) {
        return makeOpCode(OP_NEW_GLOBAL, statement->getName(), statement->getLine());
    } else {
        return makeOpCode(OP_NEW_LOCAL, statement->getName(), statement->getLine());
    }
}

std::any Pulsar::ByteCodeCompiler::visitWhileStatement(While* statement) {
    int start = this->instructions.size();
    statement->getCondition()->accept(*this);

    int offset = makeJump(OP_JUMP_IF_FALSE, statement->getLine());
    makeOpCode(OP_POP, statement->getLine());

    statement->getStatements()->accept(*this);
    makeOpCode(OP_JUMP, start, statement->getStatements()->getLine());

    fixJump(OP_JUMP_IF_FALSE, offset);
    makeOpCode(OP_POP, statement->getStatements()->getLine());

    return nullptr;
}

Pulsar::Instruction Pulsar::ByteCodeCompiler::makeConstant(std::string value, PrimitiveType type, int line) {
    if (type == PR_INTEGER) {
        this->values.emplace_back(Value(PInteger(std::stoi(value)), type));
    } else if (type == PR_DOUBLE) {
        this->values.emplace_back(Value(PDouble(std::stod(value)), type));
    } if (type == PR_CHARACTER) {
        this->values.emplace_back(Value(PCharacter(value[1]), type));
    } if (type == PR_BOOLEAN) {
        this->values.emplace_back(Value(PBoolean(value == "true"), type));
    }

    return makeOpCode(OP_CONSTANT, (int) (this->values.size() - 1), line);
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
    Instruction jumpOpCode = Instruction(opcode, (int) this->instructions.size(), line);
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

std::vector<Pulsar::Value> Pulsar::ByteCodeCompiler::getValues() {
    return this->values;
}

Pulsar::CompilerError* Pulsar::ByteCodeCompiler::getErrors() {
    return this->errors;
}
