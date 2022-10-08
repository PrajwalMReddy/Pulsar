# Guide To The Source Code Directories (Version: 0.0.6)

This is the directory that holds the core code required for the Pulsar compiler and virtual machine.

## pulsar
This holds all the source code directly involved in the compiler pipeline. This includes the main function (located in Pulsar.cpp).

## lang
This holds code that isn't directly a part of the compilation pipeline but is nevertheless very important for the compiler.

## ast
This holds all the Abstract Syntax Tree nodes that are used while parsing. There are four child directories: one for the expression nodes, two for statement nodes, and one for other miscellaneous nodes.

## variable
This subdirectory holds all files required for handling variables, including functions, classes, and enums.

## primitive
This folder holds the code that is required for the built-in primitive types to work.

## analysis
This holds all the classes that are used for the static analysis of the source code; this includes the optimizer, type checker, and validator.

## util
This holds other classes that aren't strictly needed for compilation but are there to provide diagnostic/extra information about the code and any problems present for debugging purposes.
