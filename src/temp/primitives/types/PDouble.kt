package temp.primitives.types

import temp.primitives.Primitive

class PDouble(var value: Double) : Primitive() {
    override fun toString(): String {
        return value.toString()
    }
}