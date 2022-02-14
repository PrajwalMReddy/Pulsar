package temp.pulsar;

import temp.ast.Program;

import java.util.ArrayList;

public class AbstractSyntaxTree {
    private String sourceCode;
    private ArrayList<Token> tokens;
    private Program program;

    public AbstractSyntaxTree(String sourceCode) {
        this.sourceCode = sourceCode;
        this.tokens = new ArrayList<Token>();
        this.program = new Program();
    }

    public Program createTree() {
        Lexer lexer = new Lexer(this.sourceCode);
        this.tokens = lexer.tokenize();

        return this.program;
    }
}
