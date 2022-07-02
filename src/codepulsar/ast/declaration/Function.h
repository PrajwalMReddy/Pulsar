#ifndef CODEPULSAR_FUNCTION_H
#define CODEPULSAR_FUNCTION_H

#include <vector>
#include <string>

#include "../Statement.h"
#include "../../variable/Parameter.h"
#include "../../lang/Token.h"
#include "../../primitive/PrimitiveType.h"


namespace Pulsar {
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
