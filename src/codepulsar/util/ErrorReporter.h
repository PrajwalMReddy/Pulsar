#ifndef CODEPULSAR_ERRORREPORTER_H
#define CODEPULSAR_ERRORREPORTER_H

#include <iostream>
#include <sstream>
#include <vector>

#include "../lang/CompilerError.h"


namespace Pulsar {
    class ErrorReporter {
        public:
            static void report(CompilerError* errors, std::string sourceCode);

        private:
            static void reportErrors(CompilerError* errors, std::string sourceCode);
            static std::vector<std::string> splitString(std::string string);
            static std::string trimString(std::string string);
    };
}


#endif
