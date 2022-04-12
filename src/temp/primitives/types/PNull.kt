package temp.primitives.types

import temp.primitives.Primitive
import temp.primitives.PrimitiveType

class PNull : Primitive() {
    override fun getPrimitiveType(): PrimitiveType {
        return PrimitiveType.PR_NULL
    }

    override fun getPrimitiveValue(): Any {
        return PNull()
    }

    override fun negate(): Primitive {
        return PNone()
    }

    override fun not(): Primitive {
        return PNone()
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
        return "null"
    }
}