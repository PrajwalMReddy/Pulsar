#include "PDouble.h"


Pulsar::PDouble::PDouble(double value) {
    this->value = value;
}

Pulsar::PrimitiveType Pulsar::PDouble::getPrimitiveType() {
    return PR_DOUBLE;
}

bool Pulsar::PDouble::isPrimitiveType(PrimitiveType primitiveType) {
    return primitiveType == PR_DOUBLE;
}

std::any Pulsar::PDouble::getPrimitiveValue() {
    return this->value;
}

std::any Pulsar::PDouble::unaryNegate() {
    return PDouble(-this->value);
}

std::any Pulsar::PDouble::unaryNot() {
    return PNone();
}

std::any Pulsar::PDouble::plus(std::any primitive) {
    return PDouble(this->value + std::any_cast<PDouble>(primitive).value);
}

std::any Pulsar::PDouble::minus(std::any primitive) {
    return PDouble(this->value - std::any_cast<PDouble>(primitive).value);
}

std::any Pulsar::PDouble::times(std::any primitive) {
    return PDouble(this->value * std::any_cast<PDouble>(primitive).value);
}

std::any Pulsar::PDouble::div(std::any primitive) {
    return PDouble(this->value / std::any_cast<PDouble>(primitive).value);
}

std::any Pulsar::PDouble::rem(std::any primitive) {
    return PDouble(std::fmod(this->value, std::any_cast<PDouble>(primitive).value));
}

std::any Pulsar::PDouble::compareGreater(std::any primitive) {
    return PDouble(this->value > std::any_cast<PDouble>(primitive).value);
}

std::any Pulsar::PDouble::compareLesser(std::any primitive) {
    return PDouble(this->value < std::any_cast<PDouble>(primitive).value);
}

std::string Pulsar::PDouble::toString() {
    return std::to_string(this->value);
}
