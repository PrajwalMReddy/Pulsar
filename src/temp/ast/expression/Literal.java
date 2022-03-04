package temp.ast.expression;

import temp.ast.Expression;

public class Literal extends Expression {
    private final Object value;

    private final int line;

    public Literal(Object value, int line) {
        this.value = value;
        this.line = line;
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

    public int getLine() {
        return this.line;
    }
}
