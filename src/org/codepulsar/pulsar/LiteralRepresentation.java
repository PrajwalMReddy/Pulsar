package org.codepulsar.pulsar;

public class LiteralRepresentation {
    private Object value;

    public LiteralRepresentation(Object value) {
        this.value = value;
    }

    public String toString() {
        if (this.value instanceof Integer) {
            return String.valueOf(Integer.parseInt(this.value.toString()));
        } else if (this.value instanceof Double) {
            return String.valueOf(Double.parseDouble(this.value.toString()));
        } else {
            return this.value.toString();
        }
    }
}
