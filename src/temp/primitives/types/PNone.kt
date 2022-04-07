package temp.primitives.types

import temp.primitives.Primitive

/*
    Used to implement a method that isn't applicable for that class.
*/

class PNone : Primitive() {
    override fun negate(): Primitive {
        return PNone()
    }

    override fun not(): Primitive {
        return PNone()
    }
}