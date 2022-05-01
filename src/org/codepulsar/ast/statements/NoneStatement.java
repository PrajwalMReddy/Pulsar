package org.codepulsar.ast.statements;

import org.codepulsar.ast.Statement;

/*
    Indicates nothing should be done. This can be used if a return statement is needed, but an error occurred.
*/

public class NoneStatement extends Statement {
    public NoneStatement() {
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitNoneStatement(this);
    }
}
