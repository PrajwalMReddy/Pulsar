package temp.ast.expression;

import temp.ast.Expression;

public class Unary extends Expression {
    private final String operator;
    private final Expression right;

    private final int line;

    public Unary(String operator, Expression right, int line) {
        this.operator = operator;
        this.right = right;
        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitUnaryExpression(this);
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
