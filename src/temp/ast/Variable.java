package temp.ast;

import temp.lang.Token;

public class Variable extends Expression {
    Token name;

    public Variable(Token name) {
        this.name = name;
    }
}
