package org.codepulsar.primitives;

public class PBoolean extends Primitive {
    boolean value;

    public PBoolean(boolean value) {
        this.value = value;
    }

    public String toString() {
        return String.valueOf(value);
    }

    public boolean isValue() {
        return value;
    }
}