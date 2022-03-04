package temp.util;

import temp.ast.Expression;
import temp.ast.Statement;
import temp.ast.expression.*;
import temp.ast.statement.ExpressionStmt;
import temp.pulsar.Pulsar;

public class ASTPrinter implements Expression.Visitor<String>, Statement.Visitor<String> {
    public void print(ExpressionStmt ast) {
        if (Pulsar.conditions.getDebug()) {
            System.out.println("\n-- AST --\n");
            constructTree(ast);
        }
    }

    private void constructTree(ExpressionStmt ast) {
        System.out.println(ast.accept(this));
    }

    public String visitExpressionStatement(ExpressionStmt statement) {
        return statement.getExpression().accept(this);
    }

    public String visitAssignmentExpression(Assignment expression) {
        return "Assignment(Variable(" + expression.getIdentifier() + ") = " + expression.getValue().accept(this) + ")";
    }

    public String visitBinaryExpression(Binary expression) {
        return "Binary(" + expression.getLeft().accept(this) + " " + expression.getOperator() + " " + expression.getRight().accept(this) + ")";
    }

    public String visitGroupingExpression(Grouping expression) {
        return "(" + expression.getExpression().accept(this) + ")";
    }

    public String visitLiteralExpression(Literal expression) {
        return "Literal(" + expression.getValue() + ")";
    }

    public String visitLogicalExpression(Logical expression) {
        return "Logical(" + expression.getLeft().accept(this) + " " + expression.getOperator() + " " + expression.getRight().accept(this) + ")";
    }

    public String visitUnaryExpression(Unary expression) {
        return "Unary(" + expression.getOperator() + " " + expression.getRight().accept(this) + ")";
    }

    public String visitVariableExpression(Variable expression) {
        return "Variable(" + expression.getName() + ")";
    }
}
