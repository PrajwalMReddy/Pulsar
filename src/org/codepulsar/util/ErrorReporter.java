package org.codepulsar.util;

import org.codepulsar.lang.CompilerError;

public class ErrorReporter {
    public static void report(CompilerError errors, String code) {
        if (!errors.hasError()) {
            return;
        }

        System.out.println("\n-- Errors --\n");
        reportErrors(errors, code);
    }

    private static void reportErrors(CompilerError errors, String code) {
        String[] lines = code.split(System.getProperty("line.separator"));

        for (CompilerError.Error error: errors.getErrors()) {
            System.out.print(error.getErrorType() + " | ");
            System.out.println(error.getMessage());
            System.out.println("Line " + error.getLine() + ": " + lines[error.getLine() - 1].strip() + "\n");
        }

        System.exit(1);
    }
}
