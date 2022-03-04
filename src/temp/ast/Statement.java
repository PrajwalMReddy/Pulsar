package temp.ast;

import temp.ast.statement.ExpressionStmt;

public abstract class Statement {
    public interface Visitor<R> {
        // Statement Visitor Methods
        R visitExpressionStatement(ExpressionStmt statement);
    }

    public abstract <R> R accept(Visitor<R> visitor);
}
