package org.codepulsar.pulsar

import kotlin.system.exitProcess

fun help() {
    println("Usage: pulsar [command] [file]")
    println("Commands:")
    println("    -h     : Shows This Help Menu")
    println("    -c     : Compiles The Program")
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