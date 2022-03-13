package temp.ast;

import temp.ast.expression.*;

public abstract class Expression {
    public interface Visitor<R> {
        // Expression Visitor Methods
        R visitAssignmentExpression(Assignment expression);
        R visitBinaryExpression(Binary expression);
        R visitGroupingExpression(Grouping expression);
        R visitLiteralExpression(Literal expression);
        R visitLogicalExpression(Logical expression);
        R visitUnaryExpression(Unary expression);
        R visitVariableExpression(VariableAccess expression);
    }

    public abstract <R> R accept(Visitor<R> visitor);
}
