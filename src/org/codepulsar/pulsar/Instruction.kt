package org.codepulsar.pulsar

data class Instruction(val opcode: ByteCode, val operand: Object?, val line: Int)