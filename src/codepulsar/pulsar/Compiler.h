#ifndef CODEPULSAR_COMPILER_H
#define CODEPULSAR_COMPILER_H

#include <string>


namespace Pulsar {
    class Compiler {
        public:
            Compiler(std::string sourceCode);
            void init();

        private:
            std::string sourceCode;
    };
}


#endif
