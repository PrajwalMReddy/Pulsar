package temp.ast;

import temp.ast.statement.Block;
import temp.ast.statement.ExpressionStmt;
import temp.ast.statement.If;

public abstract class Statement {
    public interface Visitor<R> {
        // Statement Visitor Methods
        R visitBlockStatement(Block statement);
        R visitExpressionStatement(ExpressionStmt statement);
        R visitIFStatement(If statement);
    }

    public abstract <R> R accept(Visitor<R> visitor);
}
