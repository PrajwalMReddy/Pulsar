package temp.lang;

/*
    The Static Analysis Class

    This class does all the static analysis that is need to ensure that the source code is correct and safe.
    This class may be expanded in the future or more related classes may be added,
        but for now the Analyzer checks to make sure that all Binary, Logical, and Unary
        operations have proper operands, as well as making sure that variables are initialized with a proper type.
*/

import temp.ast.Expression;
import temp.ast.Statement;
import temp.ast.expression.*;
import temp.ast.statement.*;

public class Analyzer implements Expression.Visitor<Void>, Statement.Visitor<Void> {
    private Statement program;

    public Analyzer(Statement program) {
        this.program = program;
    }

    public void analyze() {
        if (this.program == null) {
            return;
        }

        this.program.accept(this);
    }

    public Void visitAssignmentExpression(Assignment expression) {
        expression.getValue().accept(this);
        return null;
    }

    // TODO
    public Void visitBinaryExpression(Binary expression) {
        return null;
    }

    public Void visitGroupingExpression(Grouping expression) {
        expression.getExpression().accept(this);
        return null;
    }

    public Void visitLiteralExpression(Literal expression) {
        return null;
    }

    // TODO
    public Void visitLogicalExpression(Logical expression) {
        return null;
    }

    // TODO
    public Void visitUnaryExpression(Unary expression) {
        return null;
    }

    public Void visitVariableExpression(VariableAccess expression) {
        return null;
    }

    public Void visitBlockStatement(Block statements) {
        for (Statement statement: statements.getStatements()) {
            statement.accept(this);
        }

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

    // TODO
    public Void visitVariableStatement(Variable statement) {
        return null;
    }

    public Void visitWhileStatement(While statement) {
        statement.getCondition().accept(this);
        statement.getStatements().accept(this);

        return null;
    }
}
