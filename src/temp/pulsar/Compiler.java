package temp.pulsar;

import java.io.FileNotFoundException;
import java.io.PrintWriter;

public class Compiler {
    private final String sourceCode;
    private PrintWriter pw;

    public Compiler(String sourceCode) {
        this.sourceCode = sourceCode;
    }

    public void init() throws FileNotFoundException {
        this.pw = new PrintWriter(Pulsar.conditions.getFileIn() + ".asm");
        compile();
        this.pw.close();
    }

    private void compile() {
        this.pw.println("");
    }
}
