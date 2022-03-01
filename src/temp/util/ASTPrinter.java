package temp.util;

import temp.ast.Expression;
import temp.ast.expression.*;
import temp.lang.Visitor;
import temp.pulsar.Pulsar;

public class ASTPrinter implements Visitor<String> {
    public void print(Expression ast) { // TODO Change 'Expression' To AST Later As Well
        if (Pulsar.conditions.getDebug()) {
            System.out.println("\n-- AST --\n");
            constructTree(ast);
        }
    }

    private void constructTree(Expression ast) { // TODO Here As Well
        System.out.println(ast.accept(this));
    }

    // TODO All Below

    public String visitAssignmentExpression(Assignment expression) {
        return null;
    }

    public String visitBinaryExpression(Binary expression) {
        return null;
    }

    public String visitGroupingExpression(Grouping expression) {
        return null;
    }

    public String visitLiteralExpression(Literal expression) {
        return null;
    }

    public String visitLogicalExpression(Logical expression) {
        return null;
    }

    public String visitUnaryExpression(Unary expression) {
        return null;
    }

    public String visitVariableExpression(Variable expression) {
        return null;
    }
}
