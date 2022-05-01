package org.codepulsar.ast.statements;

import org.codepulsar.ast.Expression;
import org.codepulsar.ast.Statement;
import org.codepulsar.primitives.PrimitiveType;

public class Variable extends Statement {
    private final String name;
    private final Expression initializer;

    private final PrimitiveType type;
    private final boolean isGlobal;
    private final boolean isInitiallyInitialized;

    private final int line;

    public Variable(String name, Expression initializer, PrimitiveType type, boolean isGlobal, boolean isInitiallyInitialized, int line) {
        this.name = name;
        this.initializer = initializer;

        this.type = type;
        this.isGlobal = isGlobal;
        this.isInitiallyInitialized = isInitiallyInitialized;

        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitVariableStatement(this);
    }

    public String getName() {
        return this.name;
    }

    public Expression getInitializer() {
        return this.initializer;
    }

    public PrimitiveType getType() {
        return this.type;
    }

    public boolean isGlobal() {
        return this.isGlobal;
    }

    public boolean isInitiallyInitialized() {
        return this.isInitiallyInitialized;
    }

    public int getLine() {
        return this.line;
    }
}
