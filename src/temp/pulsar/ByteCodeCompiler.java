package temp.pulsar;

import temp.ast.Program;
import temp.lang.CompilerError;
import temp.lang.Instruction;

import java.util.ArrayList;

public class ByteCodeCompiler {
    private final String sourceCode;
    private Program program;
    private final ArrayList<Instruction> instructions;

    private CompilerError errors;

    public ByteCodeCompiler(String sourceCode) {
        this.sourceCode = sourceCode;
        this.instructions = new ArrayList<>();
    }

    public ArrayList<Instruction> compileByteCode() {
        Parser ast = new Parser(this.sourceCode);
        this.program = ast.parse();
        this.errors = ast.getErrors();

        return this.instructions;
    }

    public CompilerError getErrors() {
        return this.errors;
    }
}
