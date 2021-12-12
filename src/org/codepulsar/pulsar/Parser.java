package org.codepulsar.pulsar;

import java.util.ArrayList;
import static org.codepulsar.pulsar.TokenType.*;
import static org.codepulsar.pulsar.ByteCode.*;

public class Parser {
    private final String sourceCode;
    private ArrayList<Token> tokens;
    private ArrayList<Instruction> instructions;
    private ArrayList<Object> values;
    private int current;

    public Parser(String sourceCode) {
        this.sourceCode = sourceCode;
        this.tokens = new ArrayList<>();
        this.instructions = new ArrayList<>();
        this.values = new ArrayList<>();
        this.current = 0;
    }

    public ArrayList<Instruction> parse() {
        Lexer lexer = new Lexer(this.sourceCode + "\n");
        this.tokens = lexer.tokenize();

        System.out.println(this.tokens);

        expression();
        return this.instructions;
    }

    private void expression() {
        primary();
    }

    private void primary() {
        while (match(INTEGER)) {
            this.instructions.add(makeOpCode(OP_CONSTANT));
            advance();
        }
    }

    private Instruction makeOpCode(ByteCode opcode) {
        if (opcode == OP_CONSTANT) {
            this.values.add(peek().getLiteral());
            return new Instruction(OP_CONSTANT, this.values.size() - 1);
        } else {
            return new Instruction(opcode, null);
        }
    }

    private boolean match(TokenType type) {
        return peek().getTtype() == type;
    }

    private boolean isAtEnd() {
        return this.current >= this.tokens.size();
    }

    private Token peek() {
        return this.tokens.get(this.current);
    }

    private Token advance() {
        this.current++;
        return this.tokens.get(this.current - 1);
    }
}
