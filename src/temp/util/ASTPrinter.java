package temp.util;

import temp.ast.Expression;
import temp.ast.Statement;
import temp.ast.expression.*;
import temp.ast.statement.*;
import temp.pulsar.Pulsar;

public class ASTPrinter implements Expression.Visitor<String>, Statement.Visitor<String> {
    private int indentCount;

    public ASTPrinter() {
        this.indentCount = 0;
    }

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

    public String visitAssignmentExpression(Assignment expression) {
        return "Assignment(Variable(" + expression.getIdentifier() + ") = " + expression.getValue().accept(this) + ")";
    }

    public String visitBinaryExpression(Binary expression) {
        return "Binary(" + expression.getLeft().accept(this) + " " + expression.getOperator() + " " + expression.getRight().accept(this);
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

    public String visitNoneExpression(NoneExpression expression) {
        return "";
    }

    public String visitUnaryExpression(Unary expression) {
        return "Unary(" + expression.getOperator() + " " + expression.getRight().accept(this) + ")";
    }

    public String visitVariableExpression(VariableAccess expression) {
        return "Variable(" + expression.getName() + ")";
    }

    public String visitBlockStatement(Block statement) {
        StringBuilder stringBuilder = new StringBuilder();

        stringBuilder.append(giveTabs() + "Block(\n");
        stringBuilder.append(blockStatement(statement));
        stringBuilder.append("\n" + giveTabs() + ")");

        return stringBuilder.toString();
    }

    public String blockStatement(Block statement) {
        StringBuilder stringBuilder = new StringBuilder();
        incrementIndentCount();

        for (Statement stmt: statement.getStatements()) {
            stringBuilder.append(giveTabs() + stmt.accept(this));
        }

        decrementIndentCount();
        return stringBuilder.toString();
    }

    public String visitEndScopeStatement(EndScope statement) {
        return "";
    }

    public String visitExpressionStatement(ExpressionStmt statement) {
        return "Expression(" + statement.getExpression().accept(this) + ")\n";
    }

    public String visitIFStatement(If statement) {
        StringBuilder stringBuilder = new StringBuilder();

        stringBuilder.append("\n" + giveTabs() + "If(" + statement.getCondition().accept(this) + ") (\n");
        stringBuilder.append(blockStatement(statement.getThenBranch()) + "\n" + giveTabs() + ")");

        if (statement.hasElse()) {
            stringBuilder.append(" Else (\n");
            incrementIndentCount();

            stringBuilder.append(((statement.getElseBranch() instanceof If) ? giveTabs() : "") + statement.getElseBranch().accept(this) + "\n");

            decrementIndentCount();
            stringBuilder.append(giveTabs() + ")");
        }

        stringBuilder.append("\n");
        return stringBuilder.toString();
    }

    public String visitNoneStatement(NoneStatement statement) {
        return "";
    }

    public String visitPrintExpression(Print statement) {
        return "Print(" + statement.getExpression().accept(this) + ")\n";
    }

    public String visitVariableStatement(Variable statement) {
        return "Variable(" + (statement.isGlobal() ? "Global:" : "Local:") + statement.getName() + " = " + statement.getInitializer().accept(this) + ")\n";
    }

    public String visitWhileStatement(While statement) {
        StringBuilder stringBuilder = new StringBuilder();

        stringBuilder.append("\n" + giveTabs() + "While(" + statement.getCondition().accept(this) + ") (\n");
        stringBuilder.append(blockStatement(statement.getStatements()) + "\n" + giveTabs() + ")");

        return stringBuilder.toString();
    }

    public String giveTabs() {
        return "\t".repeat(this.indentCount);
    }

    public String giveTabs(int n) {
        return "\t".repeat(n);
    }

    public void incrementIndentCount() {
        this.indentCount++;
    }

    public void decrementIndentCount() {
        this.indentCount--;
    }
}
