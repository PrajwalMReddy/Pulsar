package org.codepulsar.primitives

class PDouble(val number: Double) : Primitive() {
    override fun toString(): String {
        return number.toString()
    }
}
