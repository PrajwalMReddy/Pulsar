# The Pulsar Syntax Guide
This syntax guide shows the different syntactic features of the latest version of Pulsar (Version 0.0.6). This is a relatively simple guide that only highlights the syntax of the language. Specialized docs will hopefully be added soon.

## Comments
```pulsar
// Single line comments are created using a double slash.
// Multiline comments are not supported (as of now).
```

## Operators
### Unary Operations
```pulsar
-a; // Unary Negation
!a; // Unary Not
```
### Binary Operations
```pulsar
a + b; // Binary Addition
a - b; // Binary Subtraction
a * b; // Binary Multiplication
a / b; // Binary Division
a % b; // Modulus
```
### Assignment Operations
```pulsar
a = b; // Regular Assignment
a += b; // Addition Assignment
a -= b; // Subtraction Assignment
a *= b; // Multiplication Assignment
a /= b; // Division Assignment
a %= b; // Modulus Assignment
```
### Comparison Operations
```pulsar
a > b; // Greater Than
a >= b; // Greater Than Equal To

a < b; // Less Than
a <= b; // Less Than Equal To

a == b; // Equal Comparison
a != b; // Not Equal Comparison
```
### Logical Operations
```pulsar
a && b; // Logical And
a || b; // Logical Or
```
As of now, bitwise operators have not been implemented. They may or may not be added in the future

## Print Statements
```pulsar
print 100;
```
Pulsar has a temporary print statement used for debugging. This will be replaced with a function in the standard library once implemented.

## Variables

```pulsar
var a: int; // Declares and initializes a (of type int) and sets it to null.
var b: boolean = true; // Declares and initializes b (of type boolean) and sets it to true.

a = 10; // Assigns the value 10 to the variable a.
```
The datatypes available for variables include boolean, char, double, and int.

## If/Else Statements
```pulsar
if a == b {
  print 200;
} else {
  print 404;
}
```
The parentheses around if statements are optional.

## While Loops
```pulsar
while i < 100 {
  print i;
  i += 1;
}
```
Once again, the parentheses around while loops are optional.
