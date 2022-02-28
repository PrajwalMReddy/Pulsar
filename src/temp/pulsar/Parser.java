package temp.pulsar;

import temp.ast.AST;
import temp.lang.CompilerError;
import temp.lang.Token;
import temp.lang.TokenType;
import temp.util.TokenDisassembler;

import java.util.ArrayList;

public class Parser {
    // Input Data
    private final String sourceCode;
    private ArrayList<Token> tokens;

    // Data To Help In Generating An AST
    private int current; // Next Token To Be Used

    // Output Data
    private final AST program;
    private CompilerError errors;

    public Parser(String sourceCode) {
        this.sourceCode = sourceCode;
        this.program = new AST();
        this.current = 0;
    }

    public AST parse() {
        Lexer lexer = new Lexer(this.sourceCode);
        this.tokens = lexer.tokenize();
        this.errors = lexer.getErrors();

        TokenDisassembler.display(this.tokens);

        expression();
        
        return this.program;
    }

    private void expression() {
        assignment();
    }

    private void assignment() {
        logicalOr();
    }

    private void logicalOr() {
        logicalAnd();
    }

    private void logicalAnd() {
        equality();
    }

    private void equality() {
        comparison();
    }

    private void comparison() {
        term();
    }

    private void term() {
        factor();
    }

    private void factor() {
        unary();
    }

    private void unary() {
        primary();
    }

    private void primary() {
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

    public CompilerError getErrors() {
        return this.errors;
    }
}
