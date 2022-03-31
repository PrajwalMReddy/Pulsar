# Refactoring The Code

This is a temporary directory that holds the new code for Pulsar as I refactor it and add an Abstract Syntax Tree step in the parsing. I will move all these files to the main directory once my work here is done.

## temp.pulsar
This holds all the source code directly involved in the compiler pipeline.

## temp.lang
This holds code that isn't directly a part of the compilation pipeline but is nevertheless very important for the compiler.

## temp.ast
This holds all the Abstract Syntax Tree nodes that will be used by the Abstract Syntax Tree Class.

## temp.analysis
This holds all the classes that are used for the static analysis of the source code; for now this only includes the type checker.

## temp.util
This holds other classes that aren't strictly needed for compilation but are there for convenience.

## temp.primitives
This package is for the classes that refer to the primitive data types.