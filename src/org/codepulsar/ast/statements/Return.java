package org.codepulsar.ast.statements;

import org.codepulsar.ast.Expression;
import org.codepulsar.ast.Statement;

public class Return extends Statement {
    private boolean hasExpression;
    private Expression expression;

    private int line;

    public Return(boolean hasExpression, Expression expression, int line) {
        this.hasExpression = hasExpression;
        this.expression = expression;

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

    public int getLine() {
        return this.line;
    }
}
