package org.codepulsar.pulsar;

import java.util.ArrayList;
import java.util.Arrays;

import static org.codepulsar.pulsar.TokenType.*;

public class Disassembler {
    public static void tokens(ArrayList<Token> tokens) {
        // Tokens With Meaningful Literals Attached To Them
        TokenType[] literals = {TK_STRING, TK_INTEGER, TK_DOUBLE, TK_IDENTIFIER};
        int line = 0;
        System.out.println("-- Tokens --");

        for (Token token: tokens) {
            if (token.getLine() == line) {
                System.out.print("            ");
            } else {
                line = token.getLine();
                System.out.print("\n" + line + spaces(line));
            }
            if (Arrays.asList(literals).contains(token.getTokenType())) {
                System.out.println(token.getTokenType() + spaces(token) + "(" + token.getLiteral() + ")");
            } else {
                System.out.println(token.getTokenType());
            }
        }
    }

    public static void disassemble(ArrayList<Instruction> instructions) {
        int line = 0;
        System.out.println("\n-- Disassembled Bytecode --");
        int count = 0;

        for (Instruction instruction : instructions) {
            if (instruction.getLine() == line) {
                System.out.print("            " + count + "  | ");
            } else {
                line = instruction.getLine();
                System.out.print("\n" + line + spaces(line) + count + "  | ");
            }
            decide(instruction);

            count++;
        }
    }

    private static void decide(Instruction instruction) {
        switch (instruction.getOpcode()) {
            // These Are OpCodes That Have Operands
            case OP_CONSTANT, OP_JUMP, OP_JUMP_IF_TRUE, OP_JUMP_IF_FALSE,
                    OP_NEW_GLOBAL, OP_STORE_GLOBAL, OP_LOAD_GLOBAL,
                    OP_SET_LOCAL, OP_GET_LOCAL, OP_NEW_LOCAL -> operand(instruction);

            // These Are OpCodes That Don't Have Operands
            case OP_ADD, OP_SUBTRACT, OP_MULTIPLY, OP_DIVIDE, OP_MODULO, OP_NEGATE,
                    OP_NOT, OP_COMPARE_EQUAL, OP_COMPARE_GREATER, OP_COMPARE_LESSER,
                    OP_POP, OP_NULL, OP_PRINT -> opcode(instruction);
        }
    }

    private static void opcode(Instruction instruction) {
        System.out.println(instruction.getOpcode());
    }

    // Displays the OpCode With The Necessary Spaces After It, And Then Prints Out The Operand
    private static void operand(Instruction instruction) {
        if (instruction.getOpcode() == ByteCode.OP_CONSTANT) {
            System.out.println(ByteCode.OP_CONSTANT + spaces(instruction) + instruction.getOperand()
                    + "  (" + Parser.values.get((int) instruction.getOperand()) + ")");
        } else {
            System.out.println(instruction.getOpcode() + spaces(instruction) + instruction.getOperand());
        }
    }

    // Overloaded Functions That 'Gives' The Spaces Required Based On The Parameter Type
    // It Works For Instructions, Tokens, and ints

    private static String spaces(Instruction instruction) {
        int length = instruction.getOpcode().toString().length();
        return giveSpaces(length);
    }

    private static String spaces(Token token) {
        int length = token.getTokenType().toString().length();
        return giveSpaces(length);
    }

    private static String spaces(int line) {
        int length = String.valueOf(line).length();
        return giveSpaces(length + 9);
    }

    // Calculates How Many Spaces To Provide Based On The Length Of The Argument Passed In
    private static String giveSpaces(int length) {
        return " ".repeat(Math.max(0, 20 - length + 1));
    }
}
