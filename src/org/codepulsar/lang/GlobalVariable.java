package org.codepulsar.lang;

import org.codepulsar.primitives.Primitive;
import org.codepulsar.primitives.PrimitiveType;

import java.util.HashMap;

public class GlobalVariable {
    HashMap<String, Global> variables;

    public GlobalVariable() {
        this.variables = new HashMap<>();
    }

    public void addVariable(String name, Primitive value, PrimitiveType type, boolean isInitialized, boolean isConstant) {
        this.variables.put(name, new Global(value, type, isInitialized, isConstant));
    }

    public void reassignVariable(String name, Primitive value) {
        Global variable = this.variables.get(name);

        this.variables.put(name, new Global(value, variable.getType(), true, variable.isConstant()));
    }

    public Primitive getValue(String name) {
        return this.variables.get(name).getValue();
    }

    public PrimitiveType getType(String name) {
        return this.variables.get(name).getType();
    }

    public boolean containsVariable(String name) {
        Global global = this.variables.get(name);
        return global != null;
    }

    record Global(Primitive value, PrimitiveType type, boolean isInitialized, boolean isConstant) {
        public Primitive getValue() {
            return this.value;
        }

        public PrimitiveType getType() {
            return this.type;
        }
    }
}
