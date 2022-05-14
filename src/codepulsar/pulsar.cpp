#include "pulsar.h"

SetUp setUpStruct = {"", false, "0.1.0"};

int main(int argc, char *argv[]) {
    if (argc == 1) {
        repl();
    } else if (argc == 2) {
        parseCommands(argv[1]);
    } else if (argc == 3) {
        parseCommands(argv[1], argv[2]);
    } else {
        error("Invalid Commands Given: Only 1 Or 2 Parameters Are Allowed But " + to_string(argc) + " Parameters Were Given");
    }
}

void repl() {
}

void interpretFile(string file) {
}

void compileFile(string file) {
}