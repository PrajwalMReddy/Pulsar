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

    public void newLocal(Token name) {
        this.variables.add(this.localCount, new Local(name, this.scopeDepth));
    }

    public Local getLocal(int index) {
        return this.variables.get(index);
    }

    public static class Local {
        Token name;
        int depth;

        public Local(Token name, int depth) {
            this.name = name;
            this.depth = depth;
        }
    }
}
