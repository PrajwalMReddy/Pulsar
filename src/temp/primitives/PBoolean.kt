package temp.primitives

class PBoolean(var value: Boolean) : Primitive() {
    override fun toString(): String {
        return value.toString()
    }
}