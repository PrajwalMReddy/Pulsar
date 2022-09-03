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

Pulsar::Primitive* Pulsar::PBoolean::unaryNegate() {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PBoolean::unaryNot() {
    return new PBoolean(!this->value);
}

Pulsar::Primitive* Pulsar::PBoolean::plus(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PBoolean::minus(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PBoolean::times(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PBoolean::div(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PBoolean::rem(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PBoolean::compareGreater(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PBoolean::compareLesser(Primitive* primitive) {
    return new PNone();
}

std::string Pulsar::PBoolean::toString() {
    return this->value ? "true" : "false";
}
