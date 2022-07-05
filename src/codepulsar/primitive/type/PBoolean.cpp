#include "PBoolean.h"


Pulsar::PBoolean::PBoolean(bool value) {
    this->value = value;
}

Pulsar::PrimitiveType Pulsar::PBoolean::getPrimitiveType() {
    return PR_BOOLEAN;
}

bool Pulsar::PBoolean::isPrimitiveType(PrimitiveType primitiveType) {
    return primitiveType == PR_BOOLEAN;
}

std::any Pulsar::PBoolean::getPrimitiveValue() {
    return this->value;
}

std::any Pulsar::PBoolean::unaryNegate() {
    return PNone();
}

std::any Pulsar::PBoolean::unaryNot() {
    return PBoolean(!this->value);
}

std::any Pulsar::PBoolean::plus(std::any primitive) {
    return PNone();
}

std::any Pulsar::PBoolean::minus(std::any primitive) {
    return PNone();
}

std::any Pulsar::PBoolean::times(std::any primitive) {
    return PNone();
}

std::any Pulsar::PBoolean::div(std::any primitive) {
    return PNone();
}

std::any Pulsar::PBoolean::rem(std::any primitive) {
    return PNone();
}

std::any Pulsar::PBoolean::compareGreater(std::any primitive) {
    return PNone();
}

std::any Pulsar::PBoolean::compareLesser(std::any primitive) {
    return PNone();
}

std::string Pulsar::PBoolean::toString() {
    return std::to_string(this->value);
}
