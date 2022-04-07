package temp.primitives.types

import temp.primitives.Primitive

class PNull : Primitive() {
    override fun negate(): Primitive {
        return PNone()
    }

    override fun not(): Primitive {
        return PNone()
    }

    override fun toString(): String {
        return "null"
    }
}