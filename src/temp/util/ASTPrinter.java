package temp.util;

import temp.ast.Expression;
import temp.pulsar.Pulsar;

public class ASTPrinter {
    // TODO Change This To A Proper Printer Later (If Needed)
    public static void print(Expression ast) { // TODO Change 'Expression' To AST Later As Well
        if (Pulsar.conditions.getDebug()) {
            System.out.println("\n-- Abstract Syntax Tree --\n");
            System.out.println(ast);
        }
    }
}
