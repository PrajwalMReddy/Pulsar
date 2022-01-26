package org.codepulsar.pulsar;

import java.util.ArrayList;

public class LocalVariable {
    ArrayList<Local> variables;
    int scopeDepth;
    int localCount;

    public LocalVariable() {
        this.variables = new ArrayList<>();
        this.scopeDepth = 1; // TODO Change Back To 0 When Functions Are Implemented
        this.localCount = 0;
    }

    public void newLocal(Token name, boolean isConstant) {
        this.variables.add(this.localCount, new Local(name, this.scopeDepth, isConstant));
    }

    public Local getLocal(int index) {
        return this.variables.get(index);
    }

    public static class Local {
        Token name;
        int depth;
        boolean isConstant;

        public Local(Token name, int depth, boolean isConstant) {
            this.name = name;
            this.depth = depth;
            this.isConstant = isConstant;
        }
    }
}
