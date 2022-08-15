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

Pulsar::Primitive* Pulsar::PDouble::unaryNegate() {
    return new PDouble(-this->value);
}

Pulsar::Primitive* Pulsar::PDouble::unaryNot() {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PDouble::plus(Primitive* primitive) {
    return new PDouble(this->value + std::any_cast<double>(primitive->getPrimitiveValue()));
}

Pulsar::Primitive* Pulsar::PDouble::minus(Primitive* primitive) {
    return new PDouble(this->value - std::any_cast<double>(primitive->getPrimitiveValue()));
}

Pulsar::Primitive* Pulsar::PDouble::times(Primitive* primitive) {
    return new PDouble(this->value * std::any_cast<double>(primitive->getPrimitiveValue()));
}

Pulsar::Primitive* Pulsar::PDouble::div(Primitive* primitive) {
    return new PDouble(this->value / std::any_cast<double>(primitive->getPrimitiveValue()));
}

Pulsar::Primitive* Pulsar::PDouble::rem(Primitive* primitive) {
    return new PDouble(std::fmod(this->value, std::any_cast<double>(primitive->getPrimitiveValue())));
}

Pulsar::Primitive* Pulsar::PDouble::compareGreater(Primitive* primitive) {
    return new PDouble(this->value > std::any_cast<double>(primitive->getPrimitiveValue()));
}

Pulsar::Primitive* Pulsar::PDouble::compareLesser(Primitive* primitive) {
    return new PDouble(this->value < std::any_cast<double>(primitive->getPrimitiveValue()));
}

std::string Pulsar::PDouble::toString() {
    return std::to_string(this->value);
}
