package temp.primitives.types

import temp.primitives.Primitive

class PCharacter(var value: Char) : Primitive() {
    override fun negate(): Primitive {
        return PNone()
    }

    override fun not(): Primitive {
        return PNone()
    }

    override fun toString(): String {
        return value.toString()
    }
}