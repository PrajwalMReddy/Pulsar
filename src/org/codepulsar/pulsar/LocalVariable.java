package org.codepulsar.pulsar;

import java.util.ArrayList;

public class LocalVariable {
    Local[] variables;
    int scopeDepth;
    int localCount;

    public LocalVariable() {
        this.variables = new Local[2048];
        this.scopeDepth = 0;
        this.localCount = 0;
    }

    public void newLocal(Token name) {
        this.variables[this.localCount] = new Local(name, this.scopeDepth);
    }

    public Local getLocal(int index) {
        return this.variables[index];
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
