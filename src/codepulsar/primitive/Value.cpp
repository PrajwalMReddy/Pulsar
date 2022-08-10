#include "Value.h"


Pulsar::Value::Value(std::any value, Pulsar::PrimitiveType type) {
    this->value = value;
    this->type = type;
}

std::any Pulsar::Value::getValue() {
    return this->value;
}

Pulsar::PrimitiveType Pulsar::Value::getType() {
    return this->type;
}
