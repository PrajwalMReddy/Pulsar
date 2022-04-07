package temp.primitives.types

import temp.primitives.Primitive

class PBoolean(var value: Boolean) : Primitive() {
    override fun negate(): Primitive {
        return PNone()
    }

    override fun not(): Primitive {
        return PBoolean(!this.value)
    }

    override fun toString(): String {
        return value.toString()
    }
}