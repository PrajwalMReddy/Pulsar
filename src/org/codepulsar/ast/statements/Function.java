package org.codepulsar.ast.statements;

import org.codepulsar.ast.Statement;
import org.codepulsar.primitives.PrimitiveType;

import java.util.ArrayList;

public class Function extends Statement {
    private final String name;
    private final PrimitiveType type;

    private final ArrayList<Parameter> parameters;
    private final int arity;
    private final Block statements;

    private final int line;

    public Function(String name, PrimitiveType type, ArrayList<Parameter> parameters, int arity, Block statements, int line) {
        this.name = name;
        this.type = type;

        this.parameters = parameters;
        this.arity = arity;
        this.statements = statements;

        this.line = line;
    }

    public <R> R accept(Visitor<R> visitor) {
        return visitor.visitFunctionStatement(this);
    }

    public String getName() {
        return this.name;
    }

    public ArrayList<Parameter> getParameters() {
        return this.parameters;
    }

    public int getArity() {
        return this.arity;
    }

    public Block getStatements() {
        return this.statements;
    }

    public int getLine() {
        return this.line;
    }

    public static class Parameter {
        private final String name;
        private final PrimitiveType type;

        public Parameter(String name, PrimitiveType type) {
            this.name = name;
            this.type = type;
        }

        public String getName() {
            return this.name;
        }

        public PrimitiveType getType() {
            return this.type;
        }
    }
}
