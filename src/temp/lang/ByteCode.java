package temp.lang;

public enum ByteCode {
    // Operators
    OP_NEGATE, OP_NOT, // Unary
    OP_ADD, OP_SUBTRACT, OP_MULTIPLY, OP_DIVIDE, OP_MODULO, // Binary
    OP_COMPARE_EQUAL, OP_COMPARE_GREATER, OP_COMPARE_LESSER, // Comparison

    // Data Types and Variables
    OP_CONSTANT, OP_NULL, // TODO Come Back To OP_NULL Later
    OP_NEW_GLOBAL, OP_STORE_GLOBAL, OP_LOAD_GLOBAL,
    OP_NEW_LOCAL, OP_SET_LOCAL, OP_GET_LOCAL, // OP_NEW_LOCAL Is A Dummy Opcode

    // Control Flow OpCodes
    OP_JUMP, OP_JUMP_IF_TRUE, OP_JUMP_IF_FALSE,

    // Special OpCodes
    OP_PRINT, OP_POP, // TODO OP_PRINT Is A Temporary Opcode
}
