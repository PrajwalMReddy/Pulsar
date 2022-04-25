package org.codepulsar.ast.statement;

import org.codepulsar.ast.Expression;
import org.codepulsar.ast.Statement;

public class If extends Statement {
    private final Expression condition;
    private final Block thenBranch;
    private final Statement elseBranch;

    private final int line;

    public If(Expression condition, Block thenBranch, Statement elseBranch, int line) {
        this.condition = condition;
        this.thenBranch = thenBranch;
        this.elseBranch = elseBranch;
        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitIfStatement(this);
    }

    public boolean hasElse() {
        return elseBranch != null;
    }

    public Expression getCondition() {
        return this.condition;
    }

    public Block getThenBranch() {
        return this.thenBranch;
    }

    public Statement getElseBranch() {
        return this.elseBranch;
    }

    public int getLine() {
        return this.line;
    }
}
