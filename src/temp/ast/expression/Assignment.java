package temp.ast.expression;

import temp.ast.Expression;

public class Assignment extends Expression {
    private final String identifier;

    private final boolean isGlobalAssignment;
    private final int number;

    private final Expression value;
    private final int line;

    public Assignment(String identifier, boolean isGlobalAssignment, int number, Expression value, int line) {
        this.identifier = identifier;
        this.isGlobalAssignment = isGlobalAssignment;
        this.number = number;
        this.value = value;
        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitAssignmentExpression(this);
    }

    public String getIdentifier() {
        return this.identifier;
    }

    public boolean isGlobalAssignment() {
        return this.isGlobalAssignment;
    }

    public int getNumber() {
        return this.number;
    }

    public Expression getValue() {
        return this.value;
    }

    public int getLine() {
        return this.line;
    }
}
