package temp.ast.statement;

import temp.ast.Statement;

/*
    Used to indicate a scope has ended and the local variables stored on the stack can be deleted.
*/

public class EndScope extends Statement {
    private final int localsToDelete;
    private final int line;

    public EndScope(int localsToDelete, int line) {
        this.localsToDelete = localsToDelete;
        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitEndScopeStatement(this);
    }

    public int getLocalsToDelete() {
        return this.localsToDelete;
    }

    public int getLine() {
        return this.line;
    }
}
