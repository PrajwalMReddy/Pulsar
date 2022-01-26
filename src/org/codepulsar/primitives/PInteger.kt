package org.codepulsar.primitives

class PInteger(var value: Int) : Primitive() {

    override fun toString(): String {
        return value.toString()
    }
}