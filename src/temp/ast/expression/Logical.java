package temp.ast.expression;

import temp.ast.Expression;
import temp.lang.Token;
import temp.lang.Visitor;

public class Logical extends Expression {
    private final Expression left;
    private final Token operator;
    private final Expression right;

    public Logical(Expression left, Token operator, Expression right) {
        this.left = left;
        this.operator = operator;
        this.right = right;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitLogicalExpression(this);
    }
}
