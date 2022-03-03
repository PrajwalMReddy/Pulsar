package temp.util;

import temp.ast.Expression;
import temp.ast.expression.*;
import temp.pulsar.Pulsar;

public class ASTPrinter implements Expression.Visitor<String> {
    public void print(Expression ast) { // TODO Change 'Expression' To AST Later As Well
        if (Pulsar.conditions.getDebug()) {
            System.out.println("\n-- AST --\n");
            constructTree(ast);
        }
    }

    private void constructTree(Expression ast) { // TODO Here As Well
        System.out.println(ast.accept(this));
    }

    public String visitAssignmentExpression(Assignment expression) {
        return "Assignment(Variable(" + expression.getIdentifier().getLiteral() + ") = " + expression.getValue().accept(this) + ")";
    }

    public String visitBinaryExpression(Binary expression) {
        return "Binary(" + expression.getLeft().accept(this) + " " + expression.getOperator().getLiteral() + " " + expression.getRight().accept(this) + ")";
    }

    public String visitGroupingExpression(Grouping expression) {
        return "(" + expression.getExpression().accept(this) + ")";
    }

    public String visitLiteralExpression(Literal expression) {
        return "Literal(" + expression.getValue() + ")";
    }

    public String visitLogicalExpression(Logical expression) {
        return "Logical(" + expression.getLeft().accept(this) + " " + expression.getOperator().getLiteral() + " " + expression.getRight().accept(this) + ")";
    }

    public String visitOpAssignmentExpression(OpAssignment expression) {
        return "Assignment(Variable(" + expression.getIdentifier().getLiteral() + ") " + expression.getAssignmentType().getLiteral() + " " + expression.getValue().accept(this) + ")";
    }

    public String visitUnaryExpression(Unary expression) {
        return "Unary(" + expression.getOperator().getLiteral() + " " + expression.getRight().accept(this) + ")";
    }

    public String visitVariableExpression(Variable expression) {
        return "Variable(" + expression.getName() + ")";
    }
}
