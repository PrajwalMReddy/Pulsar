package temp.pulsar;

import temp.ast.expression.Unary;
import temp.lang.AST;
import temp.ast.Expression;
import temp.ast.expression.Grouping;
import temp.ast.expression.Literal;
import temp.lang.CompilerError;
import temp.lang.Token;
import temp.lang.TokenType;
import temp.util.TokenDisassembler;

import java.util.ArrayList;

import static temp.lang.TokenType.*;

public class Parser {
    // Input Data
    private final String sourceCode;
    private ArrayList<Token> tokens;

    // Data To Help In Generating An AST
    private int current; // Next Token To Be Used

    // Output Data
    private Expression program; // TODO Change Most 'Expression's To AST When Statements Are Added
    private CompilerError errors;

    public Parser(String sourceCode) {
        this.sourceCode = sourceCode;

        this.current = 0;

        this.program = new Expression();
    }

    public Expression parse() {
        Lexer lexer = new Lexer(this.sourceCode);
        this.tokens = lexer.tokenize();
        this.errors = lexer.getErrors();

        TokenDisassembler.display(this.tokens);
        if (this.errors.hasError()) return this.program;

        this.program = expression();
        
        return this.program;
    }

    private Expression expression() {
        return assignment();
    }

    private Expression assignment() {
        return logicalOr();
    }

    private Expression logicalOr() {
        return logicalAnd();
    }

    private Expression logicalAnd() {
        return equality();
    }

    private Expression equality() {
        return comparison();
    }

    private Expression comparison() {
        return term();
    }

    private Expression term() {
        return factor();
    }

    private Expression factor() {
        return unary();
    }

    private Expression unary() {
        if (matchAdvance(TK_NOT, TK_MINUS)) {
            return new Unary(previous(), unary());
        } else if (matchAdvance(TK_PLUS)) {
            return unary();
        }

        return primary();
    }

    private Expression primary() {
        if (matchAdvance(TK_TRUE)) {
            return new Literal(true);
        } else if (matchAdvance(TK_FALSE)) {
            return new Literal(false);
        } else if (matchAdvance(TK_NULL)) {
            return new Literal(null);
        }

        if (match(TK_INTEGER, TK_DOUBLE, TK_CHAR)) {
            return new Literal(peekLiteral());
        }

        if (matchAdvance(TK_LPAR)) {
            Expression expression = expression();
            look(TK_RPAR, "A Closing Parenthesis Was Expected");
            return new Grouping((Expression) expression);
        }

        error("An Expression Was Expected But None Given", peekLine());
        return new Literal(TK_ERROR); // Reusing The Error Token To Indicate That There Is No Value Here
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

    private void look(TokenType token, String message) {
        if (peekType() != token) {
            error(message, peekLine());
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
                        TK_IF, TK_WHILE, TK_PRINT,
                        TK_FUN -> {
                    return;
                }
            }

            advance();
        }
    }

    private Token previous() {
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

    private void error(String message, int line) {
        this.errors.addError("Parsing Error", message, line);
    }

    public CompilerError getErrors() {
        return this.errors;
    }
}
