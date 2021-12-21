package org.codepulsar.pulsar;

import org.codepulsar.primitives.Primitive;

import java.util.HashMap;

public class Variable {
    HashMap<String, Primitive> values;

    public Variable() {
        this.values = new HashMap<>();
    }

    public void newVariable(String name, Primitive value) {
        this.values.put(name, value);
    }

    public void reassignVariable(String name, Primitive value) {
        this.values.put(name, value);
    }

    public Primitive getValue(String name) {
        return this.values.get(name);
    }

    public boolean containsKey(String name) {
        Primitive value = this.values.get(name);

        if (value == null) {
            return false;
        }
        return true;
    }
}
