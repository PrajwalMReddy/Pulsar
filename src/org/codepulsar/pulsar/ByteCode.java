package org.codepulsar.pulsar;

public enum ByteCode {
    // Operators,
    OP_NEGATE, OP_NOT, // Unary
    OP_ADD, OP_SUBTRACT, OP_MULTIPLY, OP_DIVIDE, OP_MODULO, // Binary
    OP_COMPARE_EQUAL, OP_GREATER, OP_LESSER, // Comparison

    // Data Types and Variables
    OP_CONSTANT, OP_NULL, OP_STORE_GLOBAL, OP_LOAD_GLOBAL,

    // Control Flow OpCodes
    OP_JUMP, OP_JUMP_IF_TRUE, OP_JUMP_IF_FALSE,

    // Special OpCodes
    OP_PRINT, OP_POP
}
