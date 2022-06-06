#include "Parameter.h"


Pulsar::Parameter::Parameter(std::string name, Pulsar::Token type): type(type) {
    this->name = name;
}

std::string Pulsar::Parameter::getName() {
    return this->name;
}

Pulsar::Token Pulsar::Parameter::getType() {
    return this->type;
}
