package org.codepulsar.pulsar;

public enum ByteCode {
    OP_CONSTANT,

    // 4 Horsemen of Arithmetic
    OP_ADD, OP_SUBTRACT, OP_MULTIPLY, OP_DIVIDE,

    // Unary
    OP_NEGATE, OP_NOT,
}
