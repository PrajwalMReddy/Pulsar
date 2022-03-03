package temp.ast.expression;

import temp.ast.Expression;

public class Literal extends Expression {
    private final Object value;

    public Literal(Object value) {
        this.value = value;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitLiteralExpression(this);
    }

    public Object getValue() {
        if (this.value == null) {
            return "null";
        }

        return this.value;
    }
}
