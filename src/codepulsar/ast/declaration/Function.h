#ifndef CODEPULSAR_FUNCTION_H
#define CODEPULSAR_FUNCTION_H

#include <vector>
#include <string>

#include "../Statement.h"
#include "../../variable/Parameter.h"
#include "../../lang/Token.h"


namespace Pulsar {
    class Function: public Statement {
        public:
            Function(std::string name, Token type, std::vector<Parameter*>* parameters, Block* statements, int line);
            template<typename R>
            R accept(StmtVisitor<R>& visitor);

            std::string getName();
            Token getType();
            std::vector<Parameter*>* getParameters();
            Block* getStatements();
            int getLine();

            int getArity();

        private:
            std::string name;
            Token type;
            std::vector<Parameter*>* parameters;
            Block* statements;
            int line;
    };
}


#endif
