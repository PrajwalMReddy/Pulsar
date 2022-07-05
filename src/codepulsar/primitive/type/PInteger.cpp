#include "PInteger.h"


Pulsar::PInteger::PInteger(int value) {
    this->value = value;
}

Pulsar::PrimitiveType Pulsar::PInteger::getPrimitiveType() {
    return PR_INTEGER;
}

bool Pulsar::PInteger::isPrimitiveType(PrimitiveType primitiveType) {
    return primitiveType == PR_INTEGER;
}

std::any Pulsar::PInteger::getPrimitiveValue() {
    return this->value;
}

std::any Pulsar::PInteger::unaryNegate() {
    return PInteger(-this->value);
}

std::any Pulsar::PInteger::unaryNot() {
    return PNone();
}

std::any Pulsar::PInteger::plus(std::any primitive) {
    return PInteger(this->value + std::any_cast<PInteger>(primitive).value);
}

std::any Pulsar::PInteger::minus(std::any primitive) {
    return PInteger(this->value - std::any_cast<PInteger>(primitive).value);
}

std::any Pulsar::PInteger::times(std::any primitive) {
    return PInteger(this->value * std::any_cast<PInteger>(primitive).value);
}

std::any Pulsar::PInteger::div(std::any primitive) {
    return PInteger(this->value / std::any_cast<PInteger>(primitive).value);
}

std::any Pulsar::PInteger::rem(std::any primitive) {
    return PInteger(this->value % std::any_cast<PInteger>(primitive).value);
}

std::any Pulsar::PInteger::compareGreater(std::any primitive) {
    return PInteger(this->value > std::any_cast<PInteger>(primitive).value);
}

std::any Pulsar::PInteger::compareLesser(std::any primitive) {
    return PInteger(this->value < std::any_cast<PInteger>(primitive).value);
}

std::string Pulsar::PInteger::toString() {
    return std::to_string(this->value);
}
