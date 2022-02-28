package temp.ast.expression;

import temp.ast.Expression;

public class Grouping extends Expression {
    private final Expression expression;

    public Grouping(Expression expression) {
        this.expression = expression;
    }

    @Override
    public String toString() {
        return "(" + this.expression + ")";
    }
}
