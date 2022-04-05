package temp.lang;

import temp.primitives.PrimitiveType;

import java.util.ArrayList;

public class LocalVariable {
    ArrayList<Local> variables;
    int scopeDepth;
    int localCount;

    public LocalVariable() {
        this.variables = new ArrayList<>();
        this.scopeDepth = 1;
        this.localCount = 0;
    }

    public void newLocal(Token token, String name, PrimitiveType type, boolean isConstant) {
        this.variables.add(this.localCount, new Local(token, name, type, isConstant, this.scopeDepth));
        this.localCount++;
    }

    public Local getLocal(int index) {
        return this.variables.get(index);
    }

    public Local getLocal(String name) {
        for (int i = 0; i < this.getLocalCount(); i++) {
            LocalVariable.Local local = this.getLocal(i);

            if (local.getName().equals(name)) {
                return local;
            }
        }

        return null;
    }

    public int getLocalCount() {
        return this.localCount;
    }

    public void incrementDepth() {
        this.scopeDepth++;
    }

    public void decrementDepth() {
        this.scopeDepth--;
    }

    public void decrementLocalCount() {
        this.localCount--;
    }

    public static class Local {
        Token token;

        private final String name;
        private final PrimitiveType type;

        private final boolean isConstant;
        private final int depth;

        public Local(Token token, String name, PrimitiveType type, boolean isConstant, int depth) {
            this.token = token;

            this.name = name;
            this.type = type;

            this.isConstant = isConstant;
            this.depth = depth;
        }

        public String getName() {
            return this.name;
        }

        public PrimitiveType getType() {
            return this.type;
        }

        public boolean isConstant() {
            return this.isConstant;
        }

        public int getLine() {
            return this.token.getLine();
        }

        public int getDepth() {
            return this.depth;
        }
    }
}
