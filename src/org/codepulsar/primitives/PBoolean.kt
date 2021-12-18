package org.codepulsar.primitives

class PBoolean(private val value: Boolean) : Primitive() {
    override fun toString(): String {
        return value.toString()
    }
}
