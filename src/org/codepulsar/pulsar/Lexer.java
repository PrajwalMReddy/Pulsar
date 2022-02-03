package org.codepulsar.pulsar;

import java.util.ArrayList;
import static org.codepulsar.pulsar.TokenType.*;

public class Lexer {
    private final String sourceCode;
    private int start;
    private int current;
    private int line;

    private final ArrayList<Error> errors;
    public boolean hasErrors;

    public Lexer(String sourceCode) {
        this.sourceCode = sourceCode;
        this.start = 0;
        this.current = 0;
        this.line = 1;

        this.errors = new ArrayList<>();
        this.hasErrors = false;
    }

    public ArrayList<Token> tokenize() {
        ArrayList<Token> tokens = new ArrayList<>();

        while (true) {
            Token toAdd = scanToken();
            tokens.add(toAdd);

            if (toAdd.getTokenType() == TK_EOF) {
                break;
            }
        }

        return tokens;
    }

    private boolean isAlpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    }

    private boolean isDigit(char c) {
        return c >= '0' && c <= '9';
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
            case '"':
                return string();

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
                    return errorToken("Invalid Character: '" + now + "'. Perhaps You Meant Logical AND: &&");
                }
        }

        return errorToken("Invalid Character: " + now);
    }

    private Token string() {
        while (peek() != '"' && !isAtEnd()) {
            if (peek() == '\n') {
                this.line++;
            }

            advance();
        }

        if (isAtEnd()) {
            return errorToken("String Literal Not Closed");
        }

        advance();
        return makeToken(TK_STRING);
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
            return errorToken("Invalid Literal: " + currentLiteral());
        } else if (currentLiteral().endsWith(".")) {
            return errorToken("Invalid Literal: " + currentLiteral());
        }

        return makeToken(TK_INTEGER);
    }

    private Token makeToken(TokenType tokenType) {
        return new Token(tokenType, currentLiteral(), this.line);
    }

    private Token errorToken(String message) {
        this.hasErrors = true;

        Token errorToken = new Token(TK_ERROR, message, this.line);
        Error error = new Error("Tokenizing Error", message, errorToken);

        this.errors.add(error);
        return errorToken;
    }

    private void skipWhitespace() {
        while (true) {
            char next = peek();

            switch (next) {
                case ' ', '\r', '\t':
                    advance();
                    break;
                case '\n':
                    this.line++;
                    advance();
                    break;

                case '/':
                    if (peek(1) == '/') {
                        while (peek() != '\n' && !isAtEnd()) {
                            advance();
                        }
                    } else {
                        return;
                    }
                    break;

                default:
                    return;
            }
        }
    }

    public ArrayList<Error> getErrors() {
        return this.errors;
    }

    private String currentLiteral() {
        return this.sourceCode.substring(this.start, this.current);
    }

    private boolean isAtEnd() {
        return this.current >= this.sourceCode.length() - 1;
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
}
