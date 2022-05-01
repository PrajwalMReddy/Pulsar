package org.codepulsar.ast.statements;

import org.codepulsar.ast.Expression;
import org.codepulsar.ast.Statement;

public class Print extends Statement {
    private final Expression expression;

    private final int line;

    public Print(Expression expression, int line) {
        this.expression = expression;

        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitPrintExpression(this);
    }

    public Expression getExpression() {
        return this.expression;
    }

    public int getLine() {
        return this.line;
    }
}
