package org.codepulsar.pulsar;

import java.util.ArrayList;

public class Parser {
    private String sourceCode;
    private ArrayList<Token> tokens;

    public Parser(String sourceCode) {
        this.sourceCode = sourceCode;
        this.tokens = new ArrayList<>();
    }

    public void parse() {
        Lexer lexer = new Lexer(this.sourceCode + "\n");
        this.tokens = lexer.tokenize();

        System.out.println(this.tokens);
    }
}
