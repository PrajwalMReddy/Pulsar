package temp.pulsar;

import temp.ast.Expression;
import temp.ast.Statement;
import temp.ast.expression.*;
import temp.ast.statement.ExpressionStmt;
import temp.lang.ByteCode;
import temp.lang.CompilerError;
import temp.lang.Instruction;
import temp.util.ASTPrinter;

import java.util.ArrayList;

import static temp.lang.ByteCode.*;

public class ByteCodeCompiler implements Expression.Visitor<Instruction>, Statement.Visitor<Instruction> {
    // Input Data
    private final String sourceCode;
    private ExpressionStmt program;

    // Data To Help In Compiling To ByteCode
    private static ArrayList<Object> values; // Constant Values To Be Stored

    // Output Data
    private final ArrayList<Instruction> instructions;
    private CompilerError errors;

    public ByteCodeCompiler(String sourceCode) {
        this.sourceCode = sourceCode;

        values = new ArrayList<>();

        this.instructions = new ArrayList<>();
    }

    public ArrayList<Instruction> compileByteCode() {
        Parser ast = new Parser(this.sourceCode);
        this.program = ast.parse();
        this.errors = ast.getErrors();

        if (this.errors.hasError()) return instructions;
        new ASTPrinter().print(this.program);

        compile();
        
        return this.instructions;
    }

    private void compile() {
        this.program.accept(this);
    }

    public Instruction visitExpressionStatement(ExpressionStmt statement) {
        Instruction instruction = statement.getExpression().accept(this);
        makeOpCode(OP_POP, statement.getLine());

        return instruction;
    }

    public Instruction visitAssignmentExpression(Assignment expression) {
        return null;
    }

    public Instruction visitBinaryExpression(Binary expression) {
        expression.getLeft().accept(this);
        expression.getRight().accept(this);

        ArrayList<ByteCode> operators = identifyBinaryOperator(expression.getOperator());
        for (ByteCode op: operators) {
            makeOpCode(op, expression.getLine());
        }

        return null;
    }

    public Instruction visitGroupingExpression(Grouping expression) {
        return expression.getExpression().accept(this);
    }

    public Instruction visitLiteralExpression(Literal expression) {
        Object value = expression.getValue();
        return makeConstant(value, expression.getLine());
    }

    public Instruction visitLogicalExpression(Logical expression) {
        return null;
    }

    public Instruction visitUnaryExpression(Unary expression) {
        expression.getRight().accept(this);
        ByteCode operator = identifyUnaryOperator(expression.getOperator());
        return makeOpCode(operator, expression.getLine());
    }

    public Instruction visitVariableExpression(Variable expression) {
        return null;
    }

    private Instruction makeConstant(Object value, int line) {
        values.add(value);
        Instruction instruction = new Instruction(OP_CONSTANT, values.size() - 1, line);
        this.instructions.add(instruction);
        return instruction;
    }

    private Instruction makeOpCode(ByteCode opcode, int line) {
        Instruction instruction = new Instruction(opcode, null, line);
        this.instructions.add(instruction);
        return instruction;
    }

    private Instruction makeOpCode(ByteCode opcode, Object operand, int line) {
        Instruction instruction = new Instruction(opcode, operand, line);
        this.instructions.add(instruction);
        return instruction;
    }

    private ByteCode identifyUnaryOperator(String operator) {
        switch (operator) {
            case "-" -> { return OP_NEGATE; }
            case "!" -> { return OP_NOT; }

            // Unreachable
            default -> { return null; }
        }
    }

    private ArrayList<ByteCode> identifyBinaryOperator(String operator) {
        ArrayList<ByteCode> codes = new ArrayList<>();
        switch (operator) {
            case "+" -> codes.add(OP_ADD);
            case "-" -> codes.add(OP_SUBTRACT);
            case "*" -> codes.add(OP_MULTIPLY);
            case "/" -> codes.add(OP_DIVIDE);

            case ">" -> codes.add(OP_COMPARE_GREATER);
            case ">=" -> {
                codes.add(OP_COMPARE_LESSER);
                codes.add(OP_NOT);
            }

            case "<" -> codes.add(OP_COMPARE_LESSER);
            case "<=" -> {
                codes.add(OP_COMPARE_GREATER);
                codes.add(OP_NOT);
            }

            case "==" -> codes.add(OP_COMPARE_EQUAL);
            case "!=" -> {
                codes.add(OP_COMPARE_EQUAL);
                codes.add(OP_NOT);
            }
        }

        return codes;
    }

    public static ArrayList<Object> getValues() {
        return values;
    }

    public CompilerError getErrors() {
        return this.errors;
    }
}
