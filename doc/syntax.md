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
a = b; // Assignment
a += b; // Addition Assignment
a -= b; // Subtraction Assignment
a *= b; // Multiplication Assignment
a /= b; // Division Assignment
a %= b; // Modulus Assignment
```
### Comparison Operations
```pulsar
a == b; // Equality Comparison
a != b; // Not Equal Comparison

a > b; // Greater Than
a >= b; // Greater Than Equal To

a < b; // Less Than
a <= b; // Less Than Equal To
```
### Logical Operations
```pulsar
a && b; // Logical And
a || b; // Logical Or
```
As of now, bitwise operators have not been implemented. They may be added in the future

## Print Statements
```pulsar
print 100;
```
Pulsar has a temporary print statement used for debugging. This will be replaced with a function in the standard library once implemented.

## Variables

```pulsar
var a: int; // Defines a (of type int) and leaves it uninitialized.
var b: boolean = true; // Declares and initializes b (of type boolean) and sets it to true.

a = 10; // Assigns the value 10 to the variable a.
```
The datatypes available for variables include int, double, boolean, and char.

## If/Else Statements
```pulsar
if a == b {
  print 200;
} else {
  print 404;
}
```
The parentheses around if statements are optional but the curly braces are not.

## While Loops
```pulsar
while i < 100 {
  print i;
  i += 1;
}
```
Once again, the parentheses around while loops are optional.

## Functions
```pulsar
// Function test takes in two integer arguments and returns and int.
fun test(a: int, b: int) -> int {
    if a > b {
        return a;
    } else {
        return b;
    }
}
```
The return type of the function is always written after the function parameter list, using an arrow. In addition to the datatypes available for variables, a function can have a return type of void.

### Function Calls
```pulsar
foo(); // A function with no arguments.
fib(10); // A function with a single argument.
addTwo(1, 2); // A function with more than one argument.
```
Arguments to a function call are separated by commas like the function parameter list.

### Return Statements
```pulsar
return true; // A return statement with a return value.
return; // A return statement with no return value, for void functions.
```
