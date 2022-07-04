#ifndef CODEPULSAR_FUNCTION_H
#define CODEPULSAR_FUNCTION_H

#include <vector>
#include <string>

#include "../Statement.h"
#include "../../lang/Token.h"
#include "../../primitive/PrimitiveType.h"


namespace Pulsar {
    class Parameter {
        public:
            Parameter(std::string name, PrimitiveType type);

            std::string getName();
            PrimitiveType getType();

        private:
            std::string name;
            PrimitiveType type;
    };

    class Function: public Statement {
        public:
            Function(std::string name, PrimitiveType type, std::vector<Parameter*>* parameters, Block* statements, int line);
            std::any accept(StmtVisitor& visitor);

            std::string getName();
            PrimitiveType getType();
            std::vector<Parameter*>* getParameters();
            Block* getStatements();
            int getLine();

            int getArity();

        private:
            std::string name;
            PrimitiveType type;
            std::vector<Parameter*>* parameters;
            Block* statements;
            int line;
    };
}


#endif
