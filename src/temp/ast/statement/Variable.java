package temp.ast.statement;

import temp.ast.Expression;
import temp.ast.Statement;
import temp.primitives.PrimitiveType;

public class Variable extends Statement {
    private final String name;
    private final Expression initializer;

    private final PrimitiveType type;
    private final boolean isGlobal;

    private final int line;

    public Variable(String name, Expression initializer, PrimitiveType type, boolean isGlobal, int line) {
        this.name = name;
        this.initializer = initializer;

        this.type = type;
        this.isGlobal = isGlobal;

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

    public int getLine() {
        return this.line;
    }

    public boolean isGlobal() {
        return this.isGlobal;
    }
}
