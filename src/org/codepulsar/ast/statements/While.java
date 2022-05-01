package org.codepulsar.ast.statements;

import org.codepulsar.ast.Expression;
import org.codepulsar.ast.Statement;

public class While extends Statement {
    private final Expression condition;
    private final Block statements;

    private final int line;

    public While(Expression condition, Block statements, int line) {
        this.condition = condition;
        this.statements = statements;
        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitWhileStatement(this);
    }

    public Expression getCondition() {
        return this.condition;
    }

    public Block getStatements() {
        return this.statements;
    }

    public int getLine() {
        return this.line;
    }
}
