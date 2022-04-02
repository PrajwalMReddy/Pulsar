package temp.primitives.types

import temp.primitives.Primitive

class PInteger(var value: Int) : Primitive() {
    override fun toString(): String {
        return value.toString()
    }
}