package org.codepulsar.pulsar;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Pulsar {
    public static void main(String[] args) {
        if (args.length == 0) {
            repl(); // TODO Implement REPL
        } else if (args.length == 1) {
            CommandsKt.parseCommands(args[0].trim());
        } else if (args.length == 2) {
            CommandsKt.parseCommands(args[0].trim(), args[1].trim());
        }
    }

    private static void repl() {
    }

    public static void interpretFile(String file) throws IOException {
        byte[] fileBytes = Files.readAllBytes(Paths.get(file));
        String stringFile = new String(fileBytes, Charset.defaultCharset());

        Interpreter interpreter = new Interpreter(stringFile);
        interpreter.interpret();
    }

    public static void compileFile(String file) throws IOException {
        byte[] fileBytes = Files.readAllBytes(Paths.get(file));
        String stringFile = new String(fileBytes, Charset.defaultCharset());

        Compiler compiler = new Compiler(stringFile);
        compiler.init();
    }
}