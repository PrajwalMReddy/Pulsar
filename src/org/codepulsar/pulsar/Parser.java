package org.codepulsar.pulsar;

import org.codepulsar.primitives.*;

import java.util.ArrayList;

import static org.codepulsar.pulsar.TokenType.*;
import static org.codepulsar.pulsar.ByteCode.*;

public class Parser {
    private final String sourceCode;
    private ArrayList<Token> tokens;
    private final ArrayList<Instruction> instructions;
    public static ArrayList<Primitive> values;
    private int current;
    public final ArrayList<Error> errors;
    boolean hasErrors;

    public Parser(String sourceCode) {
        this.sourceCode = sourceCode;
        this.tokens = new ArrayList<>();
        this.instructions = new ArrayList<>();
        values = new ArrayList<>();
        this.current = 0;
        this.errors = new ArrayList<>();
        this.hasErrors = false;
    }

    public ArrayList<Instruction> parse() {
        Lexer lexer = new Lexer(this.sourceCode + "\n");
        this.tokens = lexer.tokenize();

        if (CommandsKt.getDebug()) {
            Disassembler.tokens(this.tokens);
        }

        while (!match(TK_EOF)) {
            unary();
        }

        return this.instructions;
    }

    private void unary() {
        if (matchAdvance(TK_NOT)) {
            unary();
            makeOpCode(OP_NOT, peekLine());
        } else if (matchAdvance(TK_MINUS)) {
            unary();
            makeOpCode(OP_NEGATE, peekLine());
        } else {
            primary();
        }
    }

    private void primary() {
        if (match(TK_INTEGER, TK_DOUBLE, TK_TRUE, TK_FALSE, TK_NULL)) {
            makeOpCode(OP_CONSTANT, peekLine());
            advance();
        }
    }

    private Instruction makeOpCode(ByteCode opcode, int line) {
        if (opcode == OP_CONSTANT) {
            Primitive lr = new Primitive();
            switch (peekType()) {
                case TK_INTEGER -> lr = new PInteger(Integer.parseInt(peekLiteral()));
                case TK_DOUBLE -> lr = new PDouble(Double.parseDouble(peekLiteral()));
                case TK_TRUE -> lr = new PBoolean(true);
                case TK_FALSE -> lr = new PBoolean(false);
                case TK_NULL -> lr = new PNull();
            }
            values.add(lr);
            Instruction instruction = new Instruction(OP_CONSTANT, values.size() - 1, line);
            this.instructions.add(instruction);
            return instruction;
        } else {
            Instruction instruction = new Instruction(opcode, null, line);
            this.instructions.add(instruction);
            return instruction;
        }
    }

    private Instruction makeOpCode(ByteCode opcode, Object operand, int line) {
        Instruction instruction = new Instruction(opcode, operand, line);
        this.instructions.add(instruction);
        return instruction;
    }

    private boolean match(TokenType... types) {
        for (TokenType type: types) {
            if (peekType() == type) {
                return true;
            }
        }
        return false;
    }

    private boolean matchAdvance(TokenType... types) {
        for (TokenType type: types) {
            if (peekType() == type) {
                advance();
                return true;
            }
        }
        return false;
    }

    private Token advance() {
        this.current++;
        return this.tokens.get(this.current - 1);
    }

    private Token peek() {
        return this.tokens.get(this.current);
    }

    private TokenType peekType() {
        return this.tokens.get(this.current).getTtype();
    }

    private int peekLine() {
        return this.tokens.get(this.current).getLine();
    }

    private String peekLiteral() {
        return this.tokens.get(this.current).getLiteral();
    }
}
