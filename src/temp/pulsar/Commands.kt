package temp.pulsar

import kotlin.system.exitProcess

fun help() {
    println("Usage: pulsar [command] [file]")
    println("Commands:")
    println("    -h     : Shows This Help Menu")
    println("    -v     : Displays The Current Version Number")
    println("    -i     : Interprets The Given File")
    println("    -c     : Compiles The Given File")
    println("    -d     : Displays Debug Information\n" +
            "             And Interprets The File\n")
}

fun error(message: String) {
    help()
    println(message)
    exitProcess(1)
}

fun parseCommands(command: String) {
    when (command) {
        "-h" -> help()
        "-v" -> version()
        else -> error("Invalid Command For One Argument: $command")
    }
}

fun parseCommands(command: String, file: String) {
    setUp(file)
    when (command) {
        "-h" -> help()
        "-i" -> Pulsar.interpretFile(file)
        "-c" -> Pulsar.compileFile(file)

        "-d" -> {
            debug()
            Pulsar.interpretFile(file)
        }

        else -> error("Invalid Command For Two Arguments: $command")
    }
}

// Set To Debug Mode
fun debug() {
    Pulsar.conditions.debug = true
}

// Displays The Current Version (Currently Hardcoded In Pulsar.java)
fun version() {
    println("Version: ${Pulsar.conditions.version}")
}

// Store The Name Of The Input File For Future Use
fun setUp(name: String) {
    Pulsar.conditions.fileIn = name.substring(0, name.lastIndexOf("."))
}