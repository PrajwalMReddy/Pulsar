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
    ArrayList<Error> errors;
    boolean hasError;

    public Parser(String sourceCode) {
        this.sourceCode = sourceCode;
        this.tokens = new ArrayList<>();
        this.instructions = new ArrayList<>();
        this.values = new ArrayList<>();
        this.current = 0;
        this.errors = new ArrayList<>();
        this.hasError = false;
    }

    public ArrayList<Instruction> parse() {
        Lexer lexer = new Lexer(this.sourceCode + "\n");
        this.tokens = lexer.tokenize();

        System.out.println(this.tokens);

        expression();
        return this.instructions;
    }

    private void expression() {
        term();
    }

    private void term() {
        factor();

        while (match(TK_PLUS) || match(TK_MINUS)) {
            if (peek().getTtype() == TK_PLUS) {
                advance();
                factor();
                this.instructions.add(makeOpCode(OP_ADD));
            } else if (peek().getTtype() == TK_MINUS) {
                advance();
                factor();
                this.instructions.add(makeOpCode(OP_SUBTRACT));
            }
        }
    }

    private void factor() {
        unary();

        while (match(TK_MULTIPLICATION) || match(TK_DIVISION)) {
            if (peek().getTtype() == TK_MULTIPLICATION) {
                advance();
                unary();
                this.instructions.add(makeOpCode(OP_MULTIPLY));
            } else if (peek().getTtype() == TK_DIVISION) {
                advance();
                unary();
                this.instructions.add(makeOpCode(OP_DIVIDE));
            }
        }
    }

    private void unary() {
        if (match(TK_MINUS)) {
            advance();
            unary();
            this.instructions.add(makeOpCode(OP_NEGATE));
        } else if (match(TK_NOT)) {
            advance();
            unary();
            this.instructions.add(makeOpCode(OP_NOT));
        } else {
            primary();
        }
    }

    private void primary() {
        if (match(TK_INTEGER) || match(TK_DOUBLE)) {
            this.instructions.add(makeOpCode(OP_CONSTANT));
            advance();
        } else if (match(TK_LPAR)) {
            advance();
            expression();
            look(TK_RPAR, "Expected Character: ')'", "Missing Character");
        } else {
            setErrors("Missing Expression", "Expression Expected", peek());
        }
    }

    private Instruction makeOpCode(ByteCode opcode) {
        if (opcode == OP_CONSTANT) {
            if (peek().getTtype() == TK_INTEGER) {
                this.values.add(Integer.parseInt(peek().getLiteral()));
            } else if (peek().getTtype() == TK_DOUBLE) {
                this.values.add(Double.parseDouble(peek().getLiteral()));
            }
            return new Instruction(OP_CONSTANT, this.values.size() - 1);
        } else {
            return new Instruction(opcode, null);
        }
    }

    private void setErrors(String etype, String message, Token token) {
        this.hasError = true;
        Error error = new Error(etype, message, token);
        this.errors.add(error);
    }

    private void look(TokenType token, String message, String errorType) {
        if (peek().getTtype() != token) {
            setErrors(errorType, message, peek());
        } else {
            advance();
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
