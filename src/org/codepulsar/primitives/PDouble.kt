package org.codepulsar.primitives

class PDouble(var value: Double) : Primitive() {

    override fun toString(): String {
        return value.toString()
    }
}