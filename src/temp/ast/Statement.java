package temp.ast;

import temp.ast.statement.*;

public abstract class Statement {
    public interface Visitor<R> {
        // Statement Visitor Methods
        R visitBlockStatement(Block statement);
        R visitEndScopeStatement(EndScope statement);
        R visitExpressionStatement(ExpressionStmt statement);
        R visitIFStatement(If statement);
        R visitVariableStatement(Variable statement);
        R visitWhileStatement(While statement);
    }

    public abstract <R> R accept(Visitor<R> visitor);
}
