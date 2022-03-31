package temp.util;

import temp.ast.Expression;
import temp.ast.Statement;
import temp.ast.expression.*;
import temp.ast.statement.*;
import temp.pulsar.Pulsar;

public class ASTPrinter implements Expression.Visitor<String>, Statement.Visitor<String> {
    public void print(Expression ast) {
        if (Pulsar.conditions.getDebug()) {
            System.out.println("\n-- AST --\n");
            constructTree(ast);
        }
    }

    private void constructTree(Expression ast) {
        if (ast == null) {
            System.out.println("No AST Has Been Generated");
        } else {
            System.out.println(ast.accept(this));
        }
    }

    public void print(Statement ast) {
        if (Pulsar.conditions.getDebug()) {
            System.out.println("\n-- AST --\n");
            constructTree(ast);
        }
    }

    private void constructTree(Statement ast) {
        if (ast == null) {
            System.out.println("No AST Has Been Generated");
        } else {
            System.out.println(ast.accept(this));
        }
    }

    public String visitVariableStatement(Variable statement) {
        return "Variable(" + (statement.isGlobal() ? "Global:" : "Local:") + statement.getName() + " = " + statement.getInitializer().accept(this) + ")";
    }

    public String visitBlockStatement(Block statement) {
        StringBuilder stringBuilder = new StringBuilder("Block(\n");
        for (Statement stmt: statement.getStatements()) {
            stringBuilder.append("\t").append(stmt.accept(this));
        }
        return stringBuilder.append("\n)").toString();
    }

    public String visitExpressionStatement(ExpressionStmt statement) {
        return "Expression(" + statement.getExpression().accept(this) + ")";
    }

    public String visitIFStatement(If statement) {
        String ifStmt = "If(" + statement.getCondition().accept(this) + ")\n\tThen(" + statement.getThenBranch().accept(this) + ")";
        if (statement.hasElse()) {
            ifStmt += "\n\tElse(" + statement.getElseBranch().accept(this) + ")";
        }

        return ifStmt;
    }

    public String visitWhileStatement(While statement) {
        String stmt = "While(" + statement.getCondition().accept(this) + ")";
        stmt += "\n\tDo(" + statement.getStatements().accept(this) + ")";

        return stmt;
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

    public String visitVariableExpression(VariableAccess expression) {
        return "Variable(" + expression.getName() + ")";
    }
}
