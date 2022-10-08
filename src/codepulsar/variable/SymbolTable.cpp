#include "SymbolTable.h"


Pulsar::SymbolTable::SymbolTable() {
    this->scopeDepth = 0;
    this->localCount = 0;

    this->globalVariables = std::map<std::string, GlobalVariable>();
    this->localVariables = std::vector<LocalVariable>();
}

void Pulsar::SymbolTable::addFunction(std::string name, Function functionNode, int arity, PrimitiveType returnType) {
    this->functionVariable.insert({name, FunctionVariable(functionNode, arity, returnType)});
}

void Pulsar::SymbolTable::setChunk(std::string name, std::vector<Instruction> chunk) {
    this->functionVariable.find(name)->second.setChunk(chunk);
}

std::map<std::string, Pulsar::FunctionVariable> Pulsar::SymbolTable::getFunctions() {
    return this->functionVariable;
}

Pulsar::Primitive* Pulsar::SymbolTable::getGlobalValue(std::string name) {
    return this->globalVariables.find(name)->second.getValue();
}

Pulsar::PrimitiveType Pulsar::SymbolTable::getGlobalType(std::string name) {
    return this->globalVariables.find(name)->second.getType();
}

bool Pulsar::SymbolTable::isGlobalConstant(std::string name) {
    return this->globalVariables.find(name)->second.isConstant();
}

bool Pulsar::SymbolTable::isGlobalInitialized(std::string name) {
    return this->globalVariables.find(name)->second.isInitialized();
}

void Pulsar::SymbolTable::setGlobalInitialized(std::string name) {
    this->globalVariables.find(name)->second.setInitialized();
}

void Pulsar::SymbolTable::addGlobalVariable(std::string name, Primitive* value, Pulsar::PrimitiveType type, bool isInitialized, bool isConstant) {
    this->globalVariables.insert({ name, GlobalVariable(value, type, isInitialized, isConstant) });
}

void Pulsar::SymbolTable::reassignGlobalVariable(std::string name, Primitive* value) {
    GlobalVariable variable = this->globalVariables.find(name)->second;
    this->globalVariables.insert_or_assign(name, GlobalVariable(value, variable.getType(), true, variable.isConstant()));
}

bool Pulsar::SymbolTable::containsGlobalVariable(std::string name) {
    return this->globalVariables.find(name) != this->globalVariables.end();
}

Pulsar::LocalVariable Pulsar::SymbolTable::localAt(int i) {
    return this->localVariables[i];
}

Pulsar::PrimitiveType Pulsar::SymbolTable::getLocalType(std::string name) {
    return getLocalVariable(name).getType();
}

bool Pulsar::SymbolTable::isLocalConstant(std::string name) {
    return getLocalVariable(name).isConstant();
}

int Pulsar::SymbolTable::getLocalDepth(std::string name) {
    return getLocalVariable(name).getDepth();
}

bool Pulsar::SymbolTable::isLocalInitialized(std::string name) {
    return getLocalVariable(name).isInitialized();
}

void Pulsar::SymbolTable::setLocalInitialized(std::string name) {
    getLocalVariable(name).setInitialized();
}

void Pulsar::SymbolTable::newLocal(std::string name, Pulsar::PrimitiveType type, bool isInitialized, bool isConstant, int depth) {
    this->localVariables.emplace_back(name, type, isInitialized, isConstant, depth);
    this->localCount++;
}

bool Pulsar::SymbolTable::containsLocalVariable(std::string name) {
    for (int i = this->localCount - 1; i >= 0; i--) {
        LocalVariable local = this->localVariables[i];

        if (local.getDepth() < this->scopeDepth) break;
        if (local.getName() == name) return true;
    }

    return false;
}

Pulsar::LocalVariable Pulsar::SymbolTable::getLocalVariable(std::string name) {
    for (int i = 0; i < this->localCount; i++) {
        LocalVariable local = this->localVariables[i];

        if (local.getName() == name) {
            return local;
        }
    }

    return { "", PR_ERROR, false, true, -1 };
}

int Pulsar::SymbolTable::getLocalCount() {
    return this->localCount;
}

void Pulsar::SymbolTable::decrementLocalCount() {
    this->localCount--;
}

void Pulsar::SymbolTable::incrementDepth() {
    this->scopeDepth++;
}

void Pulsar::SymbolTable::decrementDepth() {
    this->scopeDepth--;
}
