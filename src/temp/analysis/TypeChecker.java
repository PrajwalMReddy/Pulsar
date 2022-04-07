package temp.analysis;

/*
    The Type Checker Class

    This class does all the type checking that is need to ensure that the source code is correct and safe.
    The Checker checks to make sure that all Binary, Logical, and Unary
        operations have proper operators for their operands, as well as making sure that
        variables are initialized according to their type.
*/

import temp.ast.Expression;
import temp.ast.Statement;
import temp.ast.expression.*;
import temp.ast.statement.*;
import temp.lang.CompilerError;
import temp.lang.LocalVariable;
import temp.primitives.PrimitiveType;

import static temp.primitives.PrimitiveType.*;

public class TypeChecker implements Expression.Visitor<PrimitiveType>, Statement.Visitor<Void> {
    private final Statement program;
    private final LocalVariable locals;

    private final CompilerError errors;

    public TypeChecker(Statement program, LocalVariable locals) {
        this.program = program;
        this.locals = locals;

        this.errors = new CompilerError();
    }

    public void check() {
        if (this.program == null) {
            return;
        }

        this.program.accept(this);
    }

    public PrimitiveType visitAssignmentExpression(Assignment expression) {
        LocalVariable.Local local = this.locals.getLocal(expression.getIdentifier());

        if (local.getType() != expression.getValue().accept(this)) {
            newError("Variable Is Being Assigned To The Wrong Type", expression.getLine());
        }

        return local.getType();
    }

    public PrimitiveType visitBinaryExpression(Binary expression) {
        PrimitiveType a = expression.getLeft().accept(this);
        PrimitiveType b = expression.getRight().accept(this);

        if (isOfType(a, PR_BOOLEAN) || isOfType(b, PR_BOOLEAN)) {
            if (!isOperation(expression.getOperator(), "==", "!=")) {
                newError("Boolean Operands May Not Be Used For This Operation Operations", expression.getLine());
                return PR_ERROR;
            }
        } else if (a != b) {
            newError("Binary Operation Operands Are Of Different Types", expression.getLine());
            return PR_ERROR;
        }

        return a;
    }

    public PrimitiveType visitGroupingExpression(Grouping expression) {
        return expression.getExpression().accept(this);
    }

    public PrimitiveType visitLiteralExpression(Literal expression) {
        return expression.getType();
    }

    public PrimitiveType visitLogicalExpression(Logical expression) {
        PrimitiveType a = expression.getLeft().accept(this);
        PrimitiveType b = expression.getRight().accept(this);

        if (!isOfType(a, PR_BOOLEAN) || !isOfType(b, PR_BOOLEAN)) {
            newError("Logical Operation Has Non Boolean Operand(s)", expression.getLine());
            return PR_ERROR;
        }

        return PR_BOOLEAN;
    }

    public PrimitiveType visitNoneExpression(NoneExpression expression) {
        return PR_ERROR;
    }

    public PrimitiveType visitUnaryExpression(Unary expression) {
        PrimitiveType a = expression.getRight().accept(this);

        if (isOperation(expression.getOperator(), "!")) {
            if (!isOfType(a, PR_BOOLEAN)) {
                newError("Unary Not Operation Has Non Boolean Operand", expression.getLine());
                return PR_ERROR;
            }
        } else if (isOperation(expression.getOperator(), "-")) {
            if (isOfType(a, PR_BOOLEAN)) {
                newError("Unary Negation Has A Boolean Operand", expression.getLine());
            }
        }

        return a;
    }

    public PrimitiveType visitVariableExpression(VariableAccess expression) {
        LocalVariable.Local local = this.locals.getLocal(expression.getName());
        return local.getType();
    }

    public Void visitBlockStatement(Block statements) {
        for (Statement statement: statements.getStatements()) {
            statement.accept(this);
        }

        return null;
    }

    public Void visitEndScopeStatement(EndScope statement) {
        return null;
    }

    public Void visitExpressionStatement(ExpressionStmt statement) {
        statement.getExpression().accept(this);
        return null;
    }

    public Void visitIFStatement(If statement) {
        PrimitiveType type = statement.getCondition().accept(this);
        statement.getThenBranch().accept(this);

        if (statement.hasElse()) {
            statement.getElseBranch().accept(this);
        }

        if (type != PR_BOOLEAN) {
            newError("If Statement Has Non Boolean Condition", statement.getLine());
        }

        return null;
    }

    public Void visitNoneStatement(NoneStatement statement) {
        return null;
    }

    public Void visitPrintExpression(Print statement) {
        statement.getExpression().accept(this);

        return null;
    }

    public Void visitVariableStatement(Variable statement) {
        PrimitiveType variableType = statement.getType();
        PrimitiveType initializerType = statement.getInitializer().accept(this);

        if ((variableType != initializerType) && (initializerType != PR_NULL)) {
            newError("Variable Has Been Initialized With The Wrong Type", statement.getLine());
        }

        return null;
    }

    public Void visitWhileStatement(While statement) {
        PrimitiveType type = statement.getCondition().accept(this);
        statement.getStatements().accept(this);

        if (type != PR_BOOLEAN) {
            newError("While Statement Has Non Boolean Condition", statement.getLine());
        }

        return null;
    }

    private boolean isOfType(PrimitiveType toCompare, PrimitiveType... types) {
        for (PrimitiveType type: types) {
            if (toCompare == type) {
                return true;
            }
        }

        return false;
    }

    private boolean isOperation(String toCompare, String... operations) {
        for (String operation: operations) {
            if (toCompare.equals(operation)) {
                return true;
            }
        }

        return false;
    }

    public void newError(String message, int line) {
        this.errors.addError("Type Error", message, line);
    }

    public CompilerError getErrors() {
        return this.errors;
    }
}
