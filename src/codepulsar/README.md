# Guide To The Source Code Directories (Version: 0.0.6)

This is the directory that holds the core code required for the Pulsar compiler and virtual machine.

## pulsar
This holds all the source code directly involved in the compiler pipeline.

## lang
This holds code that isn't directly a part of the compilation pipeline but is nevertheless very important for the compiler.

## ast
This holds all the Abstract Syntax Tree nodes that are used while parsing. Furthermore, there are two child directories: one for the expression nodes and one for the statement nodes.

## primitive
This package holds the code that is required for the built-in primitive types to work.

## analysis
This holds all the classes that are used for the static analysis of the source code; for now this only includes the type checker and validator.

## util
This holds other classes that aren't strictly needed for compilation but are there to provide diagnostic/extra information about the code and any problems present for debugging purposes.
