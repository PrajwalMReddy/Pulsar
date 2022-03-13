package temp.ast.expression;

import temp.ast.Expression;

public class VariableAccess extends Expression {
    private final String name;

    private final int line;

    public VariableAccess(String name, int line) {
        this.name = name;
        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitVariableExpression(this);
    }

    public String getName() {
        return this.name;
    }

    public int getLine() {
        return this.line;
    }
}
