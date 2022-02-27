package temp.ast;

import temp.lang.Token;

public class Assignment extends Expression {
    private final Token identifier;
    private final Expression value;

    public Assignment(Token identifier, Expression value) {
        this.identifier = identifier;
        this.value = value;
    }
}
