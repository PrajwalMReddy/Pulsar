package org.codepulsar.util;

import org.codepulsar.ast.Expression;
import org.codepulsar.ast.Statement;
import org.codepulsar.ast.expressions.*;
import org.codepulsar.ast.statements.*;
import org.codepulsar.primitives.PrimitiveType;
import org.codepulsar.pulsar.Pulsar;

import java.util.ArrayList;
import java.util.HashMap;

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

    public String visitCallExpression(Call expression) {
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append("Call:" + expression.getName().getLiteral() + "(");

        for (Expression expression1: expression.getArguments()) {
            stringBuilder.append(expression1.accept(this) + ",");
        }

        String newString = stringBuilder.toString();
        newString = newString.substring(0, newString.length() - 1) + ")";
        return newString;
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

    public String visitFunctionStatement(Function statement) {
        StringBuilder stringBuilder = new StringBuilder();

        stringBuilder.append("\n" + giveTabs() + "Function:" + statement.getName() + "(" + parameters(statement.getParameters()) + ")(\n");
        stringBuilder.append(blockStatement(statement.getStatements()));

        stringBuilder.append("\n" + giveTabs() + ")");
        return stringBuilder.toString();
    }

    private String parameters(ArrayList<Function.Parameter> parameters) {
        if (parameters.size() == 0) { return ""; }

        StringBuilder stringBuilder = new StringBuilder();

        for (Function.Parameter parameter: parameters) {
            stringBuilder.append(parameter.getName() + ",");
        }

        String newString = stringBuilder.toString();
        return newString.substring(0, newString.length() - 1);
    }

    public String visitIfStatement(If statement) {
        StringBuilder stringBuilder = new StringBuilder();

        stringBuilder.append("\n" + giveTabs() + "If(" + statement.getCondition().accept(this) + ")(\n");
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

        stringBuilder.append("\n" + giveTabs() + "While(" + statement.getCondition().accept(this) + ")(\n");
        stringBuilder.append(blockStatement(statement.getStatements()) + "\n" + giveTabs() + ")");

        return stringBuilder.toString();
    }

    public String giveTabs() {
        return "\t".repeat(this.indentCount);
    }

    public void incrementIndentCount() {
        this.indentCount++;
    }

    public void decrementIndentCount() {
        this.indentCount--;
    }
}
