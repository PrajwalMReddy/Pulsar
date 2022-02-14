package temp.pulsar;

import temp.lang.Instruction;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class Compiler {
    private final String sourceCode;
    private ArrayList<Instruction> instructions;

    private final PrintWriter pw;

    public Compiler(String sourceCode) throws FileNotFoundException {
        this.sourceCode = sourceCode;
        this.pw = new PrintWriter(Pulsar.conditions.getFileIn() + ".asm");
    }

    public void init() {
        ByteCodeCompiler bcc = new ByteCodeCompiler(this.sourceCode);
        this.instructions = bcc.compileByteCode();

        compile();
        this.pw.close();
    }

    private void compile() {
        this.pw.println("");
    }
}
