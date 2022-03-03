package temp.ast.expression;

import temp.ast.Expression;

public class Grouping extends Expression {
    private final Expression expression;

    public Grouping(Expression expression) {
        this.expression = expression;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitGroupingExpression(this);
    }

    public Expression getExpression() {
        return this.expression;
    }
}
