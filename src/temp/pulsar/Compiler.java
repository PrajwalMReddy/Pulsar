package temp.pulsar;

import temp.lang.CompilerError;
import temp.lang.Instruction;
import temp.util.ErrorReporter;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class Compiler {
    // Input Data
    private final String sourceCode;
    private ArrayList<Instruction> instructions;

    // Output Data
    private final PrintWriter pw;
    private CompilerError errors;

    public Compiler(String sourceCode) throws FileNotFoundException {
        this.sourceCode = sourceCode;
        this.pw = new PrintWriter(Pulsar.conditions.getFileIn() + ".asm");
    }

    public void init() {
        ByteCodeCompiler bcc = new ByteCodeCompiler(this.sourceCode);
        this.instructions = bcc.compileByteCode();
        this.errors = bcc.getErrors();

        ErrorReporter.report(this.errors, this.sourceCode);

        compile();
        this.pw.close();
    }

    private void compile() {
        this.pw.println("");
    }
}
