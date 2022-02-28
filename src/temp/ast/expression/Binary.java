package temp.ast.expression;

import temp.ast.Expression;
import temp.lang.Token;

public class Binary extends Expression {
    private final Expression left;
    private final Token operator;
    private final Expression right;

    public Binary(Expression left, Token operator, Expression right) {
        this.left = left;
        this.operator = operator;
        this.right = right;
    }
}
