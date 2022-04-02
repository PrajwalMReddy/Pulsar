package temp.primitives.types

import temp.primitives.Primitive

class PBoolean(var value: Boolean) : Primitive() {
    override fun toString(): String {
        return value.toString()
    }
}