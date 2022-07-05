#include "PCharacter.h"


Pulsar::PCharacter::PCharacter(char value) {
    this->value = value;
}

Pulsar::PrimitiveType Pulsar::PCharacter::getPrimitiveType() {
    return PR_CHARACTER;
}

bool Pulsar::PCharacter::isPrimitiveType(PrimitiveType primitiveType) {
    return primitiveType == PR_CHARACTER;
}

std::any Pulsar::PCharacter::getPrimitiveValue() {
    return this->value;
}

std::any Pulsar::PCharacter::unaryNegate() {
    return PNone();
}

std::any Pulsar::PCharacter::unaryNot() {
    return PCharacter(!this->value);
}

std::any Pulsar::PCharacter::plus(std::any primitive) {
    return PNone();
}

std::any Pulsar::PCharacter::minus(std::any primitive) {
    return PNone();
}

std::any Pulsar::PCharacter::times(std::any primitive) {
    return PNone();
}

std::any Pulsar::PCharacter::div(std::any primitive) {
    return PNone();
}

std::any Pulsar::PCharacter::rem(std::any primitive) {
    return PNone();
}

std::any Pulsar::PCharacter::compareGreater(std::any primitive) {
    return PNone();
}

std::any Pulsar::PCharacter::compareLesser(std::any primitive) {
    return PNone();
}

std::string Pulsar::PCharacter::toString() {
    return std::to_string(this->value);
}
