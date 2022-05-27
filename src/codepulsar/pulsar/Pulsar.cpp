#include "Pulsar.h"

Pulsar::SetUp conditions = {"", false, "0.1.0"};


int main(int argc, char* argv[]) {
    if (argc == 1) {
        Pulsar::repl();
    } else if (argc == 2) {
        Pulsar::parseCommands(argv[1]);
    } else if (argc == 3) {
        Pulsar::parseCommands(argv[1], argv[2]);
    } else {
        Pulsar::error("Invalid Commands Given: Only 1 Or 2 Parameters Are Allowed But " + std::to_string(argc) + " Parameters Were Given");
    }
}

void Pulsar::repl() {
}

void Pulsar::interpretFile(std::string file) {
    Pulsar::Interpreter interpreter = Pulsar::Interpreter(openFile(file));
    interpreter.interpret();
}

void Pulsar::compileFile(std::string file) {
    Pulsar::Compiler compiler = Pulsar::Compiler(openFile(file));
    compiler.init();
}

std::string Pulsar::openFile(std::string fileIn) {
    std::ifstream file;
    file.open(fileIn);

    std::string stringOut;
    std::string temp;

    if (file.is_open()) {
        while (getline(file, temp)) stringOut += temp + "\n";
        return stringOut;
    } else {
        error("Could Not Read File " + fileIn);
        return "";
    }
}
