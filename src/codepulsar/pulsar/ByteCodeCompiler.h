#ifndef CODEPULSAR_BYTECODECOMPILER_H
#define CODEPULSAR_BYTECODECOMPILER_H

#include <string>

#include "Parser.h"
#include "../util/ErrorReporter.h"
#include "../util/ASTPrinter.h"
#include "../analysis/TypeChecker.h"
#include "../analysis/Validator.h"
#include "../variable/SymbolTable.h"
#include "../lang/Instruction.h"
#include "../primitive/Primitive.h"
#include "../primitive/type/PInteger.h"
#include "../primitive/type/PDouble.h"
#include "../primitive/type/PCharacter.h"
#include "../primitive/type/PBoolean.h"


namespace Pulsar {
    class ByteCodeCompiler: public ExprVisitor, public StmtVisitor {
        public:
            ByteCodeCompiler(std::string sourceCode);

            std::vector<Instruction> compileByteCode();
            SymbolTable* getSymbolTable();
            std::vector<Primitive*> getValues();
            CompilerError* getErrors();

            // Expression AST Visitors
            std::any visitAssignmentExpression(Assignment* expression) override;
            std::any visitBinaryExpression(Binary* expression) override;
            std::any visitCallExpression(Call* expression) override;
            std::any visitGroupingExpression(Grouping* expression) override;
            std::any visitLiteralExpression(Literal* expression) override;
            std::any visitLogicalExpression(Logical* expression) override;
            std::any visitUnaryExpression(Unary* expression) override;
            std::any visitVariableExpression(VariableExpr* expression) override;

            // Statement AST Visitors
            std::any visitBlockStatement(Block* statement) override;
            std::any visitExpressionStatement(ExpressionStmt* statement) override;
            std::any visitFunctionStatement(Function* statement) override;
            std::any visitIfStatement(If* statement) override;
            std::any visitNoneStatement(NoneStmt* statement) override;
            std::any visitPrintStatement(Print* statement) override;
            std::any visitProgramStatement(Program* statement) override;
            std::any visitReturnStatement(Return* statement) override;
            std::any visitVariableStatement(VariableDecl* statement) override;
            std::any visitWhileStatement(While* statement) override;

        private:
            // Input Data
            std::string sourceCode;
            Statement* program;
            SymbolTable* symbolTable;

            // Processing Data
            std::vector<Primitive*> values;

            // Output Data
            std::vector<Instruction> currentChunk;
            CompilerError* errors;

            // Core Functions
            void compile();
            Instruction makeConstant(std::string value, PrimitiveType type, int line);
            Instruction makeOpCode(ByteCode opcode, int line);
            Instruction makeOpCode(ByteCode opcode, std::any operand, int line);

            int makeJump(ByteCode opcode, int line);
            void fixJump(ByteCode opcode, int offset);
            ByteCode identifyUnaryOperator(std::string oper);
            std::vector<ByteCode> identifyBinaryOperator(std::string oper);
    };
}


#endif
