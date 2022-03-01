package temp.lang;

import temp.ast.expression.*;

public interface Visitor<R> {
    // Expression Visitor Methods
    R visitAssignmentExpression(Assignment expression);
    R visitBinaryExpression(Binary expression);
    R visitGroupingExpression(Grouping expression);
    R visitLiteralExpression(Literal expression);
    R visitLogicalExpression(Logical expression);
    R visitUnaryExpression(Unary expression);
    R visitVariableExpression(Variable expression);
}
