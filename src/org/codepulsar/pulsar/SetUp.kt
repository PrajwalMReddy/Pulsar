package org.codepulsar.pulsar

import kotlin.system.exitProcess

var debug = false

fun help() {
    println("Usage: pulsar [execution mode] [file] [command]")
    println("Commands:")
    println("    -h     : Shows This Help Menu")
    println("    -i     : Interprets The Program")
    println("    -c     : Compiles The Program")
    println("    -d     : Displays Debug Information (Including Generated Tokens and Bytecode Disassembly)")
}

fun argumentError(message: String) {
    help()
    println(message)
}

fun setUp(exitCode: Int, message: String) {
    if (exitCode == 0)
    {
        help()
    } else {
        argumentError("\n" + message)
    }
    exitProcess(exitCode)
}

fun debug() {
    debug = true
}