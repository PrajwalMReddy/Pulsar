package temp.ast.statement;

import temp.ast.Expression;
import temp.ast.Statement;

public class ExpressionStmt extends Statement {
    private final Expression expression;
    private final int line;

    public ExpressionStmt(Expression expression, int line) {
        this.expression = expression;
        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitExpressionStatement(this);
    }

    public Expression getExpression() {
        return this.expression;
    }

    public int getLine() {
        return this.line;
    }
}
