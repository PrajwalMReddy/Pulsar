package temp.ast.expression;

import temp.ast.Expression;
import temp.lang.Token;

public class Variable extends Expression {
    Token name;

    public Variable(Token name) {
        this.name = name;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitVariableExpression(this);
    }

    public String getName() {
        return this.name.getLiteral();
    }
}
