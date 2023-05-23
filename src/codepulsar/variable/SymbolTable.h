#ifndef CODEPULSAR_SYMBOLTABLE_H
#define CODEPULSAR_SYMBOLTABLE_H

#include <string>
#include <vector>
#include <map>
#include <any>

#include "../primitive/PrimitiveType.h"
#include "GlobalVariable.h"
#include "LocalVariable.h"
#include "../lang/Token.h"
#include "../primitive/Primitive.h"
#include "FunctionVariable.h"


namespace Pulsar {
    class SymbolTable {
        public:
            SymbolTable();

            // Function Variable Core Functions
            void addFunction(std::string name, Function functionNode, int arity, PrimitiveType returnType);
            void setChunk(std::string name, std::vector<Instruction> chunk);
            std::map<std::string, FunctionVariable> getFunctions();

            // Global Variable Core Functions
            Primitive* getGlobalValue(std::string name);
            PrimitiveType getGlobalType(std::string name);
            bool isGlobalConstant(std::string name);
            bool isGlobalInitialized(std::string name);
            void setGlobalInitialized(std::string name);

            // Global Variable Extended Functions
            void addGlobalVariable(std::string name, Primitive* value, PrimitiveType type, bool isInitialized, bool isConstant);
            void reassignGlobalVariable(std::string name, Primitive* value);
            bool containsGlobalVariable(std::string name);

            // Local Variable Core Functions
            LocalVariable localAt(int i);
            PrimitiveType getLocalType(std::string name);
            bool isLocalConstant(std::string name);
            int getLocalDepth(std::string name);
            bool isLocalInitialized(std::string name);
            void setLocalInitialized(std::string name);

            // Local Variable Extended Functions
            void newLocal(std::string name, PrimitiveType type, bool isInitialized, bool isConstant, int depth);
            bool containsLocalVariable(std::string name);

            // Local Variable Helper Functions
            LocalVariable* getLocalVariable(std::string name);
            int getLocalCount();
            void decrementLocalCount();
            void incrementDepth();
            void decrementDepth();

        private:
            int scopeDepth;
            int localCount;

            std::map<std::string, FunctionVariable> functionVariable;
            std::map<std::string, GlobalVariable> globalVariables;
            std::vector<LocalVariable> localVariables;
    };
}


#endif
