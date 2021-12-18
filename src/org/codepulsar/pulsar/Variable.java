package org.codepulsar.pulsar;

import org.codepulsar.primitives.Primitive;

import java.util.HashMap;

public class Variable {
    HashMap<String, Primitive> values;

    public Variable() {
        this.values = new HashMap<>();
    }
}
