package temp.ast.expression;

import temp.ast.Expression;

/*
    Indicates nothing should be done. This can be used if a return statement is needed, but an error occurred.
*/

public class None extends Expression {
    public None() {
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitNoneExpression(this);
    }
}
