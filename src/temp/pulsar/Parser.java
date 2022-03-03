package temp.pulsar;

import temp.ast.*;
import temp.ast.expression.*;
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
        if (peekType() == TK_IDENTIFIER) {
            switch (peekNext().getTokenType()) {
                case TK_EQUAL -> {
                    Token next = peek();

                    advance();
                    advance();

                    Expression expression = expression();
                    return new Assignment(next, expression);
                }

                case TK_PLUS_EQUAL, TK_MINUS_EQUAL, TK_MUL_EQUAL, TK_DIV_EQUAL, TK_MOD_EQUAL -> {
                    Token next = peek();

                    advance();
                    Token operator = peek();
                    advance();

                    Expression expression = expression();
                    return new OpAssignment(next, operator, expression);
                }

                default -> {
                    return logicalOr();
                }
            }
        }

        else {
            return logicalOr();
        }
    }

    private Expression logicalOr() {
        Expression expression = logicalAnd();

        while (matchAdvance(TK_LOGICAL_OR)) {
            Token operator = previous();
            Expression right = logicalAnd();
            expression = new Logical(expression, operator, right);
        }

        return expression;
    }

    private Expression logicalAnd() {
        Expression expression = equality();

        while (matchAdvance(TK_LOGICAL_AND)) {
            Token operator = previous();
            Expression right = equality();
            expression = new Logical(expression, operator, right);
        }

        return expression;
    }

    private Expression equality() {
        Expression expression = comparison();

        while (matchAdvance(TK_EQUAL_EQUAL, TK_NOT_EQUAL)) {
            Token operator = previous();
            Expression right = comparison();
            expression = new Binary(expression, operator, right);
        }

        return expression;
    }

    private Expression comparison() {
        Expression expression = term();

        while (matchAdvance(TK_GT, TK_GT_EQUAL, TK_LT, TK_LT_EQUAL)) {
            Token operator = previous();
            Expression right = term();
            expression = new Binary(expression, operator, right);
        }

        return expression;
    }

    private Expression term() {
        Expression expression = factor();

        while (matchAdvance(TK_PLUS, TK_MINUS)) {
            Token operator = previous();
            Expression right = factor();
            expression = new Binary(expression, operator, right);
        }

        return expression;
    }

    private Expression factor() {
        Expression expression = unary();

        while (matchAdvance(TK_MULTIPLICATION, TK_DIVISION)) {
            Token operator = previous();
            Expression right = unary();
            expression = new Binary(expression, operator, right);
        }

        return expression;
    }

    private Expression unary() {
        if (matchAdvance(TK_NOT, TK_MINUS)) {
            Token operator = previous();
            Expression right = unary();
            return new Unary(operator, right);
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

        if (matchAdvance(TK_INTEGER, TK_DOUBLE, TK_CHAR)) {
            return new Literal(previous().getLiteral());
        }

        if (matchAdvance(TK_IDENTIFIER)) {
            return new Variable(previous());
        }

        if (matchAdvance(TK_LPAR)) {
            Expression expression = expression();
            look(TK_RPAR, "A Closing Parenthesis Was Expected");
            return new Grouping(expression);
        }

        error("An Expression Was Expected But Nothing Was Given", peekLine());
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
