package temp.ast.expression;

import temp.ast.Expression;
import temp.lang.Token;
import temp.lang.Visitor;

public class Unary extends Expression {
    private final Token operator;
    private final Expression right;

    public Unary(Token operator, Expression right) {
        this.operator = operator;
        this.right = right;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitUnaryExpression(this);
    }
}
