package temp.ast.expression;

import temp.ast.Expression;
import temp.lang.TokenType;

public class Literal extends Expression {
    private final String value;
    private final TokenType type;

    private final int line;

    public Literal(String value, TokenType type, int line) {
        this.value = value;
        this.type = type;
        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitLiteralExpression(this);
    }

    public String getValue() {
        if (this.value == null) {
            return "null";
        }

        return this.value;
    }

    public int getLine() {
        return this.line;
    }

    public TokenType getType() {
        return this.type;
    }
}
