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

    public void newLocal(Token token, String name, PrimitiveType type, boolean isInitialized, boolean isConstant) {
        this.variables.add(this.localCount, new Local(token, name, type, isInitialized, isConstant, this.scopeDepth));
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
        private Token token;

        private final String name;
        private final PrimitiveType type;

        private boolean isInitialized;
        private final boolean isConstant;
        private final int depth;

        public Local(Token token, String name, PrimitiveType type, boolean isInitialized, boolean isConstant, int depth) {
            this.token = token;

            this.name = name;
            this.type = type;

            this.isInitialized = isInitialized;
            this.isConstant = isConstant;
            this.depth = depth;
        }

        public String getName() {
            return this.name;
        }

        public PrimitiveType getType() {
            return this.type;
        }

        public boolean isInitialized() {
            return this.isInitialized;
        }

        public void setInitialized() {
            this.isInitialized = true;
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
