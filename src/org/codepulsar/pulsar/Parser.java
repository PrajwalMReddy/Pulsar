package org.codepulsar.pulsar;

import org.codepulsar.ast.Expression;
import org.codepulsar.ast.Statement;
import org.codepulsar.ast.expressions.*;
import org.codepulsar.ast.statements.*;
import org.codepulsar.lang.CompilerError;
import org.codepulsar.lang.Token;
import org.codepulsar.lang.TokenType;
import org.codepulsar.lang.variables.GlobalVariable;
import org.codepulsar.lang.variables.LocalVariable;
import org.codepulsar.primitives.PrimitiveType;
import org.codepulsar.util.TokenDisassembler;

import java.util.ArrayList;

import static org.codepulsar.lang.TokenType.*;
import static org.codepulsar.primitives.PrimitiveType.*;

public class Parser {
    // Input Data
    private final String sourceCode;
    private ArrayList<Token> tokens;

    // Data To Help In Generating An AST
    private int current; // Next Token To Be Used
    private int depth;

    private final GlobalVariable globals;
    private final LocalVariable locals;

    // Output Data
    private Statement program;
    private CompilerError errors;

    public Parser(String sourceCode) {
        this.sourceCode = sourceCode;

        this.current = 0;
        this.depth = 1;

        this.globals = new GlobalVariable();
        this.locals = new LocalVariable();
    }

    public Statement parse() {
        Lexer lexer = new Lexer(this.sourceCode);
        this.tokens = lexer.tokenize();
        this.errors = lexer.getErrors();

        if (this.errors.hasError()) return this.program;
        TokenDisassembler.display(this.tokens);

        // TODO Temporary Code To Allow More Than One Top Level Declaration

        int line = peekLine();
        ArrayList<Statement> statements = new ArrayList<>();

        while (!match(TK_EOF)) {
            statements.add(lightDeclaration());
        }

        this.program = new Block(statements, line);
        return this.program;
    }

    private Statement lightDeclaration() {
        while (!match(TK_EOF)) {
            if (matchAdvance(TK_FUN)) {
                return functionDeclaration();
            } else if (matchAdvance(TK_VAR)) {
                return globalVariableDeclaration(TK_VAR);
            } else if (matchAdvance(TK_CONST)) {
                return globalVariableDeclaration(TK_CONST);
            } else {
                error("Only Global Variables And Functions Are Allowed At The Top Level", peekLine());
                end();
            }
        }

        return null;
    }

    private Statement functionDeclaration() {
        String name = advance().getLiteral();

        look(TK_LPAR, "An Opening Parenthesis Was Expected Before The Parameter List");
        ArrayList<Function.Parameter> parameters = new ArrayList<>();

        int arity = 0;
        if (peekType() != TK_RPAR) {
            do {
                String varName = advance().getLiteral();
                PrimitiveType varType = PR_ERROR;

                // TODO Validate That varType != PR_ERROR In The Validator
                if (!matchAdvance(TK_COLON)) {
                    error("A Colon Was Expected After The Variable Name", peekLine());
                } else {
                    if (!match(TK_DATA_TYPE)) {
                        error("A Datatype Was Expected For The Function's Parameters", peekLine());
                    } else {
                        varType = checkType(advance());
                    }
                }

                parameters.add(new Function.Parameter(varName, varType));
                arity++;
            } while (matchAdvance(TK_COMMA));
        }

        look(TK_RPAR, "A Closing Parenthesis Was Expected After The Parameter List");

        PrimitiveType type;
        if (matchAdvance(TK_COLON)) {
            TokenType next = peek().getTokenType();
            if (next != TK_DATA_TYPE && next != TK_VOID) {
                error("A Return Datatype For The Function Was Expected", peekLine());
                type = PR_ERROR;
            } else {
                type = checkType(advance());
            }
        } else {
            type = PR_VOID;
        }

        Block statements = block();
        return new Function(name, type, parameters, arity, statements, peekLine());
    }

    private Statement globalVariableDeclaration(TokenType accessType) {
        Token name = advance();

        if (name.getTokenType() != TK_IDENTIFIER) {
            error("Invalid Identifier Name", peekLine());
            synchronize();
            return new NoneStatement();
        }

        Expression expression;

        look(TK_COLON, "A Colon Was Expected After The Variable Name");
        Token type = advance();

        if (checkType(type) == PR_ERROR || checkType(type) == PR_VOID) {
            error("Invalid Type For Variable", peekLine());
        }

        boolean isInitialized;
        if (matchAdvance(TK_EQUAL)) {
            isInitialized = true;
            expression = expression();
        } else {
            isInitialized = false;
            expression = new Literal(null, PR_NULL, peekLine());
        }

        look(TK_SEMICOLON, "A Semicolon Was Expected After The Variable Declaration");

        if (this.globals.containsVariable(name.getLiteral())) {
            error("Global Variable '" + name.getLiteral() + "' Already Exists", name.getLine());
        }

        addGlobal(name, accessType, checkType(type), isInitialized);
        return new Variable(name.getLiteral(), expression, checkType(type), true, isInitialized, name.getLine());
    }

    private void addGlobal(Token name, TokenType accessType, PrimitiveType variableType, boolean isInitialized) {
        if (accessType == TK_VAR) {
            this.globals.addVariable(name.getLiteral(), null, variableType, isInitialized, false);
        } else if (accessType == TK_CONST) {
            this.globals.addVariable(name.getLiteral(), null, variableType, isInitialized, true);
        }
    }

    private Statement statement() {
        while (!match(TK_EOF)) {
            if (matchAdvance(TK_IF)) {
                return ifStatement();
            } else if (matchAdvance(TK_WHILE)) {
                return whileStatement();
            } else if (matchAdvance(TK_VAR)) {
                return localVariableDeclaration(TK_VAR);
            } else if (matchAdvance(TK_CONST)) {
                return localVariableDeclaration(TK_CONST);
            } else if (matchAdvance(TK_PRINT)) {
                return printStatement();
            } else {
                return expressionStatement();
            }
        }

        return null;
    }

    private Statement localVariableDeclaration(TokenType accessType) {
        Token localToken = advance();

        if (localToken.getTokenType() != TK_IDENTIFIER) {
            error("Invalid Identifier Name", peekLine());
            synchronize();
            return new NoneStatement();
        }

        Expression expression;

        look(TK_COLON, "A Colon Was Expected After The Variable Name");
        Token type = advance();

        if (checkType(type) == PR_ERROR || checkType(type) == PR_VOID) {
            error("Invalid Type For Variable", peekLine());
        }

        boolean isInitialized;
        if (matchAdvance(TK_EQUAL)) {
            isInitialized = true;
            expression = expression();
        } else {
            isInitialized = false;
            expression = new Literal(null, PR_NULL, peekLine());
        }

        look(TK_SEMICOLON, "A Semicolon Was Expected After The Variable Declaration");

        for (int i = this.locals.getLocalCount() - 1; i >= 0; i--) {
            LocalVariable.Local local = this.locals.getLocal(i);

            if (local.getDepth() < this.depth) {
                break;
            }

            if (local.getName().equals(localToken.getLiteral())) {
                error("Local Variable '" + localToken.getLiteral() + "' Already Exists", localToken.getLine());
            }
        }

        addLocal(localToken, accessType, checkType(type), isInitialized);
        return new Variable(localToken.getLiteral(), expression, checkType(type),false, isInitialized, localToken.getLine());
    }

    private void addLocal(Token name, TokenType accessType, PrimitiveType variableType, boolean isInitialized) {
        if (accessType == TK_VAR) {
            this.locals.newLocal(name, name.getLiteral(), variableType, isInitialized, false);
        } else if (accessType == TK_CONST) {
            this.locals.newLocal(name, name.getLiteral(), variableType, isInitialized, true);
        }
    }

    private PrimitiveType checkType(Token type) {
        return switch (type.getLiteral()) {
            case "boolean" -> PR_BOOLEAN;
            case "char" -> PR_CHARACTER;
            case "double" -> PR_DOUBLE;
            case "int" -> PR_INTEGER;
            case "void" -> PR_VOID;
            default -> PR_ERROR;
        };
    }

    private void startScope() {
        this.depth++;
        this.locals.incrementDepth();
    }

    private Block block() {
        ArrayList<Statement> statements = new ArrayList<>();
        startScope();
        look(TK_LBRACE, "An Opening Brace Was Expected Before The Block");

        while (!match(TK_RBRACE) && !match(TK_EOF)) {
            statements.add(statement());
        }

        look(TK_RBRACE, "A Closing Brace Was Expected After The Block");
        statements.add(endScope());
        return new Block(statements, peekLine());
    }

    private Statement endScope() {
        this.depth--;
        this.locals.decrementDepth();
        int localsToDelete = 0;


        while (this.locals.getLocalCount() > 0 &&
                (this.locals.getLocal(this.locals.getLocalCount() - 1).getDepth() > this.depth)) {
            localsToDelete++;
            this.locals.decrementLocalCount();
        }

        return new EndScope(localsToDelete, this.peekLine());
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

    private Statement printStatement() {
        Print statement = new Print(expression(), peekLine());
        look(TK_SEMICOLON, "A Semicolon Was Expected After The Print Statement");
        return statement;
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
            Token variable = peek();

            switch (peekNext().getTokenType()) {
                case TK_EQUAL -> {
                    Token next = peek();

                    advance();
                    advance();

                    Expression expression = expression();
                    return new Assignment(next.getLiteral(), (resolveLocal(next) == -1), resolveLocal(variable), expression, next.getLine());
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
                    return new Assignment(identifier, (resolveLocal(next) == -1), resolveLocal(variable),
                            new Binary(
                                        new VariableAccess(identifier, (resolveLocal(next) == -1), resolveLocal(variable), line
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

        while (matchAdvance(TK_MULTIPLICATION, TK_DIVISION, TK_MODULUS)) {
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
            return new Literal("true", PR_BOOLEAN, peekLine());
        } else if (matchAdvance(TK_FALSE)) {
            return new Literal("false", PR_BOOLEAN, peekLine());
        } else if (matchAdvance(TK_NULL)) {
            return new Literal("null", PR_NULL, peekLine());
        }

        if (matchAdvance(TK_INTEGER)) {
            return new Literal(previous().getLiteral(), PR_INTEGER, peekLine());
        } else if (matchAdvance(TK_DOUBLE)) {
            return new Literal(previous().getLiteral(), PR_DOUBLE, peekLine());
        } else if (matchAdvance(TK_CHARACTER)) {
            return new Literal(previous().getLiteral(), PR_CHARACTER, peekLine());
        }

        if (match(TK_IDENTIFIER)) {
            Token name = advance();
            return new VariableAccess(previous().getLiteral(), (resolveLocal(name) == -1), resolveLocal(name), peekLine());
        }

        if (matchAdvance(TK_LPAR)) {
            Expression expression = expression();
            look(TK_RPAR, "A Closing Parenthesis Was Expected");
            return new Grouping(expression);
        }

        error("An Expression Was Expected But Nothing Was Given", peekLine());
        return new NoneExpression();
    }

    private int resolveLocal(Token name) {
        for (int i = this.locals.getLocalCount() - 1; i >= 0; i--) {
            LocalVariable.Local local = this.locals.getLocal(i);

            if (local.getName().equals(name.getLiteral())) {
                return i;
            }
        }

        return -1;
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

    // Returns true if there's been a look ahead error.
    private boolean look(TokenType token, String message) {
        if (peekType() != token) {
            error(message, peekLine());
            synchronize();
            return true;
        } else {
            advance();
            return false;
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

    private void end() {
        while (!match(TK_EOF)) {
            advance();
        }
    }

    private boolean inGlobalScope() {
        return this.depth == 0;
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

    private void error(String message, int line) {
        this.errors.addError("Parsing Error", message, line);
    }

    public GlobalVariable getGlobals() {
        return this.globals;
    }

    public LocalVariable getLocals() {
        return this.locals;
    }

    public CompilerError getErrors() {
        return this.errors;
    }
}
