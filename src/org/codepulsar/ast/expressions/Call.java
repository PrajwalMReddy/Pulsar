package org.codepulsar.ast.expressions;

import org.codepulsar.ast.Expression;
import org.codepulsar.lang.Token;

import java.util.ArrayList;

public class Call extends Expression {
    private final Token name;
    private final ArrayList<Expression> arguments;

    private final int line;

    public Call(Token name, ArrayList<Expression> arguments) {
        this.name = name;
        this.arguments = arguments;

        this.line = name.getLine();
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitCallExpression(this);
    }

    public Token getName() {
        return this.name;
    }

    public ArrayList<Expression> getArguments() {
        return this.arguments;
    }

    public int getLine() {
        return this.line;
    }
}
