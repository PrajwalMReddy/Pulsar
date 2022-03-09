package temp.primitives

class PCharacter(var value: Char) : Primitive() {
    override fun toString(): String {
        return value.toString()
    }
}