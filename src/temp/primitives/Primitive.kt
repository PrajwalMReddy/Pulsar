package temp.primitives

abstract class Primitive {
    abstract fun getPrimitiveType(): PrimitiveType
    abstract fun getPrimitiveValue(): Any

    abstract fun negate(): Primitive
    abstract fun not(): Primitive

    abstract operator fun plus(primitive: Primitive): Primitive
    abstract operator fun minus(primitive: Primitive): Primitive
    abstract operator fun times(primitive: Primitive): Primitive
    abstract operator fun div(primitive: Primitive): Primitive
    abstract operator fun rem(primitive: Primitive): Primitive

    abstract fun compareGreater(primitive: Primitive): Primitive
    abstract fun compareLesser(primitive: Primitive): Primitive
}