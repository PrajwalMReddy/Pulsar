#ifndef CODEPULSAR_COMPILERERROR_H
#define CODEPULSAR_COMPILERERROR_H

#include <vector>
#include <string>

#include "Error.h"


namespace Pulsar {
    class CompilerError {
        public:
            CompilerError();
            Pulsar::Error addError(std::string errorType, std::string message, int line);
            bool hasError();
            int errorCount();
            std::vector<Pulsar::Error>* getErrors();

        private:
            std::vector<Pulsar::Error>* errors;
    };
}


#endif
