#include "SymbolTable.h"


Pulsar::SymbolTable::SymbolTable() {
    this->globalVariables = std::map<std::string, GlobalVariable>();
}

std::any Pulsar::SymbolTable::getGlobalValue(std::string name) {
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

void Pulsar::SymbolTable::addGlobalVariable(std::string name, std::any value, Pulsar::PrimitiveType type, bool isInitialized, bool isConstant) {
    this->globalVariables.insert({ name, GlobalVariable(value, type, isInitialized, isConstant) });
}

void Pulsar::SymbolTable::reassignGlobalVariable(std::string name, std::any value) {
    GlobalVariable variable = this->globalVariables.find(name)->second;
    this->globalVariables.insert_or_assign(name, GlobalVariable(value, variable.getType(), true, variable.isConstant()));
}

bool Pulsar::SymbolTable::containsGlobalVariable(std::string name) {
    return this->globalVariables.find(name) != this->globalVariables.end();
}
