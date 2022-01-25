package org.codepulsar.pulsar;

import org.codepulsar.primitives.*;

import java.util.ArrayList;

import static org.codepulsar.pulsar.TokenType.*;
import static org.codepulsar.pulsar.ByteCode.*;

public class Parser {
    private final String sourceCode; // Original Source Code From User
    private ArrayList<Token> tokens; // Fully Tokenized Output From Lexer

    private final ArrayList<Instruction> instructions; // Instructions Produced From Parser
    public static ArrayList<Primitive> values; // Constant Values To Be Stored
    private int current; // Next Token To Be Used

    private int depth; // The Total Depth Of The Current Scope

    public final ArrayList<Error> errors; // Full List Of Errors To Be Reported
    boolean hasErrors; // Flag To Indicate If The Code Has Any Errors

    private LocalVariable locals;

    public Parser(String sourceCode) {
        this.sourceCode = sourceCode;
        this.tokens = new ArrayList<>();

        this.instructions = new ArrayList<>();
        values = new ArrayList<>();
        this.current = 0;

        this.depth = 1; // TODO Change Back To 0 When Functions Are Implemented

        this.errors = new ArrayList<>();
        this.hasErrors = false;

        this.locals = new LocalVariable();
    }

    public ArrayList<Instruction> parse() {
        Lexer lexer = new Lexer(this.sourceCode + "\n");
        this.tokens = lexer.tokenize();

        if (CommandsKt.getDebug()) {
            Disassembler.tokens(this.tokens);
        }

        start();

        return this.instructions;
    }

    private void start() {
        while (!match(TK_EOF)) {
            statement(); // TODO When Functions Are Implemented, Change This Back To 'declaration();'
        }
    }

    private void declaration() {
        if (matchAdvance(TK_VAR, TK_CONST)) {
            globalVariableDeclaration();
        } else if (matchAdvance(TK_FUN)) {
            functionDeclaration();
        } else {
            setErrors("Invalid Top Level Code", "Only Function And Global Variable Declarations Are " +
                    "Allowed At The Top Level", peek());
            synchronizeTopLevel();
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

        makeOpCode(OP_NEW_GLOBAL, name, peekLine());
        look(TK_SEMICOLON, "A Semicolon Was Expected After The Variable Declaration", "Missing Character");
    }

    private void functionDeclaration() {
        // TODO Finish Function Declarations
    }

    private void block() {
        startScope();
        look(TK_LBRACE, "An Opening Brace Was Expected Before The Block", "Missing Character");
        while (!match(TK_RBRACE) && !match(TK_EOF)) {
            statement();
        }
        look(TK_RBRACE, "A Closing Brace Was Expected Before The Block", "Missing Character");
        endScope();
    }

    private void startScope() {
        this.depth++;
        this.locals.scopeDepth++;
    }

    private void endScope() {
        this.depth--;
        this.locals.scopeDepth--;

        while (this.locals.localCount > 0 &&
                (this.locals.getLocal(this.locals.localCount - 1).depth > this.depth)) {
            makeOpCode(OP_POP, peekLine());
            this.locals.localCount--;
        }
    }

    private void statement() {
        if (matchAdvance(TK_IF)) {
            ifStatement();
        } else if (matchAdvance(TK_WHILE)) {
            whileStatement();
        } else if (matchAdvance(TK_PRINT)) {
            printStatement();
        } else if (matchAdvance(TK_VAR, TK_CONST)) {
            localVariableDeclaration();
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

    private void printStatement() {
        expression();
        makeOpCode(OP_PRINT, peekLine());
        look(TK_SEMICOLON, "A Semicolon Was Expected After The Print Statement", "Missing Character");
    }

    private void localVariableDeclaration() {
        Token localToken = peek();

        for (int i = this.locals.localCount - 1; i >= 0; i--) {
            LocalVariable.Local local = this.locals.getLocal(i);

            if (local.depth < this.depth) {
                break;
            }

            if (local.name.getLiteral().equals(localToken.getLiteral())) {
                setErrors("Variable Error",
                        "A Local Variable With This Name Already Exists - " + localToken.getLiteral(), peek());
            }
        }

        addLocal(localToken);

        advance();

        if (matchAdvance(TK_EQUAL)) {
            expression();
        } else {
            makeOpCode(OP_NULL, peekLine());
        }

        look(TK_SEMICOLON, "A Semicolon Was Expected After The Variable Declaration", "Missing Character");
    }

    private void addLocal(Token name) {
        this.locals.newLocal(name);
        this.locals.localCount++;
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
        if (peekType() == TK_IDENTIFIER && peekNext().getLiteral().contains("=")
                && peekNext().getTokenType() != TK_EQUAL_EQUAL
                && peekNext().getTokenType() != TK_NOT_EQUAL
                && peekNext().getTokenType() != TK_LT_EQUAL
                && peekNext().getTokenType() != TK_GT_EQUAL) {
            Token next = peekNext();
            Token localToken = peek();

            String name = peekLiteral();
            advance();
            advance();
            expression();

            if (next.getLiteral().indexOf("=") > 0) {
                if (inGlobalScope()) {
                    makeOpCode(OP_LOAD_GLOBAL, name, peekLine());
                } else {
                    makeOpCode(OP_GET_LOCAL, resolveLocal(localToken), peekLine());
                }
                if (next.getTokenType() == TK_PLUS_EQUAL) {
                    makeOpCode(OP_ADD, next.getLine());
                } else if (next.getTokenType() == TK_MINUS_EQUAL) {
                    makeOpCode(OP_SUBTRACT, next.getLine());
                } else if (next.getTokenType() == TK_MUL_EQUAL) {
                    makeOpCode(OP_MULTIPLY, next.getLine());
                } else if (next.getTokenType() == TK_DIV_EQUAL) {
                    makeOpCode(OP_DIVIDE, next.getLine());
                } else if (next.getTokenType() == TK_MOD_EQUAL) {
                    makeOpCode(OP_MODULO, next.getLine());
                }
            }

            if (inGlobalScope()) {
                makeOpCode(OP_STORE_GLOBAL, name, peekLine());
            } else {
                makeOpCode(OP_SET_LOCAL, resolveLocal(localToken), peekLine());
            }
        } else {
            logicalOr();
        }
    }

    private Object resolveLocal(Token name) {
        for (int i = this.locals.localCount - 1; i >= 0; i--) {
            LocalVariable.Local local = this.locals.getLocal(i);
            if (local.name.getLiteral().equals(name.getLiteral())) {
                return i;
            }
        }

        return -1;
    }

    private void logicalOr() {
        logicalAnd();
        int offset;

        while (match(TK_LOGICAL_OR)) {
            if (peekType() == TK_LOGICAL_OR) {
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

        while (match(TK_LOGICAL_AND)) {
            if (peekType() == TK_LOGICAL_AND) {
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

        while (match(TK_EQUAL_EQUAL, TK_NOT_EQUAL)) {
            if (peekType() == TK_EQUAL_EQUAL) {
                advance();
                comparison();
                makeOpCode(OP_COMPARE_EQUAL, peekLine());
            } else if (peekType() == TK_NOT_EQUAL) {
                advance();
                comparison();
                makeOpCode(OP_COMPARE_EQUAL, peekLine());
                makeOpCode(OP_NOT, peekLine());
            }
        }
    }

    private void comparison() {
        term();

        while (match(TK_GT, TK_GT_EQUAL, TK_LT, TK_LT_EQUAL)) {
            if (peekType() == TK_GT) {
                advance();
                term();
                makeOpCode(OP_COMPARE_GREATER, peekLine());
            } else if (peekType() == TK_LT) {
                advance();
                term();
                makeOpCode(OP_COMPARE_LESSER, peekLine());
            } else if (peekType() == TK_GT_EQUAL) {
                advance();
                term();
                makeOpCode(OP_COMPARE_LESSER, peekLine());
                makeOpCode(OP_NOT, peekLine());
            } else if (peekType() == TK_LT_EQUAL) {
                advance();
                term();
                makeOpCode(OP_COMPARE_GREATER, peekLine());
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
            if (inGlobalScope()) {
                makeOpCode(OP_LOAD_GLOBAL, peekLiteral(), peekLine());
            } else {
                makeOpCode(OP_GET_LOCAL, resolveLocal(peek()), peekLine());
            }
            advance();
        } else if (matchAdvance(TK_LPAR)) {
            expression();
            look(TK_RPAR, "A Closing Parenthesis Was Expected Before The Block",
                    "Missing Character");
        } else {
            setErrors("Missing Expression",
                    "An Expression Was Expected But Nothing Was Given", peek());
        }
    }

    private Instruction makeOpCode(ByteCode opcode, int line) {
        if (opcode == OP_CONSTANT) {
            Primitive primitiveLiteral = null;
            switch (peekType()) {
                case TK_INTEGER -> primitiveLiteral = new PInteger(Integer.parseInt(peekLiteral()));
                case TK_DOUBLE -> primitiveLiteral = new PDouble(Double.parseDouble(peekLiteral()));
                case TK_TRUE -> primitiveLiteral = new PBoolean(true);
                case TK_FALSE -> primitiveLiteral = new PBoolean(false);
                case TK_NULL -> primitiveLiteral = new PNull();
            }
            values.add(primitiveLiteral);
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

    private Instruction makeOpCode(Instruction instruction) {
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
        if (peek().getTokenType() != token) {
            setErrors(errorType, message, peek());
            synchronize();
        } else {
            advance();
        }
    }

    private void synchronize() {
        while (peekType() != TK_EOF) {
            if (peekType() == TK_SEMICOLON) {
                return;
            }

            switch (peekType()) {
                case TK_VAR, TK_CONST,
                        TK_IF, TK_WHILE, TK_PRINT -> { return; }
            }

            advance();
        }
    }

    private void synchronizeTopLevel() {
        while (peekType() != TK_EOF) {
            if (peekType() == TK_FUN) {
                return;
            }

            advance();
        }
    }

    private void setErrors(String errorType, String message, Token token) {
        this.hasErrors = true;
        Error error = new Error(errorType, message, token);
        this.errors.add(error);
    }

    public LocalVariable getLocals() {
        return this.locals;
    }

    private boolean inGlobalScope() {
        return this.depth == 0;
    }

    private Token peek() {
        return this.tokens.get(this.current);
    }

    private Token peekNext() {
        return this.tokens.get(this.current + 1);
    }

    private TokenType peekType() {
        return this.tokens.get(this.current).getTokenType();
    }

    private int peekLine() {
        return this.tokens.get(this.current).getLine();
    }

    private String peekLiteral() {
        return this.tokens.get(this.current).getLiteral();
    }
}
