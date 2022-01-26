package org.codepulsar.primitives

class PBoolean(var isValue: Boolean) : Primitive() {

    override fun toString(): String {
        return isValue.toString()
    }
}