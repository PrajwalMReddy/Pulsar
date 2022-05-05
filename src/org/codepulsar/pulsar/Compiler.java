package org.codepulsar.pulsar;

import org.codepulsar.lang.CompilerError;
import org.codepulsar.lang.Instruction;
import org.codepulsar.lang.variables.FunctionVariable;
import org.codepulsar.lang.variables.GlobalVariable;
import org.codepulsar.lang.variables.LocalVariable;
import org.codepulsar.primitives.Primitive;
import org.codepulsar.util.Disassembler;
import org.codepulsar.util.ErrorReporter;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class Compiler {
    // Input Data
    private final String sourceCode;
    private ArrayList<Instruction> instructions;

    // Data To Help In Compiling To Assembly Code
    private FunctionVariable functions;
    private GlobalVariable globals;
    private LocalVariable locals;
    private ArrayList<Primitive> values;

    // Output Data
    private final PrintWriter pw;
    private CompilerError errors;
    private CompilerError staticErrors;

    public Compiler(String sourceCode) throws FileNotFoundException {
        this.sourceCode = sourceCode;

        this.pw = new PrintWriter(Pulsar.conditions.getFileIn() + ".asm");
    }

    public void init() {
        ByteCodeCompiler bcc = new ByteCodeCompiler(this.sourceCode);

        this.functions = bcc.getFunctions();
        this.globals = bcc.getGlobals();
        this.locals = bcc.getLocals();

        this.errors = bcc.getErrors();
        this.staticErrors = bcc.getStaticErrors();

        this.values = bcc.getValues();

        ErrorReporter.report(this.errors, this.sourceCode);
        ErrorReporter.report(this.staticErrors, this.sourceCode);

        Disassembler.disassemble(this.functions, bcc);

        compile();
        this.pw.close();
    }

    private void compile() {
        this.pw.println("");
    }
}
