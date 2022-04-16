package org.codepulsar.analysis;

/*
    The Validator Class

    This class makes sure that all code is correct.
    This includes catching all errors that haven't been caught elsewhere.
    This will be expanded on in the future.
*/

import org.codepulsar.ast.Expression;
import org.codepulsar.ast.Statement;
import org.codepulsar.ast.expression.*;
import org.codepulsar.ast.statement.*;
import org.codepulsar.lang.CompilerError;
import org.codepulsar.lang.LocalVariable;

public class Validator implements Expression.Visitor<Void>, Statement.Visitor<Void> {
    private final Statement program;
    private final LocalVariable locals;

    private final CompilerError errors;

    public Validator(Statement program, LocalVariable locals) {
        this.program = program;
        this.locals = locals;

        this.errors = new CompilerError();
    }

    public void validate() {
        if (this.program == null) {
            return;
        }

        this.program.accept(this);
    }

    public Void visitAssignmentExpression(Assignment expression) {
        LocalVariable.Local local = this.locals.getLocal(expression.getIdentifier());

        if (local.isConstant()) {
            newError("Local Variable '" + local.getName() + "' Is A Constant And Cannot Be Reassigned", expression.getLine());
        }

        expression.getValue().accept(this);
        return null;
    }

    public Void visitBinaryExpression(Binary expression) {
        expression.getLeft().accept(this);
        expression.getRight().accept(this);

        return null;
    }

    public Void visitGroupingExpression(Grouping expression) {
        expression.getExpression().accept(this);
        return null;
    }

    public Void visitLiteralExpression(Literal expression) {
        return null;
    }

    public Void visitLogicalExpression(Logical expression) {
        expression.getLeft().accept(this);
        expression.getRight().accept(this);

        return null;
    }

    public Void visitNoneExpression(NoneExpression expression) {
        return null;
    }

    public Void visitUnaryExpression(Unary expression) {
        expression.getRight().accept(this);
        return null;
    }

    public Void visitVariableExpression(VariableAccess expression) {
        LocalVariable.Local local = this.locals.getLocal(expression.getName());

        if (!local.isInitialized()) {
            newError("Variable '" + expression.getName() + "' Has Not Been Initialized", expression.getLine());
        }

        return null;
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
        statement.getCondition().accept(this);
        statement.getThenBranch().accept(this);

        if (statement.hasElse()) {
            statement.getElseBranch().accept(this);
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
        statement.getInitializer().accept(this);
        return null;
    }

    public Void visitWhileStatement(While statement) {
        statement.getCondition().accept(this);
        statement.getStatements().accept(this);

        return null;
    }

    private void newError(String message, int line) {
        // TODO Need Better Error Type Than 'Code Error'
        this.errors.addError("Code Error", message, line);
    }

    public CompilerError getErrors() {
        return this.errors;
    }
}
