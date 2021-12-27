package org.codepulsar.pulsar;

import java.util.ArrayList;

public class LocalVariable {
    ArrayList<Local> variables;
    int scopeDepth;

    public LocalVariable() {
        this.variables = new ArrayList<>();
        this.scopeDepth = 0;
    }

    public void newLocal(String name, int offset) {
        this.variables.add(new Local(name, offset, this.scopeDepth));
    }

    public Local getLocal(int index) {
        return this.variables.get(index);
    }

    public static class Local {
        String name;
        int stackOffset;
        int depth;

        public Local(String name, int stackOffset, int depth) {
            this.name = name;
            this.stackOffset = stackOffset;
            this.depth = depth;
        }
    }
}
