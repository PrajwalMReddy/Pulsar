package org.codepulsar.pulsar

var debug = false

fun help() {
    println("Usage: pulsar [command] [file]")
    println("Commands:")
    println("    -h     : Shows This Help Menu")
    println("    -i     : Interprets The Given File")
    println("    -c     : Compiles The Given File")
    println("    -d     : Displays Debug Information Including Generated Tokens and Bytecode Disassembly\n" +
            "             And Interprets The File")
}

fun error(message: String) {
    help()
    println(message)
}

fun parseCommands(command: String) {
    when (command) {
        "-h" -> help()
        else -> error("Invalid Command For One Argument: $command")
    }
}

fun parseCommands(command: String, file: String) {
    when (command) {
        "-h" -> help()
        "-i" -> Pulsar.interpretFile(file)
        "-c" -> Pulsar.compileFile(file)

        "-d" -> {
            debug()
            Pulsar.interpretFile(file)
        }

        else -> error("Invalid Command: $command")
    }
}

fun debug() {
    debug = true
}