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


namespace Pulsar {
    class SymbolTable {
        public:
            SymbolTable();

            // Global Variable Core Functions
            std::any getGlobalValue(std::string name);
            PrimitiveType getGlobalType(std::string name);
            bool isGlobalConstant(std::string name);
            bool isGlobalInitialized(std::string name);
            void setGlobalInitialized(std::string name);

            // Global Variable Extended Functions
            void addGlobalVariable(std::string name, std::any value, PrimitiveType type, bool isInitialized, bool isConstant);
            void reassignGlobalVariable(std::string name, std::any value);
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
            LocalVariable getLocalVariable(std::string name);
            int getLocalCount();
            void decrementLocalCount();
            void incrementDepth();
            void decrementDepth();

        private:
            int scopeDepth;
            int localCount;

            std::map<std::string, GlobalVariable> globalVariables;
            std::vector<LocalVariable> localVariables;
    };
}


#endif
