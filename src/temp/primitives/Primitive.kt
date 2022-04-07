package temp.primitives

abstract class Primitive {
    abstract fun negate(): Primitive
    abstract fun not(): Primitive
}