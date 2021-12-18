package org.codepulsar.primitives

class PInteger(private val number: Int) : Primitive() {
    override fun toString(): String {
        return number.toString()
    }
}
