package temp.primitives.types

import temp.primitives.Primitive

class PInteger(var value: Int) : Primitive() {
    override fun negate(): Primitive {
        return PInteger(-this.value)
    }

    override fun not(): Primitive {
        return PNone()
    }

    override fun toString(): String {
        return value.toString()
    }
}