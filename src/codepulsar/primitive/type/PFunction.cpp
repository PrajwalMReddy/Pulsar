#include "PFunction.h"


Pulsar::PFunction::PFunction(std::string name) {
    this->name = name;
}

Pulsar::PrimitiveType Pulsar::PFunction::getPrimitiveType() {
    return PR_FUNCTION;
}

bool Pulsar::PFunction::isPrimitiveType(PrimitiveType primitiveType) {
    return primitiveType == PR_FUNCTION;
}

std::any Pulsar::PFunction::getPrimitiveValue() {
    return this->name;
}

Pulsar::Primitive* Pulsar::PFunction::unaryNegate() {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PFunction::unaryNot() {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PFunction::plus(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PFunction::minus(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PFunction::times(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PFunction::div(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PFunction::rem(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PFunction::compareGreater(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PFunction::compareLesser(Primitive* primitive) {
    return new PNone();
}

std::string Pulsar::PFunction::toString() {
    return this->name;
}
