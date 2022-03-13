package temp.ast.statement;

import temp.ast.Expression;
import temp.ast.Statement;

public class Variable extends Statement {
    private final String name;
    private final Expression initializer;
    private boolean isGlobal;

    private final int line;

    public Variable(String name, Expression initializer, boolean isGlobal, int line) {
        this.name = name;
        this.initializer = initializer;
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

    public int getLine() {
        return this.line;
    }

    public boolean isGlobal() {
        return this.isGlobal;
    }
}
