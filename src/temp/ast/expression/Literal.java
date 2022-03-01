package temp.ast.expression;

import temp.ast.Expression;

public class Literal extends Expression {
    private final Object value;

    public Literal(Object value) {
        this.value = value;
    }

    public String toString() {
        return this.value.toString();
    }
}
