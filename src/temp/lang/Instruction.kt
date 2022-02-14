package temp.lang

data class Instruction(val opcode: ByteCode, val operand: Any?, val line: Int)
