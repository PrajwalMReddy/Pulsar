package temp.ast.statement;

import temp.ast.Statement;

import java.util.ArrayList;

public class Block extends Statement {
    private final ArrayList<Statement> statements;

    private final int line;

    public Block(ArrayList<Statement> statements, int line) {
        this.statements = statements;
        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitBlockStatement(this);
    }

    public ArrayList<Statement> getStatements() {
        return this.statements;
    }

    public int getLine() {
        return this.line;
    }
}
