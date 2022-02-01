package org.codepulsar.pulsar;

import org.codepulsar.primitives.Primitive;

import java.util.HashMap;

// TODO Figure Out A Way To Make Constant Global Variables
public class GlobalVariable {
    HashMap<String, Primitive> values;

    public GlobalVariable() {
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
        return value != null;
    }
}
