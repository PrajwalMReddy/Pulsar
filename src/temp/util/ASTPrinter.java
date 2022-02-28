package temp.util;

import temp.ast.Expression;
import temp.lang.AST;
import temp.pulsar.Pulsar;

public class ASTPrinter {
    public static void print(Expression ast) { // TODO Change 'Expression' To AST Later As Well
        if (Pulsar.conditions.getDebug()) {
            printAST(ast);
        }
    }

    private static void printAST(Expression ast) { // TODO And Here
        System.out.println("Printed!");
    }
}
