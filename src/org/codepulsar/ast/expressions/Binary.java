package org.codepulsar.ast.expressions;

import org.codepulsar.ast.Expression;

public class Binary extends Expression {
    private final Expression left;
    private final String operator;
    private final Expression right;

    private final int line;

    public Binary(Expression left, String operator, Expression right, int line) {
        this.left = left;
        this.operator = operator;
        this.right = right;
        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitBinaryExpression(this);
    }

    public Expression getLeft() {
        return this.left;
    }

    public String getOperator() {
        return this.operator;
    }

    public Expression getRight() {
        return this.right;
    }

    public int getLine() {
        return this.line;
    }
}
