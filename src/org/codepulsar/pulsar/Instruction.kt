package org.codepulsar.pulsar

data class Instruction(val opcode: ByteCode, val operand: Int?, val line: Int)