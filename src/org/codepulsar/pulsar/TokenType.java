package org.codepulsar.pulsar;

public enum TokenType {
    // Operators
    NOT, PLUSPLUS, MINUSMINUS, // Unary
    MINUS, PLUS, MULTIPLICATION, DIVISION, // Binary
    NOTEQUAL, EQUALEQUAL, GT, GTEQUAL, LT, LTEQUAL, // Comparison
    EQUAL, PLUSEQUAL, MINUSEQUAL, MULEQUAL, DIVEQUAL, // Assignment
    LOGICALOR, LOGICALAND, // Logical

    // Other Character Tokens
    DOT, COMMA, COLON, SEMICOLON, DOUBLECOLON, QMARK,
    LPAR, RPAR, LBRACE, RBRACE,

    // Keywords
    PACKAGE, USE, MOD, CLASS,
    VAR, CONST,
    FUN, RETURN,
    IF, ELSE, WHILE,

    // Data Types and Variables
    STRING, INTEGER, DOUBLE, IDENTIFIER,

    // Special Tokens
    ERROR, EOF
}
