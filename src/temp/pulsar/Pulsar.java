package temp.pulsar;

import temp.lang.CommandsKt;
import temp.lang.SetUp;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.NoSuchFileException;
import java.nio.file.Paths;

public class Pulsar {
    public static SetUp conditions = new SetUp("", false, "0.0.6");

    public static void main(String[] args) {
        if (args.length == 0) {
            repl();
        } else if (args.length == 1) {
            CommandsKt.parseCommands(args[0].trim());
        } else if (args.length == 2) {
            CommandsKt.parseCommands(args[0].trim(), args[1].trim());
        } else {
            CommandsKt.error("Invalid Commands Given: Only 1 Or 2 Parameters Are Allowed But " + args.length + " Parameters Were Given");
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
            CommandsKt.error("The File Path '" + file + "' Was Not Found");
            return null;
        }
    }
}
