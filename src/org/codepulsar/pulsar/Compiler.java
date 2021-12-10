package org.codepulsar.pulsar;

import java.util.ArrayList;

public class Compiler {
    private final String sourceCode;

    public Compiler(String sourceCode) {
        this.sourceCode = sourceCode;
    }

    public void compile() {
        Lexer lexer = new Lexer(this.sourceCode + "\n");
        ArrayList<Token> tokens = lexer.tokenize();

        System.out.println(tokens);
    }
}
