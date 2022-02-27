package temp.ast;

public class Grouping extends Expression {
    private final Expression expression;

    public Grouping(Expression expression) {
        this.expression = expression;
    }
}
