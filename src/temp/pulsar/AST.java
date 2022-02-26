package temp.pulsar;

import temp.ast.Program;
import temp.lang.CompilerError;
import temp.lang.Token;
import temp.util.TokenDisassembler;

import java.util.ArrayList;

public class AST {
    private final String sourceCode;
    private ArrayList<Token> tokens;
    private final Program program;

    private CompilerError errors;

    public AST(String sourceCode) {
        this.sourceCode = sourceCode;
        this.program = new Program();
    }

    public Program parse() {
        Lexer lexer = new Lexer(this.sourceCode);
        this.tokens = lexer.tokenize();
        this.errors = lexer.getErrors();

        TokenDisassembler.display(this.tokens);

        return this.program;
    }

    public CompilerError getErrors() {
        return this.errors;
    }
}
