package org.codepulsar.ast.statement;

import org.codepulsar.ast.Statement;
import org.codepulsar.primitives.PrimitiveType;

import java.util.HashMap;

public class Function extends Statement {
    private String name;
    private PrimitiveType type;

    private HashMap<String, PrimitiveType> parameters;
    private Block statements;

    private int line;

    public Function(String name, PrimitiveType type, HashMap<String, PrimitiveType> parameters, Block statements, int line) {
        this.name = name;
        this.type = type;

        this.parameters = parameters;
        this.statements = statements;

        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitFunctionStatement(this);
    }

    public HashMap<String, PrimitiveType> getParameters() {
        return this.parameters;
    }

    public Block getStatements() {
        return this.statements;
    }
}
