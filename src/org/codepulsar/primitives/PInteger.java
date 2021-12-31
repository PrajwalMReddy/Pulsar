package org.codepulsar.primitives;

public class PInteger extends Primitive {
    int value;

    public PInteger(int value) {
        this.value = value;
    }

    public String toString() {
        return String.valueOf(value);
    }

    public int getValue() {
        return value;
    }
}