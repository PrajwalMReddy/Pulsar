package temp.ast.expression;

import temp.ast.Expression;

public class VariableAccess extends Expression {
    private final String name;

    private final boolean isGlobalVariable;
    private final int number;

    private final int line;

    public VariableAccess(String name, boolean isGlobalVariable, int number, int line) {
        this.name = name;
        this.isGlobalVariable = isGlobalVariable;
        this.number = number;

        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitVariableExpression(this);
    }

    public String getName() {
        return this.name;
    }

    public boolean isGlobalVariable() {
        return this.isGlobalVariable;
    }

    public int getNumber() {
        return this.number;
    }

    public int getLine() {
        return this.line;
    }
}
