package temp.pulsar;

import temp.lang.Token;

import java.util.ArrayList;

public class Lexer {
    private final String sourceCode;

    private final ArrayList<Token> tokens;

    public Lexer(String sourceCode) {
        this.sourceCode = sourceCode;
        this.tokens = new ArrayList<>();
    }

    public ArrayList<Token> tokenize() {
        return this.tokens;
    }
}
