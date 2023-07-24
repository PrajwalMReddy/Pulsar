#ifndef CODEPULSAR_BYTECODE_H
#define CODEPULSAR_BYTECODE_H


namespace Pulsar {
    enum ByteCode {
        // Operators
        OP_NEGATE, OP_NOT, // Unary
        OP_ADD, OP_SUBTRACT, OP_MULTIPLY, OP_DIVIDE, OP_MODULO, // Binary
        OP_COMPARE_EQUAL, OP_COMPARE_GREATER, OP_COMPARE_LESSER, // Comparison

        // Data Types and Variables
        OP_CONSTANT,
        OP_NEW_GLOBAL, OP_STORE_GLOBAL, OP_LOAD_GLOBAL,
        OP_NEW_LOCAL, OP_SET_LOCAL, OP_GET_LOCAL, // OP_NEW_LOCAL Is A Dummy Opcode

        // Control Flow OpCodes
        OP_JUMP, OP_JUMP_IF_TRUE, OP_JUMP_IF_FALSE,

        // Functions and Classes
        OP_LOAD_FUNCTION, OP_CALL, OP_RETURN,

        // Special OpCodes
        OP_PRINT, OP_POP, OP_ERROR, // TODO OP_PRINT Is A Temporary Opcode
    };
}


#endif
