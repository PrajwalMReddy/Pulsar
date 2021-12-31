package org.codepulsar.primitives;

public class PDouble extends Primitive {
    double value;

    public PDouble(double value) {
        this.value = value;
    }

    public String toString() {
        return String.valueOf(value);
    }

    public double getValue() {
        return value;
    }
}