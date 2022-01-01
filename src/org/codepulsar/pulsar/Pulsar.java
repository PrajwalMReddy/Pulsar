package org.codepulsar.pulsar;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.NoSuchFileException;
import java.nio.file.Paths;

public class Pulsar {
    public static void main(String[] args) {
        if (args.length == 0) {
            repl(); // TODO Implement REPL
        } else if (args.length == 1) {
            CommandsKt.parseCommands(args[0].trim());
        } else if (args.length == 2) {
            CommandsKt.parseCommands(args[0].trim(), args[1].trim());
        } else {
            CommandsKt.error("Invalid Parameters Given; Only 1 or 2 Parameters Allowed");
        }
    }

    private static void repl() {
    }

    public static void interpretFile(String file) throws IOException {
        Interpreter interpreter = new Interpreter(openFile(file));
        interpreter.interpret();
    }

    public static void compileFile(String file) throws IOException {
        Compiler compiler = new Compiler(openFile(file));
        compiler.init();
    }

    private static String openFile(String file) throws IOException {
        String stringFile;
        try {
            byte[] fileBytes = Files.readAllBytes(Paths.get(file));
            stringFile = new String(fileBytes, Charset.defaultCharset());
            return stringFile;
        } catch (NoSuchFileException fileException) {
            CommandsKt.error("The File Path That Was Provided Was Not Found");
            return null;
        }
    }
}