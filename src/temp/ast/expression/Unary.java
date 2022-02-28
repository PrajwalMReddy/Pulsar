package temp.ast.expression;

import temp.ast.Expression;
import temp.lang.Token;

public class Unary extends Expression {
    private final Token operator;
    private final Expression right;

    public Unary(Token operator, Expression right) {
        this.operator = operator;
        this.right = right;
    }

    public String toString() {
        return "(" + this.operator.getLiteral() + this.right + ")";
    }
}
