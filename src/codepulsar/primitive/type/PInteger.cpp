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

Pulsar::Primitive* Pulsar::PInteger::unaryNegate() {
    return new PInteger(-this->value);
}

Pulsar::Primitive* Pulsar::PInteger::unaryNot() {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PInteger::plus(Primitive* primitive) {
    return new PInteger(this->value + std::any_cast<int>(primitive->getPrimitiveValue()));
}

Pulsar::Primitive* Pulsar::PInteger::minus(Primitive* primitive) {
    return new PInteger(this->value - std::any_cast<int>(primitive->getPrimitiveValue()));
}

Pulsar::Primitive* Pulsar::PInteger::times(Primitive* primitive) {
    return new PInteger(this->value * std::any_cast<int>(primitive->getPrimitiveValue()));
}

Pulsar::Primitive* Pulsar::PInteger::div(Primitive* primitive) {
    return new PInteger(this->value / std::any_cast<int>(primitive->getPrimitiveValue()));
}

Pulsar::Primitive* Pulsar::PInteger::rem(Primitive* primitive) {
    return new PInteger(this->value % std::any_cast<int>(primitive->getPrimitiveValue()));
}

Pulsar::Primitive* Pulsar::PInteger::compareGreater(Primitive* primitive) {
    return new PBoolean(this->value > std::any_cast<int>(primitive->getPrimitiveValue()));
}

Pulsar::Primitive* Pulsar::PInteger::compareLesser(Primitive* primitive) {
    return new PBoolean(this->value < std::any_cast<int>(primitive->getPrimitiveValue()));
}

std::string Pulsar::PInteger::toString() {
    return std::to_string(this->value);
}
