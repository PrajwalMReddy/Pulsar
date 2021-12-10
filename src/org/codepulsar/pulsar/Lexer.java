package org.codepulsar.pulsar;

import java.util.ArrayList;
import static org.codepulsar.pulsar.TokenType.*;

public class Lexer {
    private final String sourceCode;
    private int start;
    private int current;
    private int line;

    public Lexer(String sourceCode) {
        this.sourceCode = sourceCode;
        this.start = 0;
        this.current = 0;
        this.line = 1;
    }

    public ArrayList<Token> tokenize() {
        ArrayList<Token> tokens = new ArrayList<>();

        while (true) {
            Token toAdd = scanToken();
            tokens.add(toAdd);

            if (toAdd.getTtype() == EOF) {
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
            return makeToken(EOF);
        }

        char now = advance();

        if (isAlpha(now)) {
            return identifier();
        } if (isDigit(now)) {
            return number();
        }

        return errorToken("Unknown Character: " + now);
    }

    private Token identifier() {
        while (isAlpha(peek()) || isDigit(peek()))  {
            advance();
        }

        return makeToken(identifyIdentifier());
    }

    private TokenType identifyIdentifier() {
        switch (this.sourceCode.charAt(this.start)) {
            case 'c':
                switch (this.sourceCode.charAt(this.start + 1)) {
                    case 'l':
                        return checkKeyword("ass", CLASS, 2);
                    case 'o':
                        return checkKeyword("nst", CONST, 2);
                    default:
                        return IDENTIFIER;
                }
            case 'e':
                return checkKeyword("lse", ELSE, 1);
            case 'f':
                return checkKeyword("un", FUN, 1);
            case 'i':
                return checkKeyword("f", IF, 1);
            case 'm':
                return checkKeyword("od", MOD, 1);
            case 'p':
                return checkKeyword("ackage", PACKAGE, 1);
            case 'r':
                return checkKeyword("eturn", RETURN, 1);
            case 'u':
                return checkKeyword("se", USE, 1);
            case 'v':
                return checkKeyword("ar", VAR, 1);
            case 'w':
                return checkKeyword("hile", WHILE, 1);
            default:
                return IDENTIFIER;
        }
    }

    private TokenType checkKeyword(String remaining, TokenType ttype, int starter) {
        int length = remaining.length() + starter;
        String word = this.sourceCode.substring(start + starter, start + length);

        if (((this.current - this.start) == length) && (word.equals(remaining))) {
            return ttype;
        }

        return IDENTIFIER;
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
            return makeToken(DOUBLE);
        } else if (dotCount > 1) {
            return errorToken("Invalid Literal: " + currentLiteral());
        } else if (currentLiteral().endsWith(".")) {
            return errorToken("Invalid Literal: " + currentLiteral());
        }

        return makeToken(INTEGER);
    }

    private Token makeToken(TokenType ttype) {
        return new Token(ttype, currentLiteral(), this.line);
    }

    private Token errorToken(String message) {
        return new Token(ERROR, message, this.line);
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
                    if (peek() == '/') {
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

    private char advance() {
        this.current++;
        return this.sourceCode.charAt(this.current - 1);
    }
}
