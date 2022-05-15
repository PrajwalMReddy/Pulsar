#include "Pulsar.h"
#include "Interpreter.h"
#include "Compiler.h"


SetUp setUpConditions = {"", false, "0.1.0"};

int main(int argc, char* argv[]) {
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
    Interpreter* interpreter = new Interpreter(openFile(file));
    interpreter->interpret();
}

void compileFile(string file) {
    Compiler* compiler = new Compiler(openFile(file));
    compiler->init();
}

string openFile(string fileIn) {
    ifstream file;
    file.open(fileIn);

    string stringOut;
    string temp;

    if (file.is_open()) {
        while (getline(file, temp)) stringOut += temp + "\n";
        return stringOut;
    } else {
        error("Could Not Read File " + fileIn);
        return "";
    }
}
