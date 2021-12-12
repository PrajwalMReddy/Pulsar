package org.codepulsar.pulsar;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Pulsar {
    public static void main(String[] args) throws IOException {
        if (args.length < 1) {
            // TODO Implement REPL
            repl();
        } else if (args.length == 1) {
            if (args[0].trim().equals("-h")) {
                SetUpKt.setUp(0, "");
            } else {
                SetUpKt.setUp(1, "Invalid Command For One Argument: " + args[0] + "\nTry pulsar -h For More");
            }
        } else {
            switch (args[0].trim()) {
                case "-i" ->
                        // TODO Implement Interpreter
                        interpretFile(args[1]);
                case "-c" ->
                        // TODO Implement Compiler
                        compileFile(args[1]);
                default -> SetUpKt.setUp(1, ("Invalid Command: " + args[0]));
            }
        }
    }

    private static void repl() {
    }

    private static void interpretFile(String file) throws IOException {
        byte[] fileBytes = Files.readAllBytes(Paths.get(file));
        String stringFile = new String(fileBytes, Charset.defaultCharset());

        Interpreter interpreter = new Interpreter(stringFile);
        interpreter.interpret();
    }

    private static void compileFile(String file) throws IOException {
        byte[] fileBytes = Files.readAllBytes(Paths.get(file));
        String stringFile = new String(fileBytes, Charset.defaultCharset());

        Compiler compiler = new Compiler(stringFile);
        compiler.start();
    }
}
