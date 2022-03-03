package temp.pulsar;

import temp.ast.Expression;
import temp.ast.expression.*;
import temp.lang.CompilerError;
import temp.lang.Instruction;
import temp.util.ASTPrinter;

import java.util.ArrayList;

public class ByteCodeCompiler implements Expression.Visitor<Void> {
    // Input Data
    private final String sourceCode;
    private Expression program; // TODO Also Change This Back To 'AST'

    // Output Data
    private final ArrayList<Instruction> instructions;
    private CompilerError errors;

    public ByteCodeCompiler(String sourceCode) {
        this.sourceCode = sourceCode;

        this.instructions = new ArrayList<>();
    }

    public ArrayList<Instruction> compileByteCode() {
        Parser ast = new Parser(this.sourceCode);
        this.program = ast.parse();
        this.errors = ast.getErrors();
        
        new ASTPrinter().print(this.program);
        if (this.errors.hasError()) return instructions;
        
        compile();
        
        return this.instructions;
    }

    private void compile() {
        this.program.accept(this);
    }

    public Void visitAssignmentExpression(Assignment expression) {
        return null;
    }

    public Void visitBinaryExpression(Binary expression) {
        return null;
    }

    public Void visitGroupingExpression(Grouping expression) {
        return null;
    }

    public Void visitLiteralExpression(Literal expression) {
        return null;
    }

    public Void visitLogicalExpression(Logical expression) {
        return null;
    }

    public Void visitOpAssignmentExpression(OpAssignment expression) {
        return null;
    }

    public Void visitUnaryExpression(Unary expression) {
        return null;
    }

    public Void visitVariableExpression(Variable expression) {
        return null;
    }

    public CompilerError getErrors() {
        return this.errors;
    }
}
