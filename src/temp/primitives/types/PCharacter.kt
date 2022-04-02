package temp.primitives.types

import temp.primitives.Primitive

class PCharacter(var value: Char) : Primitive() {
    override fun toString(): String {
        return value.toString()
    }
}