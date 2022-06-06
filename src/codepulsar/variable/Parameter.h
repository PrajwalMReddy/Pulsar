#ifndef CODEPULSAR_PARAMETER_H
#define CODEPULSAR_PARAMETER_H

#include <string>

#include "../lang/Token.h"


namespace Pulsar {
    class Parameter {
        public:
            Parameter(std::string name, Token type);

            std::string getName();
            Token getType();

        private:
            std::string name;
            Token type;
    };
}


#endif
