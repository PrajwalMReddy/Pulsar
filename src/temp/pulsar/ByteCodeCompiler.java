package temp.pulsar;

import temp.ast.Program;

import java.util.ArrayList;

public class ByteCodeCompiler {
    private String sourceCode;
    private ArrayList<Instruction> instructions;
    private Program program;

    public ByteCodeCompiler(String sourceCode) {
        this.sourceCode = sourceCode;
        this.instructions = new ArrayList<>();
    }

    public ArrayList<Instruction> generate() {
        AbstractSyntaxTree ast = new AbstractSyntaxTree(this.sourceCode);
        this.program = ast.createTree();

        return this.instructions;
    }
}
