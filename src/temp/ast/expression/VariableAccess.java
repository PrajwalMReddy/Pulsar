package temp.ast.expression;

import temp.ast.Expression;
import temp.primitives.PrimitiveType;

import static temp.primitives.PrimitiveType.*;

public class VariableAccess extends Expression {
    private final String name;
    private PrimitiveType type;

    private final int line;

    public VariableAccess(String name, int line) {
        this.name = name;
        this.type = PR_NULL; // TODO Change This Later Once Static Typing Is Added

        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitVariableExpression(this);
    }

    public String getName() {
        return this.name;
    }

    public PrimitiveType getType() {
        return this.type;
    }

    public int getLine() {
        return this.line;
    }
}
