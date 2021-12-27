package org.codepulsar.primitives

class PInteger(val number: Int) : Primitive() {
    override fun toString(): String {
        return number.toString()
    }
}
