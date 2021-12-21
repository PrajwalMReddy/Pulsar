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
            declaration();
        }

        return this.instructions;
    }

    private void declaration() {
        if (match(TK_VAR, TK_CONST, TK_FUN)) {
            topLevelDeclaration();
        } else {
            statement();
        }
    }

    private void topLevelDeclaration() {
        if (matchAdvance(TK_VAR, TK_CONST)) {
            globalVariableDeclaration();
        } else if (matchAdvance(TK_FUN)) {
            functionDeclaration();
        }
    }

    private void globalVariableDeclaration() {
        String name = peekLiteral();
        advance();

        if (matchAdvance(TK_EQUAL)) {
            expression();
        } else {
            makeOpCode(OP_NULL, peekLine());
        }

        makeOpCode(OP_STORE_GLOBAL, name, peekLine());
        makeOpCode(OP_POP, peekLine());
        look(TK_SEMICOLON, "A Semicolon Was Expected After The Expression", "Missing Character");
    }

    private void functionDeclaration() {
        // TODO Finish Function Declarations
    }

    private void statement() {
        if (matchAdvance(TK_IF)) {
            ifStatement();
        } else if (matchAdvance(TK_WHILE)) {
            whileStatement();
        } else if (matchAdvance(TK_PRINT)) {
            printStatement();
        } else {
            expressionStatement();
        }
    }

    private void ifStatement() {
        expression();
        int ifOffset = makeJump(OP_JUMP_IF_FALSE);
        makeOpCode(OP_POP, peekLine());
        block();

        int elseOffset = makeJump(OP_JUMP);
        fixJump(ifOffset, OP_JUMP_IF_FALSE);
        makeOpCode(OP_POP, peekLine());

        if (matchAdvance(TK_ELSE)) {
            if (matchAdvance(TK_IF)) {
                ifStatement();
            } else {
                block();
            }
        }

        fixJump(elseOffset, OP_JUMP);
    }

    private void whileStatement() {
        int start = this.instructions.size();
        expression();

        int offset = makeJump(OP_JUMP_IF_FALSE);
        makeOpCode(OP_POP, peekLine());

        block();
        makeOpCode(OP_JUMP, start, peekLine());

        fixJump(offset, OP_JUMP_IF_FALSE);
        makeOpCode(OP_POP, peekLine());
    }

    private void block() {
        look(TK_LBRACE, "An Opening Brace Was Expected Before The Block", "Missing Character");
        while (!match(TK_RBRACE)) {
            statement();
        }
        look(TK_RBRACE, "A Closing Brace Was Expected Before The Block", "Missing Character");
    }

    private void printStatement() {
        expression();
        makeOpCode(OP_PRINT, peekLine());
        look(TK_SEMICOLON, "A Semicolon Was Expected After The Expression", "Missing Character");
    }

    private void expressionStatement() {
        expression();
        makeOpCode(OP_POP, peekLine());
        look(TK_SEMICOLON, "A Semicolon Was Expected After The Expression", "Missing Character");
    }

    private void expression() {
        assignment();
    }

    private void assignment() {
        if (peekType() == TK_IDENTIFIER && peekNext().getLiteral().contains("=")) {
            Token next = peekNext();

            String name = peekLiteral();
            advance();
            advance();
            expression();

            if (next.getLiteral().indexOf("=") > 0) {
                makeOpCode(OP_LOAD_GLOBAL, name, peekLine());
                if (next.getTtype() == TK_PLUSEQUAL) {
                    makeOpCode(OP_ADD, next.getLine());
                } else if (next.getTtype() == TK_MINUSEQUAL) {
                    makeOpCode(OP_SUBTRACT, next.getLine());
                } else if (next.getTtype() == TK_MULEQUAL) {
                    makeOpCode(OP_MULTIPLY, next.getLine());
                } else if (next.getTtype() == TK_DIVEQUAL) {
                    makeOpCode(OP_DIVIDE, next.getLine());
                }
            }

            makeOpCode(OP_STORE_GLOBAL, name, peekLine());
        } else {
            logicalOr();
        }
    }

    private void logicalOr() {
        logicalAnd();
        int offset;

        while (match(TK_LOGICALOR)) {
            if (peekType() == TK_LOGICALOR) {
                int line = peekLine();
                advance();
                offset = makeJump(OP_JUMP_IF_TRUE);
                makeOpCode(OP_POP, line);
                logicalAnd();
                fixJump(offset, OP_JUMP_IF_TRUE);
            }
        }
    }

    private void logicalAnd() {
        equality();
        int offset;

        while (match(TK_LOGICALAND)) {
            if (peekType() == TK_LOGICALAND) {
                int line = peekLine();
                advance();
                offset = makeJump(OP_JUMP_IF_FALSE);
                makeOpCode(OP_POP, line);
                equality();
                fixJump(offset, OP_JUMP_IF_FALSE);
            }
        }
    }

    private void equality() {
        comparison();

        while (match(TK_EQUALEQUAL, TK_NOTEQUAL)) {
            if (peekType() == TK_EQUALEQUAL) {
                advance();
                comparison();
                makeOpCode(OP_COMPARE_EQUAL, peekLine());
            } else if (peekType() == TK_NOTEQUAL) {
                advance();
                comparison();
                makeOpCode(OP_COMPARE_EQUAL, peekLine());
                makeOpCode(OP_NOT, peekLine());
            }
        }
    }

    private void comparison() {
        term();

        while (match(TK_GT, TK_GTEQUAL, TK_LT, TK_LTEQUAL)) {
            if (peekType() == TK_GT) {
                advance();
                term();
                makeOpCode(OP_GREATER, peekLine());
            } else if (peekType() == TK_LT) {
                advance();
                term();
                makeOpCode(OP_LESSER, peekLine());
            } else if (peekType() == TK_GTEQUAL) {
                advance();
                term();
                makeOpCode(OP_LESSER, peekLine());
                makeOpCode(OP_NOT, peekLine());
            } else if (peekType() == TK_LTEQUAL) {
                advance();
                term();
                makeOpCode(OP_GREATER, peekLine());
                makeOpCode(OP_NOT, peekLine());
            }
        }
    }

    private void term() {
        factor();

        while (match(TK_PLUS, TK_MINUS)) {
            if (peekType() == TK_PLUS) {
                advance();
                factor();
                makeOpCode(OP_ADD, peekLine());
            } else if (peekType() == TK_MINUS) {
                advance();
                factor();
                makeOpCode(OP_SUBTRACT, peekLine());
            }
        }
    }

    private void factor() {
        unary();

        while (match(TK_MULTIPLICATION, TK_DIVISION, TK_MODULUS)) {
            if (peekType() == TK_MULTIPLICATION) {
                advance();
                unary();
                makeOpCode(OP_MULTIPLY, peekLine());
            } else if (peekType() == TK_DIVISION) {
                advance();
                unary();
                makeOpCode(OP_DIVIDE, peekLine());
            } else if (peekType() == TK_MODULUS) {
                advance();
                unary();
                makeOpCode(OP_MODULO, peekLine());
            }
        }
    }

    private void unary() {
        if (matchAdvance(TK_NOT)) {
            unary();
            makeOpCode(OP_NOT, peekLine());
        } else if (matchAdvance(TK_MINUS)) {
            unary();
            makeOpCode(OP_NEGATE, peekLine());
        } else if (matchAdvance(TK_PLUS)) {
            unary();
        } else {
            primary();
        }
    }

    private void primary() {
        if (match(TK_INTEGER, TK_DOUBLE, TK_TRUE, TK_FALSE, TK_NULL)) {
            makeOpCode(OP_CONSTANT, peekLine());
            advance();
        } else if (match(TK_IDENTIFIER)) {
            makeOpCode(OP_LOAD_GLOBAL, peekLiteral(), peekLine());
            advance();
        } else if (matchAdvance(TK_LPAR)) {
            expression();
            look(TK_RPAR, "A Closing Parenthesis Was Expected Before The Block", "Missing Character");
        } else {
            setErrors("Missing Expression", "An Expression Was Expected But Nothing Was Given", peek());
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

    private int makeJump(ByteCode opcode) {
        int size = this.instructions.size();

        makeOpCode(opcode, peekLine());

        return size;
    }

    private void fixJump(int offset, ByteCode opcode) {
        Instruction oldJump = this.instructions.get(offset);
        int line = oldJump.getLine();
        Instruction jumpOpCode = new Instruction(opcode, this.instructions.size(), line);
        this.instructions.set(offset, jumpOpCode);
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

    private void look(TokenType token, String message, String errorType) {
        if (peek().getTtype() != token) {
            setErrors(errorType, message, peek());
            synchronize();
        } else {
            advance();
        }
    }

    private void synchronize() {
        while (peek().getTtype() != TK_EOF) {
            if (peek().getTtype() == TK_SEMICOLON) {
                advance();
                return;
            }

            advance();
        }
    }

    private void setErrors(String etype, String message, Token token) {
        this.hasErrors = true;
        Error error = new Error(etype, message, token);
        this.errors.add(error);
    }

    private Token peek() {
        return this.tokens.get(this.current);
    }

    private Token peekNext() {
        return this.tokens.get(this.current + 1);
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
