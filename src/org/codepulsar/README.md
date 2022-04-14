# Guide To The Source Code Directories (Version: 0.0.6)

This is the main directory that holds all the code for Pulsar.

## pulsar
This holds all the source code directly involved in the compiler pipeline.

## lang
This holds code that isn't directly a part of the compilation pipeline but is nevertheless very important for the compiler.

## ast
This holds all the Abstract Syntax Tree nodes that will be used while compiling.

## primitives
This package is for the classes that refer to the primitive data types.

## analysis
This holds all the classes that are used for the static analysis of the source code; for now this only includes the type checker.

## util
This holds other classes that aren't strictly needed for compilation but are there to provide diagnostic/extra information about the code and any problems present for debugging purposes.
