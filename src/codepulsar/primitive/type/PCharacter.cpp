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

Pulsar::Primitive* Pulsar::PCharacter::unaryNegate() {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PCharacter::unaryNot() {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PCharacter::plus(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PCharacter::minus(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PCharacter::times(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PCharacter::div(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PCharacter::rem(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PCharacter::compareGreater(Primitive* primitive) {
    return new PNone();
}

Pulsar::Primitive* Pulsar::PCharacter::compareLesser(Primitive* primitive) {
    return new PNone();
}

std::string Pulsar::PCharacter::toString() {
    return std::to_string(this->value);
}
