package temp.ast.expression;

import temp.ast.Expression;
import temp.lang.Visitor;

public class Grouping extends Expression {
    private final Expression expression;

    public Grouping(Expression expression) {
        this.expression = expression;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitGroupingExpression(this);
    }
}
