package temp.ast.expression;

import temp.ast.Expression;
import temp.lang.Token;

public class OpAssignment extends Expression {
    private final Token identifier;
    private final Token assignmentType;
    private final Expression value;

    public OpAssignment(Token identifier, Token assignmentType, Expression value) {
        this.identifier = identifier;
        this.assignmentType = assignmentType;
        this.value = value;
    }

    public <R> R accept(Expression.Visitor<R> visitor) {
        return visitor.visitOpAssignmentExpression(this);
    }

    public Token getIdentifier() {
        return this.identifier;
    }

    public Token getAssignmentType() {
        return this.assignmentType;
    }

    public Expression getValue() {
        return this.value;
    }
}
