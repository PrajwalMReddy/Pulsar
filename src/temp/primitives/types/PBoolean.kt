package temp.primitives.types

import temp.primitives.Primitive

class PBoolean(var value: Boolean) : Primitive() {
    override fun getPrimitiveValue(): Any {
        return this.value
    }

    override fun negate(): Primitive {
        return PNone()
    }

    override fun not(): Primitive {
        return PBoolean(!this.value)
    }

    override fun plus(primitive: Primitive): Primitive {
        return PNone()
    }

    override fun minus(primitive: Primitive): Primitive {
        return PNone()
    }

    override fun times(primitive: Primitive): Primitive {
        return PNone()
    }

    override fun div(primitive: Primitive): Primitive {
        return PNone()
    }

    override fun rem(primitive: Primitive): Primitive {
        return PNone()
    }

    override fun compareGreater(primitive: Primitive): Primitive {
        return PNone()
    }

    override fun compareLesser(primitive: Primitive): Primitive {
        return PNone()
    }

    override fun toString(): String {
        return value.toString()
    }
}