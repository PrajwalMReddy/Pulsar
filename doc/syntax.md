# The Pulsar Syntax Guide
This syntax guide shows the different syntactic features of the latest version of Pulsar (Version 0.0.5). This is a relatively simple guide that only highlights the syntax of the language. Specialized docs will hopefully be added soon.
Semicolons are mandatory, for now. This is going to be removed soon.

## Comments
```rust
// Single line comments are created using a double slash.
// Multiline comments are not supported (as of now).
```

## Operators
### Unary Operations
```rust
-a; // Unary Negation
!a; // Unary Not
```
### Binary Operations
```rust
a + b; // Binary Addition
a - b; // Binary Subtraction
a * b; // Binary Multiplication
a / b; // Binary Division
a % b; // Modulus
```
### Comparison Operations
```rust
a > b; // Greater Than
a >= b; // Greater Than Equal To
a < b; // Less Than
a <= b; // Less Than Equal To

a == b; // Equal Comparison
a != b; // Not Equal Comparison
```
### Logical Operations
```rust
a && b; // Logical And
a || b; // Logical Or
```
As of now, bitwise operators have not been implemented. They may or may not be added in the future. Additionally, all the binary operators are available as assignment operators, in addition to the standard equals sign.

## Print Statements
```lox
print 100;
```
Pulsar has a temporary print statement used for debugging. This will be replaced with a function in the standard library once implemented.

## Variables

```kotlin
var a // Initializes a and sets it to null.

var a = 0 // Assigns the value 0 to the variable a.
```
Explicit type annotations will be added soon.

## If/Else Statements
```rust
if a == b {
  print 200;
} else {
  print 404;
}
```
The parentheses around if statements are optional.

## While Loops
```rust
while i < 100 {
  print i;
  i += 1;
}
```
Once again, the parentheses around while loops are optional.
