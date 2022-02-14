package temp.pulsar;

import temp.ast.Program;
import temp.lang.Token;

import java.util.ArrayList;

public class AST {
    private final String sourceCode;
    private ArrayList<Token> tokens;

    private final Program program;

    public AST(String sourceCode) {
        this.sourceCode = sourceCode;
        this.program = new Program();
    }

    public Program parse() {
        Lexer lexer = new Lexer(this.sourceCode);
        this.tokens = lexer.tokenize();

        return this.program;
    }
}
