package temp.primitives.types

import temp.primitives.Primitive
import temp.primitives.PrimitiveType

class PInteger(var value: Int) : Primitive() {
    override fun getPrimitiveType(): PrimitiveType {
        return PrimitiveType.PR_INTEGER
    }

    override fun isPrimitiveType(primitiveType: PrimitiveType): Boolean {
        return primitiveType == PrimitiveType.PR_INTEGER
    }

    override fun getPrimitiveValue(): Any {
        return this.value
    }

    override fun negate(): Primitive {
        return PInteger(-this.value)
    }

    override fun not(): Primitive {
        return PNone()
    }

    override fun plus(primitive: Primitive): Primitive {
        return PInteger(this.value + (primitive as PInteger).value)
    }

    override fun minus(primitive: Primitive): Primitive {
        return PInteger(this.value - (primitive as PInteger).value)
    }

    override fun times(primitive: Primitive): Primitive {
        return PInteger(this.value * (primitive as PInteger).value)
    }

    override fun div(primitive: Primitive): Primitive {
        return PInteger(this.value / (primitive as PInteger).value)
    }

    override fun rem(primitive: Primitive): Primitive {
        return PInteger(this.value % (primitive as PInteger).value)
    }

    override fun compareGreater(primitive: Primitive): Primitive {
        return PBoolean(this.value > (primitive as PInteger).value)
    }

    override fun compareLesser(primitive: Primitive): Primitive {
        return PBoolean(this.value < (primitive as PInteger).value)
    }

    override fun toString(): String {
        return value.toString()
    }
}