package temp.util;

import temp.lang.Token;
import temp.lang.TokenType;
import temp.pulsar.Pulsar;

import java.util.ArrayList;
import java.util.Arrays;

import static temp.lang.TokenType.*;

public class TokenDisassembler {
    public static void display(ArrayList<Token> tokens) {
        if (Pulsar.conditions.getDebug()) {
            System.out.println("-- Tokens --");
            displayTokens(tokens);
        }
    }

    private static void displayTokens(ArrayList<Token> tokens) {
        TokenType[] literals = {TK_CHAR, TK_INTEGER, TK_DOUBLE, TK_IDENTIFIER};
        int line = 0;

        for (Token token: tokens) {
            if (token.getLine() == line) {
                System.out.print("            ");
            } else {
                line = token.getLine();
                System.out.print("\n" + line + space(line));
            }

            if (Arrays.asList(literals).contains(token.getTokenType())) {
                System.out.println(token.getTokenType() + space(token) + "(" + token.getLiteral() + ")");
            } else {
                System.out.println(token.getTokenType());
            }
        }
    }

    private static String space(int line) {
        int length = String.valueOf(line).length();
        return giveSpaces(length + 9);
    }

    private static String space(Token token) {
        int length = token.getTokenType().toString().length();
        return giveSpaces(length);
    }

    // Calculates How Many Spaces To Provide Based On The Length Of The Argument Passed In
    private static String giveSpaces(int length) {
        return " ".repeat(Math.max(0, 20 - length + 1));
    }
}
