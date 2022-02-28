package temp.pulsar;

import temp.ast.Expression;
import temp.lang.CompilerError;
import temp.lang.Instruction;
import temp.util.ASTPrinter;

import java.util.ArrayList;

public class ByteCodeCompiler {
    // Input Data
    private final String sourceCode;
    private Expression program; // TODO Also Change This Back To 'AST'

    // Output Data
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

        ASTPrinter.print(this.program);
        if (this.errors.hasError()) return instructions;

        return this.instructions;
    }

    public CompilerError getErrors() {
        return this.errors;
    }
}
