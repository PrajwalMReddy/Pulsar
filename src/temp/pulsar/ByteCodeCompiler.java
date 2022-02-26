package temp.pulsar;

import temp.ast.Program;
import temp.lang.Instruction;

import java.util.ArrayList;

public class ByteCodeCompiler {
    private final String sourceCode;
    private Program program;
    private final ArrayList<Instruction> instructions;

    public ByteCodeCompiler(String sourceCode) {
        this.sourceCode = sourceCode;
        this.instructions = new ArrayList<>();
    }

    public ArrayList<Instruction> compileByteCode() {
        AST ast = new AST(this.sourceCode);
        this.program = ast.parse();

        return this.instructions;
    }
}
