package org.codepulsar.ast.statements;

import org.codepulsar.ast.Expression;
import org.codepulsar.ast.Statement;

public class Return extends Statement {
    private final boolean hasExpression;
    private final Expression expression;

    private final String function;
    private final int line;

    public Return(boolean hasExpression, Expression expression, String function, int line) {
        this.hasExpression = hasExpression;
        this.expression = expression;
        this.function = function;

        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitReturnStatement(this);
    }

    public boolean hasExpression() {
        return this.hasExpression;
    }

    public Expression getExpression() {
        return this.expression;
    }

    public String getFunction() {
        return this.function;
    }

    public int getLine() {
        return this.line;
    }
}
