package temp.pulsar;

import temp.lang.CompilerError;
import temp.lang.Token;
import temp.lang.TokenType;

import java.util.ArrayList;

import static temp.lang.TokenType.*;

public class Lexer {
    // Input Data
    private final String sourceCode;

    // Data To Help In Lexing
    private int start;
    private int current;
    private int line;

    // Output Data
    private final ArrayList<Token> tokens;
    private final CompilerError errors;

    public Lexer(String sourceCode) {
        this.sourceCode = sourceCode;
        this.tokens = new ArrayList<>();

        this.start = 0;
        this.current = 0;
        this.line = 1;

        this.errors = new CompilerError();
    }

    public ArrayList<Token> tokenize() {
        while (true) {
            Token toAdd = scanToken();
            this.tokens.add(toAdd);

            if (toAdd.getTokenType() == TK_EOF) {
                break;
            }
        }

        return this.tokens;
    }

    private Token scanToken() {
        skipWhitespace();
        this.start = this.current;

        if (isAtEnd()) {
            return makeToken(TK_EOF);
        }

        char now = advance();

        if (isAlpha(now)) {
            return identifier();
        } if (isDigit(now)) {
            return number();
        }
        
        return character(now);
    }

    private Token character(char now) {
        switch (now) {
            case '.':
                return makeToken(TK_DOT);
            case ',':
                return makeToken(TK_COMMA);
            case ':':
                if (peek() == ':') {
                    advance();
                    return makeToken(TK_DOUBLE_COLON);
                } else {
                    return makeToken(TK_COLON);
                }
            case ';':
                return makeToken(TK_SEMICOLON);
            case '?':
                return makeToken(TK_QMARK);
            case '(':
                return makeToken(TK_LPAR);
            case ')':
                return makeToken(TK_RPAR);
            case '{':
                return makeToken(TK_LBRACE);
            case '}':
                return makeToken(TK_RBRACE);
            case '\'':
                return charLiteral();

            case '!':
                if (peek() == '=') {
                    advance();
                    return makeToken(TK_NOT_EQUAL);
                } else {
                    return makeToken(TK_NOT);
                }
            case '+':
                if (peek() == '='){
                    advance();
                    return makeToken(TK_PLUS_EQUAL);
                } else {
                    return makeToken(TK_PLUS);
                }
            case '-':if (peek() == '='){
                    advance();
                    return makeToken(TK_MINUS_EQUAL);
                } else {
                    return makeToken(TK_MINUS);
                }
            case '*':
                if (peek() == '=') {
                    advance();
                    return makeToken(TK_MUL_EQUAL);
                } else {
                    return makeToken(TK_MULTIPLICATION);
                }
            case '/':
                if (peek() == '=') {
                    advance();
                    return makeToken(TK_DIV_EQUAL);
                } else {
                    return makeToken(TK_DIVISION);
                }
            case '%':
                if (peek() == '=') {
                    advance();
                    return makeToken(TK_MOD_EQUAL);
                } else {
                    return makeToken(TK_MODULUS);
                }

            case '=':
                if (peek() == '=') {
                    advance();
                    return makeToken(TK_EQUAL_EQUAL);
                } else {
                    return makeToken(TK_EQUAL);
                }
            case '>':
                if (peek() == '=') {
                    advance();
                    return makeToken(TK_GT_EQUAL);
                } else {
                    return makeToken(TK_GT);
                }
            case '<':
                if (peek() == '=') {
                    advance();
                    return makeToken(TK_LT_EQUAL);
                } else {
                    return makeToken(TK_LT);
                }
            case '|':
                if (peek() == '|') {
                    advance();
                    return makeToken(TK_LOGICAL_OR);
                } else {
                    return errorToken("Invalid Character: '" + now + "'. Perhaps You Meant Logical Or: ||");
                }
            case '&':
                if (peek() == '&') {
                    advance();
                    return makeToken(TK_LOGICAL_AND);
                } else {
                    return errorToken("Invalid Character: '" + now + "'. Perhaps You Meant Logical And: &&");
                }
        }

        return errorToken("Invalid Character: " + now);
    }

    private Token charLiteral() {
        while (peek() != '\'' && !isAtEnd()) {
            if (peek() == '\n') {
                this.line++;
            }

            advance();
        }

        if (isAtEnd()) {
            return errorToken("Char Literal Not Closed");
        }

        advance();

        if (currentLiteral().length() != 3) {
            return errorToken("The Length Of A Char Can Only Be 1");
        }

        return makeToken(TK_CHAR);
    }

    private Token identifier() {
        while (isAlpha(peek()) || isDigit(peek()))  {
            advance();
        }

        return makeToken(identifyIdentifier());
    }

    private TokenType identifyIdentifier() {
        return switch (this.sourceCode.charAt(this.start)) {
            case 'a' -> switch (this.sourceCode.charAt(this.start + 1)) {
                case 's' -> checkKeyword("ync", TK_ASYNC, 2);
                case 'w' -> checkKeyword("ait", TK_AWAIT, 2);
                default -> TK_IDENTIFIER;
            };
            case 'b' -> checkKeyword("reak", TK_BREAK, 1);
            case 'c' -> switch (this.sourceCode.charAt(this.start + 1)) {
                case 'l' -> checkKeyword("ass", TK_CLASS, 2);
                case 'o' -> switch (this.sourceCode.charAt(this.start + 3)) {
                    case 's' -> checkKeyword("t", TK_CONST, 4);
                    case 't' -> checkKeyword("inue", TK_CONTINUE, 4);
                    default -> TK_IDENTIFIER;
                };
                default -> TK_IDENTIFIER;
            };
            case 'e' -> switch (this.sourceCode.charAt(this.start + 1)) {
                case 'l' -> checkKeyword("se", TK_ELSE, 2);
                case 'n' -> checkKeyword("um", TK_ENUM, 2);
                case 'x' -> checkKeyword("cept", TK_EXCEPT, 2);
                default -> TK_IDENTIFIER;
            };
            case 'f' -> switch (this.sourceCode.charAt(this.start + 1)) {
                case 'u' -> checkKeyword("n", TK_FUN, 2);
                case 'a' -> checkKeyword("lse", TK_FALSE, 2);
                default -> TK_IDENTIFIER;
            };
            case 'i' -> switch (this.sourceCode.charAt(this.start + 1)) {
                case 'f' -> checkKeyword("", TK_IF, 2);
                case 'm' -> checkKeyword("port", TK_IMPORT, 2);
                default -> TK_IDENTIFIER;
            };
            case 'l' -> checkKeyword("oop", TK_LOOP, 1);
            case 'm' -> switch (this.sourceCode.charAt(this.start + 1)) {
                case 'o' -> checkKeyword("d", TK_MOD, 2);
                case 'a' -> checkKeyword("tch", TK_MATCH, 2);
                default -> TK_IDENTIFIER;
            };
            case 'n' -> switch (this.sourceCode.charAt(this.start + 1)) {
                case 'u' -> checkKeyword("ll", TK_NULL, 2);
                case 'a' -> checkKeyword("tive", TK_NATIVE, 2);
                default -> TK_IDENTIFIER;
            };
            case 'p' -> switch (this.sourceCode.charAt(this.start + 1)) {
                case 'a' -> checkKeyword("ckage", TK_PACKAGE, 2);
                case 'r' -> checkKeyword("int", TK_PRINT, 2);
                default -> TK_IDENTIFIER;
            };
            case 'r' -> checkKeyword("eturn", TK_RETURN, 1);
            case 't' -> switch (this.sourceCode.charAt(this.start + 2)) {
                case 'u' -> checkKeyword("e", TK_TRUE, 3);
                case 'y' -> checkKeyword("", TK_TRY, 3);
                default -> TK_IDENTIFIER;
            };
            case 'u' -> checkKeyword("nsafe", TK_UNSAFE, 1);
            case 'v' -> checkKeyword("ar", TK_VAR, 1);
            case 'w' -> checkKeyword("hile", TK_WHILE, 1);
            default -> TK_IDENTIFIER;
        };
    }

    private TokenType checkKeyword(String remaining, TokenType tokenType, int starter) {
        int length = remaining.length() + starter;
        String word = this.sourceCode.substring(start + starter, start + length);

        if (((this.current - this.start) == length) && (word.equals(remaining))) {
            return tokenType;
        }

        return TK_IDENTIFIER;
    }

    private Token number() {
        int dotCount = 0;

        while (isDigit(peek()) || peek() == '.') {
            if (peek() == '.') {
                dotCount++;
            }

            advance();
        }

        if (dotCount == 1 && !currentLiteral().endsWith(".")) {
            return makeToken(TK_DOUBLE);
        } else if (dotCount > 1) {
            return errorToken("Invalid Number Literal: " + currentLiteral());
        } else if (currentLiteral().endsWith(".")) {
            return errorToken("Invalid Number Literal: " + currentLiteral());
        }

        return makeToken(TK_INTEGER);
    }

    private void skipWhitespace() {
        while (true) {
            char next = peek();

            switch (next) {
                case ' ', '\r', '\t' -> advance();

                case '\n' -> {
                    this.line++;
                    advance();
                }

                case '/' -> {
                    if (peek(1) == '/') {
                        while (peek() != '\n' && !isAtEnd()) {
                            advance();
                        }
                    } else {
                        return;
                    }
                }

                default -> {
                    return;
                }
            }
        }
    }

    private boolean isAlpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    }

    private boolean isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    private Token makeToken(TokenType tokenType) {
        return new Token(tokenType, currentLiteral(), this.line);
    }

    private Token errorToken(String message) {
        Token errorToken = new Token(TK_ERROR, message, this.line);
        this.errors.addError("Tokenizing Error", message, errorToken.getLine());
        return errorToken;
    }

    private String currentLiteral() {
        return this.sourceCode.substring(this.start, this.current);
    }

    private char peek() {
        if (isAtEnd()) {
            return '\0';
        }
        return this.sourceCode.charAt(this.current);
    }

    private char peek(int skip) {
        if (isAtEnd()) {
            return '\0';
        }
        return this.sourceCode.charAt(this.current + skip);
    }

    private char advance() {
        this.current++;
        return this.sourceCode.charAt(this.current - 1);
    }

    private boolean isAtEnd() {
        return this.current >= this.sourceCode.length();
    }

    public CompilerError getErrors() {
        return this.errors;
    }
}
