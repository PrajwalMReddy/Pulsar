#include "PNone.h"


Pulsar::PNone::PNone() {
}

Pulsar::PrimitiveType Pulsar::PNone::getPrimitiveType() {
    return PR_ERROR;
}

bool Pulsar::PNone::isPrimitiveType(PrimitiveType primitiveType) {
    return primitiveType == PR_ERROR;
}

std::any Pulsar::PNone::getPrimitiveValue() {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PNone::unaryNegate() {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PNone::unaryNot() {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PNone::plus(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PNone::minus(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PNone::times(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PNone::div(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PNone::rem(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PNone::compareGreater(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PNone::compareLesser(Primitive* primitive) {
    return new PNone();
}

std::string Pulsar::PNone::toString() {
    return "¯\\_(ツ)_/¯";
}
