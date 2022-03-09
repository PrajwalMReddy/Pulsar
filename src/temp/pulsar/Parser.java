package temp.pulsar;

import temp.ast.Expression;
import temp.ast.Statement;
import temp.ast.expression.*;
import temp.ast.statement.Block;
import temp.ast.statement.ExpressionStmt;
import temp.ast.statement.If;
import temp.ast.statement.While;
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
    private Statement program;
    private CompilerError errors;

    public Parser(String sourceCode) {
        this.sourceCode = sourceCode;

        this.current = 0;
    }

    public Statement parse() {
        Lexer lexer = new Lexer(this.sourceCode);
        this.tokens = lexer.tokenize();
        this.errors = lexer.getErrors();

        if (this.errors.hasError()) return this.program;
        TokenDisassembler.display(this.tokens);

        this.program = statement();
        
        return this.program;
    }

    private Statement statement() {
        while (!match(TK_EOF)) {
            if (matchAdvance(TK_IF)) {
                return ifStatement();
            } else if (matchAdvance(TK_WHILE)) {
                return whileStatement();
            } else {
                return expressionStatement();
            }
        }

        return null;
    }

    private Block block() {
        ArrayList<Statement> statements = new ArrayList<>();
        look(TK_LBRACE, "An Opening Brace Was Expected Before The Block");

        while (!match(TK_RBRACE) && !match(TK_EOF)) {
            statements.add(statement());
        }

        look(TK_RBRACE, "A Closing Brace Was Expected After The Block");
        return new Block(statements, peekLine());
    }

    private Statement whileStatement() {
        int line = peekLine();
        Expression expression = expression();
        Block statements = block();

        return new While(expression, statements, line);
    }

    private Statement ifStatement() {
        int line = peekLine();
        Expression expression = expression();
        Block thenBranch = block();
        Statement elseBranch = null;

        if (matchAdvance(TK_ELSE)) {
            if (matchAdvance(TK_IF)) {
                elseBranch = ifStatement();
            } else {
                elseBranch = block();
            }
        }

        return new If(expression, thenBranch, elseBranch, line);
    }

    private ExpressionStmt expressionStatement() {
        ExpressionStmt expression = new ExpressionStmt(expression(), peekLine());
        look(TK_SEMICOLON, "A Semicolon Was Expected After The Expression");
        return expression;
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
                    return new Assignment(next.getLiteral(), expression, next.getLine());
                }

                case TK_PLUS_EQUAL, TK_MINUS_EQUAL, TK_MUL_EQUAL, TK_DIV_EQUAL, TK_MOD_EQUAL -> {
                    Token next = peek();
                    String identifier = next.getLiteral();
                    int line = next.getLine();

                    advance();
                    Token operator = peek();
                    String operatorType = operator.getLiteral();
                    advance();

                    Expression expression = expression();

                    // Expand An Operator Assignment Into A Normal Assignment
                    return new Assignment(identifier,
                                    new Binary(
                                            new Variable(identifier, line
                                            ), operatorType.substring(0, operatorType.length() - 1), expression, line
                                    ), line
                            );
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
            expression = new Logical(expression, operator.getLiteral(), right, operator.getLine());
        }

        return expression;
    }

    private Expression logicalAnd() {
        Expression expression = equality();

        while (matchAdvance(TK_LOGICAL_AND)) {
            Token operator = previous();
            Expression right = equality();
            expression = new Logical(expression, operator.getLiteral(), right, operator.getLine());
        }

        return expression;
    }

    private Expression equality() {
        Expression expression = comparison();

        while (matchAdvance(TK_EQUAL_EQUAL, TK_NOT_EQUAL)) {
            Token operator = previous();
            Expression right = comparison();
            expression = new Binary(expression, operator.getLiteral(), right, operator.getLine());
        }

        return expression;
    }

    private Expression comparison() {
        Expression expression = term();

        while (matchAdvance(TK_GT, TK_GT_EQUAL, TK_LT, TK_LT_EQUAL)) {
            Token operator = previous();
            Expression right = term();
            expression = new Binary(expression, operator.getLiteral(), right, operator.getLine());
        }

        return expression;
    }

    private Expression term() {
        Expression expression = factor();

        while (matchAdvance(TK_PLUS, TK_MINUS)) {
            Token operator = previous();
            Expression right = factor();
            expression = new Binary(expression, operator.getLiteral(), right, operator.getLine());
        }

        return expression;
    }

    private Expression factor() {
        Expression expression = unary();

        while (matchAdvance(TK_MULTIPLICATION, TK_DIVISION)) {
            Token operator = previous();
            Expression right = unary();
            expression = new Binary(expression, operator.getLiteral(), right, operator.getLine());
        }

        return expression;
    }

    private Expression unary() {
        if (matchAdvance(TK_NOT, TK_MINUS)) {
            Token operator = previous();
            Expression right = unary();
            return new Unary(operator.getLiteral(), right, operator.getLine());
        } else if (matchAdvance(TK_PLUS)) {
            return unary();
        }

        return primary();
    }

    private Expression primary() {
        if (matchAdvance(TK_TRUE)) {
            return new Literal("true", TK_TRUE, peekLine());
        } else if (matchAdvance(TK_FALSE)) {
            return new Literal("false", TK_FALSE, peekLine());
        } else if (matchAdvance(TK_NULL)) {
            return new Literal("null", TK_NULL, peekLine());
        }

        if (matchAdvance(TK_INTEGER)) {
            return new Literal(previous().getLiteral(), TK_INTEGER, peekLine());
        } else if (matchAdvance(TK_DOUBLE)) {
            return new Literal(previous().getLiteral(), TK_DOUBLE, peekLine());
        } else if (matchAdvance(TK_CHAR)) {
            return new Literal(previous().getLiteral(), TK_CHAR, peekLine());
        }

        if (matchAdvance(TK_IDENTIFIER)) {
            return new Variable(previous().getLiteral(), peekLine());
        }

        if (matchAdvance(TK_LPAR)) {
            Expression expression = expression();
            look(TK_RPAR, "A Closing Parenthesis Was Expected");
            return new Grouping(expression);
        }

        error("An Expression Was Expected But Nothing Was Given", peekLine());
        return new Literal("Error", TK_ERROR, peekLine()); // Returning An 'Error Literal'
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
