package org.codepulsar.primitives

class PDouble(private val number: Double) : Primitive() {
    override fun toString(): String {
        return number.toString()
    }
}