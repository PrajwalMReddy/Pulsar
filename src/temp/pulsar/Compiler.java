package temp.pulsar;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class Compiler {
    private final String sourceCode;
    private ArrayList<Instruction> instructions;

    private PrintWriter pw;

    public Compiler(String sourceCode) throws FileNotFoundException {
        this.sourceCode = sourceCode;
        this.instructions = new ArrayList<>();
        this.pw = new PrintWriter(Pulsar.conditions.getFileIn() + ".asm");
    }

    public void init() {
        ByteCodeCompiler bcc = new ByteCodeCompiler(this.sourceCode);
        this.instructions = bcc.generate();

        compile();
        this.pw.close();
    }

    private void compile() {
        this.pw.println("");
    }
}
