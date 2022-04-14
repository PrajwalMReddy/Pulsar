package org.codepulsar.lang

data class Token(val tokenType: TokenType, val literal: String, val line: Int)
