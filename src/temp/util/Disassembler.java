package temp.util;

import temp.lang.ByteCode;
import temp.lang.Instruction;
import temp.pulsar.ByteCodeCompiler;
import temp.pulsar.Pulsar;

import java.util.ArrayList;

public class Disassembler {
    public static void disassemble(ArrayList<Instruction> instructions, ByteCodeCompiler bcc) {
        if (Pulsar.conditions.getDebug()) {
            System.out.println("\n-- Disassembled Bytecode --");
            displayInstructions(instructions, bcc);
        }
    }

    private static void displayInstructions(ArrayList<Instruction> instructions, ByteCodeCompiler bcc) {
        int line = 0;
        int count = 0;

        for (Instruction instruction: instructions) {
            if (instruction.getLine() == line) {
                System.out.print("            " + count + "  | ");
            } else {
                line = instruction.getLine();
                System.out.print("\n" + line + spaces(line) + count + "  | ");
            }

            decide(instruction, bcc);
            count++;
        }
    }

    private static void decide(Instruction instruction, ByteCodeCompiler bcc) {
        switch (instruction.getOpcode()) {
            // These Are OpCodes That Have Operands
            case OP_CONSTANT, OP_JUMP, OP_JUMP_IF_TRUE, OP_JUMP_IF_FALSE,
                    OP_NEW_GLOBAL, OP_STORE_GLOBAL, OP_LOAD_GLOBAL,
                    OP_SET_LOCAL, OP_GET_LOCAL, OP_NEW_LOCAL -> operand(instruction, bcc);

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
    private static void operand(Instruction instruction, ByteCodeCompiler bcc) {
        if (instruction.getOpcode() == ByteCode.OP_CONSTANT) {
            System.out.println(ByteCode.OP_CONSTANT + spaces(instruction) + instruction.getOperand()
                    + "  (" + bcc.getValues().get((int) instruction.getOperand()) + ")");
        } else {
            System.out.println(instruction.getOpcode() + spaces(instruction) + instruction.getOperand());
        }
    }

    private static String spaces(Instruction instruction) {
        int length = instruction.getOpcode().toString().length();
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
