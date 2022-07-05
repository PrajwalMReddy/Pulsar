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
    return PNone();
}

std::any Pulsar::PNone::unaryNegate() {
    return PNone();
}

std::any Pulsar::PNone::unaryNot() {
    return PNone();
}

std::any Pulsar::PNone::plus(std::any primitive) {
    return PNone();
}

std::any Pulsar::PNone::minus(std::any primitive) {
    return PNone();
}

std::any Pulsar::PNone::times(std::any primitive) {
    return PNone();
}

std::any Pulsar::PNone::div(std::any primitive) {
    return PNone();
}

std::any Pulsar::PNone::rem(std::any primitive) {
    return PNone();
}

std::any Pulsar::PNone::compareGreater(std::any primitive) {
    return PNone();
}

std::any Pulsar::PNone::compareLesser(std::any primitive) {
    return PNone();
}

std::string Pulsar::PNone::toString() {
    return "¯\\_(ツ)_/¯";
}
