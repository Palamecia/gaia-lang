# Gaïa Language Specification

## Introduction

### 1. Overview

Gaïa is a general-purpose programming language designed to modernize the programming paradigms and design principles established by C++.

Its primary objective is to provide a more consistent, accessible and predictable programming experience while preserving the expressive power, flexibility and fundamental capabilities that have made C++ a successful programming language.

Rather than introducing entirely new programming paradigms or imposing restrictive design choices, Gaïa builds upon established and proven concepts, revisiting their syntax, semantics and interactions to address historical inconsistencies and legacy design decisions.

### 2. Design Philosophy

Gaïa follows these fundamental principles:

Familiarity: Preserve established programming paradigms and concepts, minimizing unnecessary conceptual differences from C++.
Consistency: Provide coherent syntax and semantics across the language.
Predictability: Minimize surprising behavior and ensure that language constructs behave consistently.
Simplicity: Remove unnecessary syntactic complexity without sacrificing expressive power.
Flexibility: Preserve programmer freedom and low-level programming capabilities.
Interoperability: Support interoperability with existing C++ code and ecosystems.

### 3. Relationship with C++

Gaïa is inspired by C++ and shares many of its fundamental design principles, programming paradigms and capabilities.

However, Gaïa is an independent language with its own syntax and language specification.

Compatibility with C++ is not an unconditional requirement. Existing C++ concepts may be adapted, simplified or redesigned whenever doing so improves consistency, usability or predictability.

### 4. Interoperability

Gaïa aims to support interoperability with C++.

The initial interoperability model is unidirectional, allowing Gaïa programs to interact with existing C++ code.

The exact interoperability mechanisms, compatibility requirements and supported language features are defined in the relevant sections of this specification.

## Design Goals

Gaïa is designed around two primary objectives and one complementary objective.

### 1. Syntax Modernization

Gaïa aims to provide a modern, consistent and expressive syntax that improves both code readability and writing experience.

The language should minimize unnecessary verbosity, eliminate historical syntactic inconsistencies and favor constructs that are easy to understand and recognize.

Syntax modernization must not come at the expense of expressiveness or programming flexibility.

### 2. Behavioral Modernization

Gaïa aims to revisit established C++ mechanisms and behaviors to make them more practical, robust and predictable.

Existing concepts should be preserved whenever their underlying design remains relevant. However, their semantics may be revised to eliminate surprising behaviors, inconsistencies and unnecessary complexity.

Particular attention is given to type conversions, type promotions, memory management and interactions between language features.

### 3. Conceptual Evolution

Gaïa may introduce new concepts or unify existing ones whenever a genuine design need is identified.

New abstractions should solve concrete problems rather than introduce complexity for its own sake.

The introduction of new concepts must remain consistent with the fundamental philosophy of the language.

## Built-in Types and Literals

### 1. Built-in Types

Gaïa provides the following built-in primitive types:

- `Int8`, `Int16`, `Int32` and `Int64`: signed integer types.
- `UInt8`, `UInt16`, `UInt32` and `UInt64`: unsigned integer types.
- `Float32` and `Float64`: floating-point types.
- `Size`: a type used to represent memory sizes and offsets.
- `Byte`: a type representing an 8-bit unit.
- `CodeUnit8`, `CodeUnit16` and `CodeUnit32`: types representing individual code units.
- `Bool`: the Boolean type.
- `Null`: the type of the `null` value.

The platform-dependent `Int` and `UInt` names are not built-in types. They are provided by the standard library through macros that select an appropriate integer type for the target platform.

Gaïa does not define a separate `Void` type. The empty tuple type `()` is used to represent the absence of a return value. A function that does not return a value therefore has `()` as its return type.

Similarly, Gaïa does not define a built-in `Never` type. The `@no_return` annotation is used to indicate that a function never returns normally.

Numeric types follow the general implicit and explicit conversion rules defined by the language. Implicit conversions must preserve the value without loss of information.

### 2. Integer Literals

Integer literals may be written in decimal, binary, octal or hexadecimal notation.

The following prefixes select the corresponding base:

- No prefix: decimal.
- `0b`: binary.
- `0o`: octal.
- `0x`: hexadecimal.

Examples:

```gaia
42
0b101010
0o52
0x2A
```

Underscores may be used to separate digits for readability. An underscore must appear between two digits belonging to the same numeric sequence. It cannot appear at the beginning or end of a literal, immediately after a base prefix, next to a decimal point, or immediately after an exponent marker.

Examples:

```gaia
1_000_000
0b1010_1010
0o12_345
0xDEAD_BEEF
```

Prefixes and suffixes are case-insensitive. Lowercase prefixes and suffixes are used in this specification as the canonical notation.

An integer literal may have an explicit type suffix:

| Suffix | Type |
|---|---|
| `i8` | `Int8` |
| `i16` | `Int16` |
| `i32` | `Int32` |
| `i64` | `Int64` |
| `u8` | `UInt8` |
| `u16` | `UInt16` |
| `u32` | `UInt32` |
| `u64` | `UInt64` |
| `size` | `Size` |

When a suffix is present, the literal has the specified type. If its value cannot be represented by that type, compilation fails.

An integer literal without an explicit suffix has its type inferred from its value. The compiler selects the narrowest available integer type capable of representing that value:

- Positive values use unsigned integer types.
- Negative values use signed integer types.
- The available widths are 8, 16, 32 and 64 bits.

The minus sign immediately preceding an integer literal is considered when determining the literal's type. It is therefore possible to infer a signed type directly from a negative literal, rather than first inferring an unsigned type for its positive magnitude and then applying unary negation.

For example:

```gaia
let a = 42;       // UInt8
let b = 255;      // UInt8
let c = 256;      // UInt16

let d = -1;       // Int8
let e = -128;     // Int8
let f = -129;     // Int16
let g = -32768;   // Int16
```

This special treatment applies only when the minus sign is directly associated with the integer literal. Parentheses or an intervening expression cause the ordinary unary negation operator rules to apply.

For example:

```gaia
let a = -42;      // Negative integer literal: Int8
let b = -(42);    // Unary negation of a positive integer expression
let c = -value;   // Unary negation of an expression
```

If no available integer type can represent an unsuffixed literal, compilation fails.

### 3. Floating-Point Literals

Floating-point literals use decimal notation and may include an exponent.

Examples:

```gaia
1.5
0.25
1e10
1.5e-3
2.0E+8
```

A floating-point literal must contain at least one digit before the decimal point and, when a decimal point is present, at least one digit after it. Consequently, `.5` and `5.` are invalid; they must be written as `0.5` and `5.0`, respectively.

An exponent may be specified without a decimal point.

A floating-point literal may have one of the following suffixes:

- `f32`: the literal has type `Float32`.
- `f64`: the literal has type `Float64`.

Without an explicit suffix, a floating-point literal has type `Float64`.

The decimal representation of a floating-point literal is converted directly to its destination type. In particular, a literal suffixed with `f32` is converted directly to `Float32`, rather than being first converted to `Float64`.

Floating-point conversion uses rounding to the nearest representable value. If the conversion loses precision, the compiler emits the `numeric-floating-point-precision-loss` warning. This warning applies to both `Float32` and `Float64` literals and may be promoted to an error through the standard warning configuration mechanisms. It may also be locally suppressed using:

```gaia
@ignore(numeric-floating-point-precision-loss)
```

A floating-point literal whose value exceeds the representable range of its destination type is a compile-time error.

Underflow is reported separately from precision loss. When underflow occurs, the compiler emits an underflow warning and the resulting value is `0.0`.

`NaN` and `Infinity` are not special language literals. These values, as well as signed zero, are provided through the standard library.

### 4. Boolean Literals

The Boolean literals are:

- `true`
- `false`

Both literals have type `Bool`.

### 5. Character and String Literals

Character and string literals produce code units. They do not directly represent characters or string objects of a particular standard-library type.

The source file encoding determines the default encoding used for literals without an explicit encoding prefix:

- ASCII source files produce UTF-8 code units (`CodeUnit8`).
- UTF-8 source files produce UTF-8 code units (`CodeUnit8`).
- UTF-16 source files produce UTF-16 code units (`CodeUnit16`).
- UTF-32 source files produce UTF-32 code units (`CodeUnit32`).

ASCII is treated as a subset of UTF-8 and does not have a separate literal encoding prefix.

An explicit encoding prefix may be placed immediately before the opening delimiter:

- `u8`: UTF-8, producing `CodeUnit8` values.
- `u16`: UTF-16, producing `CodeUnit16` values.
- `u32`: UTF-32, producing `CodeUnit32` values.


For example:

```gaia
u8'a'
u16'é'
u32'€'

u8"Hello"
u16"Bonjour"
u32"こんにちは"
```

The compiler decodes the source text according to the source file encoding and transcodes the literal contents to the selected target encoding when necessary.

#### 5.1 Character Literals

A character literal is enclosed in single quotes:

```gaia
'a'
```

It represents exactly one code unit in the selected encoding.

Consequently, a character that requires multiple code units in the selected encoding cannot be represented by a character literal. For example, `'é'` is invalid in a UTF-8 source file because its UTF-8 representation requires two code units. The corresponding string literal must be used instead.

The same restriction applies to characters requiring a surrogate pair in UTF-16.

UTF-32 represents each valid Unicode code point using a single code unit.

#### 5.2 String Literals

An ordinary string literal is enclosed in double quotes:

```gaia
"Hello, world!"
```

A string literal produces a fixed-size array of code units terminated by a null code unit. Its array length includes the terminating code unit.

For example, in UTF-8:

```gaia
"abc"    // [4]CodeUnit8
""       // [1]CodeUnit8
```

The length of the resulting array is measured in code units, not in Unicode characters.

Ordinary string literals support the following escape sequences:

| Escape | Meaning |
|---|---|
| `\n` | Line feed |
| `\r` | Carriage return |
| `\t` | Horizontal tab |
| `\\` | Backslash |
| `\'` | Apostrophe |
| `\"` | Double quotation mark |
| `\0` | Null code unit |

An ordinary string literal may span multiple source lines. Source line breaks occurring inside the literal are ignored. All other characters, including indentation and whitespace, are preserved.

For example, the following source:

```gaia
"Hello
    World"
```

produces a string containing `Hello    World`, with no line break between the two words.

Numeric escapes allow a code unit to be specified by its numeric value:

- `\x{...}`: hexadecimal value.
- `\o{...}`: octal value.
- `\b{...}`: binary value.

Underscores may be used as digit separators inside these escapes, following the same rules as integer literals.

Examples:

```gaia
'\x{FF}'
'\o{377}'
'\b{1111_1111}'
```

Numeric escapes directly specify the value of a code unit. They are not interpreted as Unicode code points and are not transcoded to the selected encoding. The specified value must fit in the corresponding code unit type; otherwise, compilation fails.

For example, the UTF-8 encoding of `é` may be written explicitly as:

```gaia
"\x{C3}\x{A9}"
```

The `\0` escape may be used within the contents of a string. The compiler still appends the final null terminator after all literal contents, independently of any null code units explicitly present in the string.

#### 5.3 Raw String Literals

Raw string literals preserve their contents literally. Escape sequences are not interpreted, and source line breaks and whitespace are preserved.

A raw string literal uses at least three consecutive double quotes as its delimiter:

```gaia
"""Raw string content"""
```

The opening and closing delimiters must contain the same number of consecutive double quotes. The delimiter may contain more than three quotes when necessary to include sequences of double quotes in the contents.

Raw string literals have two forms.

A single-line raw string literal places its contents between the opening and closing delimiters.

A multiline raw string literal begins with an opening delimiter immediately followed by a source line break. Its closing delimiter must be preceded by a source line break and must appear at the beginning of a source line, without indentation.

The line breaks immediately following the opening delimiter and preceding the closing delimiter are part of the delimiters and are not included in the resulting string. No other indentation or whitespace is removed.

For example:

```gaia
let message = """
    Hello
    World
""";
```

The resulting string contains:

```text
    Hello
    World
```

The indentation before `Hello` and `World` is preserved.

Raw string literals follow the same encoding, prefix, array-size and null-termination rules as ordinary string literals.

### 6. Array Literals

Array literals may specify their element type explicitly or rely on type inference.

Examples:

```gaia
[0, 1, 2]
Int32 [0, 1, 2]
```

The resulting array has a fixed number of elements, determined by the number of entries in the literal.

#### 6.1 Explicit Element Type

When an element type is explicitly specified, every element must be implicitly convertible to that type.

Each element is converted to the specified type when the array is constructed. If any element cannot be implicitly converted, compilation fails.

These conversions follow the general implicit conversion rules of the language, including conversions provided by user-defined conversion functions.

#### 6.2 Inferred Element Type

When no element type is specified, the compiler infers a common element type by examining the elements from left to right.

The type of the first element becomes the initial inferred type. Each subsequent element is then compared with the current inferred type.

For two distinct types, the following rules apply:

- If the new element's type is implicitly convertible to the current inferred type, the current inferred type is retained.
- If the current inferred type is implicitly convertible to the new element's type, the new element's type becomes the inferred type.
- If both conversions are possible, the inference is ambiguous and compilation fails.
- If neither conversion is possible, no common type can be inferred and compilation fails.

If the two types are identical, the inferred type remains unchanged.

The implicit conversion relation is transitive. Therefore, when the inferred type is promoted to a new type, all previously examined element types remain convertible to the new inferred type.

An empty array literal has no element from which a type can be inferred. Its element type must therefore always be specified explicitly.

#### 6.3 Nested Array Literals

Type inference is recursive. When an array literal contains other array literals, the type of each nested array is inferred independently using the same rules. The inferred types of these nested arrays are then used to infer the element type of the enclosing array.

This allows promotions to occur recursively through nested array types, provided that the corresponding implicit conversions are valid.

#### 6.4 Type Inference and Array Construction

Array literal processing consists of two distinct phases.

**Type inference** takes place entirely at compile time. The compiler determines the final array type by examining the types of its elements and applying the implicit conversion rules. This phase does not evaluate the elements or execute conversion functions.

**Array construction** takes place at runtime. Once the final type has been determined, the elements are inserted into the array, converting them to the inferred or explicitly specified element type when necessary.

The conversions performed during construction are exactly those permitted by the general implicit conversion rules, including conversions implemented by user-defined conversion functions.

Elements are inserted in source order, from the beginning of the array to the end. This ordering also applies recursively to nested arrays: each nested array is constructed, including its own element conversions, before construction proceeds to the next element of the enclosing array.

## Variable Declarations

### 1. Declaration Syntax

Variables are declared using the `let` keyword.

The general syntax is:

```gaia
let [mut] identifier [: Type] = expression;
```

The type annotation is optional.

### 2. Immutability

Variables declared using `let` are immutable.

Once initialized, a variable cannot be assigned a new value.

```gaia
let a: Int32 = 42;

// Invalid: cannot assign to an immutable variable
a = 10;
```

Immutability applies to the variable itself and does not necessarily imply deep immutability of the object it references.

### 3. Mutable Variables

The `mut` keyword explicitly declares a mutable variable.

Mutable variables may be assigned new values after initialization.

```gaia
let mut counter: Int32 = 0;

counter = counter + 1;
```

### 4. Type Inference

When no explicit type annotation is provided, the compiler infers the variable's type from its initializer expression.

```gaia
let a = 42;
let b = 3.14;
let c = "Hello World";
```

The inferred type follows the language's type inference and literal typing rules.

### 5. Explicit Type Annotation

Variables may explicitly specify their type.

The initializer must be compatible with the declared type according to the language's conversion rules.

```gaia
let a: Int8 = 42;
let b: Int16 = a;
```

### 6. Statement Termination

Variable declarations are terminated using a semicolon (;).

### 7. The Discard Identifier `_`

The identifier `_` may be used as a discard identifier in a variable declaration:

```gaia
let _ = expression;
```

Unlike ordinary variable declarations, a declaration using `_` does not introduce a name into the current scope. It therefore cannot be referenced and never participates in name lookup or shadowing.

The discard identifier may be used multiple times within the same scope, without conflicting with other declarations of `_`:

```gaia
let _ = first_expression;
let _ = second_expression;
```

Although the declared value cannot be accessed by name, it remains alive until the end of the enclosing scope and is destroyed according to the ordinary lifetime and destruction rules of Gaïa.

## Type Conversions

### 1. General Principles

Gaïa supports implicit and explicit type conversions.

Implicit conversions are permitted when they preserve all possible values of the source type, or when an appropriate user-defined implicit conversion exists.

Explicit conversions are performed using the `as` operator or dedicated conversion functions.

### 2. Implicit Conversions

Implicit conversions are automatically performed when the source and destination types are compatible.

The compiler must not perform implicit conversions that may result in information loss, unless a user-defined implicit conversion explicitly provides such behavior.

### 3. User-Defined Implicit Conversions

Gaïa allows user-defined implicit conversions through constructors and instance methods.

#### 3.1 Converting Constructors

A constructor declared with the `implicit` modifier allows implicit construction from its parameter type.

Example:

```gaia
class Celsius {
    value: Float32;

    pub implicit init(mut self, value: Float32) {
        self.value = value;
    }
}
```

This allows implicit conversion from `Float32` to `Celsius`.

#### 3.2 Conversion Methods

An instance method declared with the `implicit` modifier defines an implicit conversion from its enclosing type to its return type.

Example:

```gaia
class Celsius {
    value: Float32;

    pub fn implicit(self) -> Fahrenheit {
        return Fahrenheit(self.value * 1.8 + 32);
    }
}
```

This allows implicit conversion from `Celsius` to `Fahrenheit`.

They are particularly useful for specialized conversions, such as conversions to `Bool`.

#### 3.3 Conversion Chains

Implicit conversions may be chained.

The compiler resolves the required conversion sequence according to the same overload resolution principles used elsewhere in the language.

#### 3.4 Ambiguous Conversions

When multiple valid conversion sequences produce an ambiguous result, compilation fails.

The compiler must report the ambiguity and require the developer to explicitly select a conversion or remove the conflicting conversion mechanism.

#### 3.5 Duplicate Conversions

A conversion between two types must not be declared more than once.

For example, defining a converting constructor from `A` to `B` and an implicit conversion method from `A` to `B` constitutes a duplicate conversion and produces a compilation error.

Conversions in opposite directions are permitted.

For example, `A` may implicitly convert to `B`, while `B` may implicitly convert to `A`.

These are distinct conversions and do not constitute duplicates.

### 4. Explicit Conversions

Explicit conversions use the `as` operator.

The operator adapts its behavior according to the source and destination types.

It may invoke user-defined implicit conversions explicitly.

Example:

```gaia
let temperature: Celsius = 25.0;

let fahrenheit: Fahrenheit = temperature as Fahrenheit;
```

The `as` operator does not make otherwise invalid conversions possible.

### 5. Conversion Restrictions

Some conversions require dedicated functions rather than the `as` operator.

For example, floating-point to integer conversions must use appropriate conversion functions such as `round` or `floor`.

Example:

```gaia
let value: Float64 = 42.7;

let rounded: Int32 = round(value);
let floored: Int32 = floor(value);
```

The `as` operator is not intended to replace specialized conversion operations.

### 6. Implicit Conversions in Overload Resolution

#### 6.1 General Principles

Implicit conversions participate in function overload resolution.

When multiple overload candidates are otherwise viable, the compiler compares their required implicit conversion sequences.

#### 6.2 Conversion Sequence Preference

Conversion sequences requiring fewer intermediate conversion steps are preferred over sequences requiring more steps.

This rule also applies to chained user-defined implicit conversions.

#### 6.3 Ambiguous Conversion Sequences

When multiple candidates require conversion sequences with the same number of intermediate steps and no other overload resolution rule can distinguish them, compilation fails with an ambiguity error.

The compiler must not arbitrarily select one of the candidates.

### 7. Conversions Involving Inherited Types

A reference or pointer to a derived class may be implicitly converted to a reference or pointer to one of its base classes, provided that the inheritance relationship is public and unambiguous.

These conversions also participate in ordinary overload resolution and implicit conversion sequences. Consequently, functions, methods, constructors, and operators accepting references or pointers to a base class may also accept instances of derived classes through the corresponding implicit conversion.

When a derived object is used to construct or assign a base-class object, the operation acts on the corresponding base subobject. Only the state belonging to the base class is copied or assigned. This behavior is known as object slicing.

In contrast, converting a pointer or reference to a derived object into one referring to a base subobject does not copy the object or alter its dynamic type.

## Numeric Conversions

### 1. General Principles

Gaïa supports implicit conversions between numeric types when the conversion preserves the exact value of every possible value of the source type.

A numeric conversion is implicitly permitted only when the entire value range of the source type is representable by the destination type without loss of information.

The validity of a conversion is determined by the source and destination types, independently of the actual value of the expression being converted.

Conversions that may lose information are not implicitly permitted.

### 2. Integer Conversions

Integer types may be implicitly converted to other integer types when the destination type can represent every possible value of the source type.

This includes conversions between signed and unsigned integer types when the destination type provides a sufficiently large value range.

Examples of permitted conversions include:

- `Int8` to `Int16`.
- `Int16` to `Int32`.
- `Int32` to `Int64`.
- `UInt8` to `UInt16`.
- `UInt16` to `UInt32`.
- `UInt32` to `UInt64`.
- `UInt8` to `Int16`.
- `UInt16` to `Int32`.

Conversions between integer types of the same width are not implicitly permitted when their value ranges are incompatible.

For example, `Int32` cannot be implicitly converted to `UInt32`, because negative values are not representable by the destination type.

### 3. Floating-Point Conversions

Floating-point types may be implicitly converted to other floating-point types when the destination type can represent every possible value of the source type exactly.

For example, `Float32` may be implicitly converted to `Float64`.

The reverse conversion is not implicitly permitted because it may lose precision or range.

### 4. Integer-to-Floating-Point Conversions

Integer types may be implicitly converted to floating-point types when the destination type can represent every possible integer value of the source type exactly.

For example:

- `Int16` to `Float32`.
- `UInt16` to `Float32`.
- `Int32` to `Float64`.
- `UInt32` to `Float64`.

Conversions such as `Int64` to `Float64` are not implicitly permitted if the destination cannot represent every possible source value exactly.

The conversion must preserve the mathematical value of the source integer.

### 5. Floating-Point-to-Integer Conversions

Floating-point-to-integer conversions are never implicitly permitted.

These conversions must use dedicated mathematical functions that explicitly define the rounding behavior.

Examples include:

- `round`: Rounds to the nearest integer according to its specified rounding rules.
- `floor`: Rounds toward negative infinity.
- `ceil`: Rounds toward positive infinity.

Example:

```gaia
let value: Float64 = 42.7;

let rounded: Int32 = round(value);
let floored: Int32 = floor(value);
let ceiled: Int32 = ceil(value);
```

The `as` operator must not be used to perform floating-point-to-integer conversions.

### 6. Signed-to-Unsigned Conversions

Implicit conversions from signed integer types to unsigned integer types are permitted only when the destination type can represent the entire value range of the source type.

Conversions between signed and unsigned integer types of equal width are not implicitly permitted.

Such conversions require dedicated conversion functions because they may represent different semantic operations.

The following operations are distinguished:

#### 6.1 Absolute Value Conversion

Converts the absolute value of the source integer to the destination unsigned type.

Example:

```gaia
let value: Int32 = -42;
let result: UInt32 = abs(value);
```

The behavior when the absolute value cannot be represented by the source type must be explicitly defined by the corresponding mathematical function.

#### 6.2 Bitwise Conversion

Preserves the exact bit pattern of the source integer while interpreting it as an unsigned integer of the same width.

Example:

```gaia
let value: Int32 = -42;
let result: UInt32 = bitcast<UInt32>(value);
```

This operation preserves the binary representation rather than the mathematical value.

#### 6.3 Checked Conversion

Converts the source integer after verifying at runtime that its value is representable by the destination type.

If the source value is outside the destination type's representable range, the operation reports a runtime failure.

Example:

```gaia
let value: Int32 = 42;
let result: UInt32 = checked_cast<UInt32>(value);
```

A checked conversion must never silently truncate, wrap or otherwise alter the mathematical value.

### 7. Conversion Restrictions

The `as` operator does not permit arbitrary numeric conversions.

It may only perform conversions already permitted implicitly or conversions explicitly defined by the language, such as dynamic casts involving class inheritance.

Conversions requiring rounding, truncation, reinterpretation of bit patterns or runtime validation must use their corresponding dedicated operations.

### 8. Conversion Sequence Integration

Numeric conversions participate in implicit conversion sequences according to the general conversion ranking rules.

Each individual numeric conversion constitutes one conversion step.

Chained numeric conversions are resolved according to the shortest-path and ambiguity rules defined in the Overload Resolution section.

## Pointer Types

### 1. General Principles

Gaïa distinguishes between pointers, array pointers, fixed-size arrays and slices.

These types explicitly describe nullability and sequence representation.

### 2. Object Pointers

Two pointer types are available for individual objects.

- `&T`: Non-nullable pointer to an object of type `T`.
- `*T`: Nullable pointer to an object of type `T`.

### 3. Array Pointers

Array pointers represent an address pointing to the first element of a sequence of objects.

- `[&]T`: Non-nullable pointer to the first element of a sequence of `T`.
- `[*]T`: Nullable pointer to the first element of a sequence of `T`.

Array pointers do not inherently contain the number of elements in the sequence.

### 4. Fixed-Size Arrays

The `[N]T` syntax represents an array containing exactly `N` instances of type `T`.

### 5. Slices

The `[]T` syntax represents a slice of elements of type `T`.

A slice consists of a pointer to its first element and a size.

Elements may be accessed using the indexing operator `[]` or iteration mechanisms.

The number of elements is accessible through the `.size()` member.

### 6. Mutability

Mutability is independently specified at each relevant level.

Variable mutability determines whether a pointer variable can be reassigned.

Pointer mutability determines whether the pointed-to value can be modified.

The mutability of a pointer expression determines whether it provides mutable or immutable access to its target.

### 7. Mutability Conversions

Implicit mutability conversions are permitted only from mutable to immutable.

Conversions from immutable to mutable require an explicit operation.

When converting nested pointer types, all mutable qualifiers to the left of the target mutability level must first be removed.

## Pointer Operations

### 1. Automatic Dereferencing

Gaïa performs automatic pointer dereferencing.

Pointers behave as values when accessed through ordinary expressions.

Explicit dereferencing using the `*` operator is not required to access the pointed-to object.

Example:

```gaia
let value: Int32 = 42;
let ptr: &Int32 = &value;

print(ptr);
```

#### 1.1 Implicit Pointer Operations

Pointer operations may be performed implicitly when required by an expression's expected type.

An object of type `T` may be implicitly converted to a reference of type `&T` when an appropriate address can be obtained.

A reference of type `&T` may be automatically dereferenced when a value of type `T` is expected.

These operations participate in implicit conversion resolution and each constitutes one conversion step.

### 2. Address-of Operator

The `&` operator obtains the address of a value.

The `&mut` form obtains its address with mutable access.

Examples:

```gaia
let value: Int32 = 42;
let ptr: &Int32 = &value;

let mut mutable_value: Int32 = 42;
let mutable_ptr: &mut Int32 = &mut mutable_value;
```

### 3. Pointer Assignment

Pointers are manipulated as ordinary values.

Accessing or modifying a pointed-to object does not require explicit dereferencing.

The mutability of the pointer variable and the mutability of its target remain independent.

### 4. Pointer Arithmetic

Pointer arithmetic is restricted to array pointer types.

Ordinary object pointers do not support pointer arithmetic.

### 5. Pointer Assignment

Pointer assignment supports automatic dereferencing.

The assignment operation is resolved according to the type of the right-hand operand.

#### 5.1 Pointee Assignment

When the right-hand operand is compatible with the pointed-to value type, the assignment modifies the pointed-to value.

Example:

```gaia
let mut value: Int32 = 42;
let mut ptr: &mut Int32 = &mut value;

ptr = 50;
```

This operation is equivalent to modifying the value referenced by `ptr`.

#### 5.2 Pointer Reassignment

When the right-hand operand is compatible with the pointer type, the assignment replaces the address stored in the pointer.

Example:

```gaia
let mut first: Int32 = 42;
let mut second: Int32 = 100;

let mut ptr: &mut Int32 = &mut first;

ptr = &mut second;
```

#### 5.3 Mutability Requirements

Pointee assignment requires mutable access to the pointed-to object.

Pointer reassignment requires the pointer variable itself to be mutable.

These requirements are independent.

### 6. Pointer Conversions

#### 6.1 Nullability Conversions

Non-nullable pointers may be implicitly converted to their nullable counterparts.

The reverse conversion requires an explicit operation.

#### 6.2 Array Pointer Conversions

Array pointers may be implicitly converted to ordinary element pointers.

The reverse conversion requires an explicit operation.

#### 6.3 Inheritance Conversions

Pointers to derived class types may be implicitly converted to pointers to their base class types.

These conversions account for the required pointer adjustments, including those resulting from multiple inheritance.

The reverse conversion requires an explicit dynamic cast using the `as` operator.

Example:

```gaia
let player: &Player = ...;
let entity: &Entity = player;

let another_player: &Player = entity as &Player;
```

Dynamic casts perform runtime type verification.

They must account for multiple inheritance and the corresponding pointer adjustments.

When a dynamic cast fails, its behavior depends on the destination pointer nullability:

- Nullable destination: returns `null`.
- Non-nullable destination: reports a runtime failure.

#### 6.4 Array Pointer Inheritance Restrictions

Array pointers do not support inheritance-based conversions.

An array pointer to a derived type cannot be converted to an array pointer to one of its base types.

## Nullability

### 1. Null Type

Gaïa provides a dedicated `Null` type.

The `null` literal is the only value of this type.

```gaia
let value: Null = null;
```

### 2. Nullable Pointers

The following pointer types are nullable:

- `*T`
- `[*]T`

Nullable pointers may be initialized or assigned using a value of type `Null`.

Example:

```gaia
let ptr: *Int32 = null;

let mut other: *Int32 = &value;
other = null;
```

Non-nullable pointer types do not accept values of type `Null`.

### 3. Nullable Pointer Diagnostics

Using a nullable pointer without an appropriate nullability check may generate a compiler warning.

These diagnostics follow the same general principles as lifetime diagnostics.

Potentially unsafe operations generate warnings, while situations that can be conclusively identified as invalid may produce compilation errors.

Lifetime and nullability diagnostics may be configured through compilation options and source-level annotations.

### 4. Null Coalescing Operator

The `??` operator provides a fallback value when a nullable pointer contains `null`.

When the pointer is non-null, the operator evaluates to its referenced value.

When the pointer is null, the operator evaluates to the fallback expression.

Example:

```gaia
let ptr: *Int32 = null;

let value: Int32 = ptr ?? 42;
```

### 5. Optional Member Access

The `?.` operator provides conditional member access on nullable pointers.

When the pointer is non-null, the operator accesses the requested member.

When the pointer is null, the result is null.

The resulting type is nullable.

Example:

```gaia
let player: *Player = get_player();

let health: *Int32 = player?.health;
```

### 6. Control Flow Nullability Analysis

Gaïa performs nullability analysis based on the Control Flow Graph (CFG).

The analysis tracks the potential nullability states of nullable pointers throughout program execution.

#### 6.1 Conditional Analysis

The compiler recognizes nullability checks performed through equality and inequality comparisons with `null`.

Examples:

```gaia
if (ptr != null) {
    // ptr is known to be non-null.
}

if (ptr == null) {
    // ptr is known to be null.
}
```

#### 6.2 Control Flow Propagation

Nullability information is propagated across control flow branches.

The compiler may determine that a pointer is non-null after a conditional block when all execution paths leading beyond that block guarantee its non-null state.

Example:

```gaia
if (ptr == null) {
    return;
}

// ptr is known to be non-null.
```

#### 6.3 State Invalidation

Nullability information must be updated when an operation may change the value or nullability of a pointer.

Assignments and other potentially modifying operations invalidate previously established assumptions when appropriate.

#### 6.4 Diagnostic Generation

The compiler generates nullability warnings based on the results of its control flow analysis.

The absence of a warning does not constitute a runtime guarantee that the pointer is non-null.

## Arrays and Slices

### 1. Fixed-Size Arrays

The `[N]T` syntax represents a contiguous array containing exactly `N` instances of type `T`.

The array size is known at compile time.

Example:

```gaia
let values: [10]Int32 = [
    0, 1, 2, 3, 4,
    5, 6, 7, 8, 9
];
```

### 2. Slices

The `[]T` syntax represents a slice of elements of type `T`.

A slice logically consists of a pointer to its first element and a size.

Its logical representation is:

```gaia
{
    ptr: [&]T,
    size: Size
}
```

This representation is conceptual and is not directly accessible.

The slice does not own the elements it references.

### 3. Slice Construction

A slice may be implicitly constructed from a fixed-size array.

The compiler initializes its pointer to the first array element and its size to the array's compile-time size.

Example:

```gaia
let values: [10]Int32 = [...];
let slice: []Int32 = values;
```

### 4. Slice Size

The number of elements in a slice can be retrieved using `.size()`.

Example:

```gaia
let count: Size = slice.size();
```

### 5. Slice Iteration

Slices support indexed iteration and range-based iteration.

Example:

```gaia
for (let i = 0; i < slice.size(); ++i) {
    print(slice[i]);
}
```

Alternatively:

```gaia
for i in slice {
    print(i);
}
```

### 6. Array Pointer Conversion

Fixed-size arrays and slices may be implicitly converted to array pointers.

The following conversions are supported:

- `[N]T` to `[&]T`
- `[N]T` to `[*]T`
- `[]T` to `[&]T`
- `[]T` to `[*]T`

These conversions discard the size information.

The compiler may generate a warning when it determines that the size information is lost without being preserved through another means.

### 7. Information-Losing Conversions

Conversion from an array or slice to an array pointer is the only implicit conversion category permitted to lose information.

Such conversions remain implicitly valid, but may generate a compiler warning.

### 8. Element Access

Gaïa provides checked and unchecked element access operations.

#### 8.1 Checked Access

The `[]` operator performs bounds-checked element access.

When the specified index is outside the valid range, the operation must report an out-of-bounds error.

This operator is available for arrays and slices.

Example:

```gaia
let values: [10]Int32 = [...];

let value = values[5];
```

#### 8.2 Unchecked Access

The `get_unchecked(index)` method provides unchecked element access.

It does not perform bounds checking.

Calling this method with an invalid index results in undefined behavior.

Example:

```gaia
let value = values.get_unchecked(5);
```

### 9. Pointer-to-Slice Conversion

No conversion from array pointers to slices is currently provided.

An array pointer does not contain sufficient size information to construct a slice.

Such a conversion would require an explicit mechanism for supplying the missing size information.

### 10. Pointer Conversions

#### 10.1 Array Pointer to Element Pointer

Array pointers may be implicitly converted to ordinary element pointers.

The resulting pointer refers to the first element of the original sequence.

Examples:

```gaia
let array_ptr: [&]Int32 = ...;
let element_ptr: &Int32 = array_ptr;
```

The reverse conversion requires an explicit operation.

#### 10.2 Derived-to-Base Pointer Conversion

Pointers to derived class types may be implicitly converted to pointers to their base class types.

This conversion preserves the referenced object.

Examples:

```gaia
let derived: &Derived = ...;
let base: &Base = derived;
```

The reverse conversion requires an explicit operation.

#### 10.3 Explicit Conversions

Conversions that introduce a more restrictive or specific pointer interpretation require explicit syntax.

This includes:

- Element pointer to array pointer.
- Base class pointer to derived class pointer.

The validity and runtime behavior of explicit conversions depend on the source and destination types.

#### 10.4 Array Pointer Type Compatibility

Array pointer conversions do not support inheritance-based type conversions.

An array pointer to a derived type cannot be converted to an array pointer to one of its base types.

This restriction applies regardless of pointer nullability or mutability.

The reason is that array pointers represent contiguous sequences of elements whose memory layout and element stride depend on their actual type.

Converting an array pointer between types with potentially different memory layouts would invalidate element addressing.

Ordinary object pointers may still support derived-to-base conversions when the inheritance relationship permits it.

## Pointer Ownership and Memory Management

### 1. General Principles

Gaïa distinguishes pointer representation from object ownership.

Pointer types do not imply ownership of the objects they reference.

The ownership and lifetime of dynamically allocated objects are managed separately.

### 2. Non-Owning Pointers

The pointer types `&T`, `*T`, `[&]T` and `[*]T` are non-owning pointers.

They do not automatically manage the lifetime of their targets.

Destroying a pointer does not destroy the object it references.

### 3. Ownership Types

Gaïa provides dedicated ownership types through its standard library:

- `Box<T>`: Unique ownership.
- `Rc<T>`: Shared reference-counted ownership.
- `Arc<T>`: Shared atomic reference-counted ownership.

### 4. Manual Memory Management

Gaïa supports manual memory management through `new` and `delete`.

The `new` expression dynamically allocates and initializes an object.

The `delete` expression explicitly destroys and deallocates an object.

Example:

```gaia
let ptr: &mut T = new T();

// Use ptr...

delete ptr;
```

Manual memory management is the responsibility of the developer.

The compiler does not enforce ownership tracking for ordinary pointers.

## Dynamic Allocation

### 1. General Principles

Gaïa supports dynamic memory allocation through the `new` keyword.

Dynamically allocated objects have a lifetime independent of the lexical scope in which they were allocated.

Their destruction is performed explicitly using `delete` or `delete[]`.

### 2. Single Object Allocation

The general syntax is:

```gaia
new Type(arguments)
```

This expression dynamically allocates and initializes a single object.

Example:

```gaia
let ptr: &mut Int32 = new Int32(42);

delete ptr;
```

### 3. Dynamic Array Allocation

The general syntax is:

```gaia
new [Size]Type
```

This expression dynamically allocates an array containing the specified number of elements.

Example:

```gaia
let ptr: [&]Int32 = new [10]Int32;

delete[] ptr;
```

### 4. Dynamic Array Initialization

Dynamic arrays may also be initialized using an explicit initializer list.

The general syntax is:

```gaia
new Type [values...]
```

The number of elements is determined by the number of initializers.

Example:

```gaia
let ptr: [&]Int32 = new Int32 [
    0, 1, 2, 3, 4,
    5, 6, 7, 8, 9
];

delete[] ptr;
```

### 5. Deallocation

Gaïa distinguishes between single-object and array deallocation.

- `delete ptr` destroys and deallocates a single dynamically allocated object.
- `delete[] ptr` destroys and deallocates a dynamically allocated array.

The deallocation operation must correspond to the allocation form.

### 6. In-Place Construction

Gaïa supports in-place construction, allowing an object to be constructed in an existing memory region without performing a new allocation.

The general syntax is:

```gaia
new (storage) Type(arguments)
```

The provided storage must be sufficiently large and correctly aligned for the object being constructed.

Example:

```gaia
let storage: [&]mut Byte = malloc(sizeof(Foo));
let object: &mut Foo = new (storage) Foo(arguments);
```

In-place construction does not allocate or take ownership of the underlying storage. It only constructs the object at the specified location and returns a mutable reference to it.

The lifetime of the constructed object is independent of the lifetime of the underlying storage. Destroying the object does not release the storage, which remains available for subsequent use.

In-place construction also supports dynamically allocated arrays.

The general syntax is:

```gaia
new (storage) [Size]Type
```

Example:

```gaia
let storage: [&]mut Byte = malloc(sizeof(Foo) * 10);
let objects: [&]mut Foo = new (storage) [10]Foo;
```

The storage must be sufficiently large and correctly aligned for the entire array. Elements are constructed according to the ordinary array construction rules.

### 7. Destruction Without Deallocation

Gaïa provides distinct syntax for destroying an object without releasing its underlying storage.

The general syntax is:

```gaia
delete() ptr;
```

This operation invokes the object's destructor but does not deallocate the memory containing it.

For dynamically allocated arrays, the corresponding syntax is:

```gaia
delete[]() ptr;
```

This operation destroys all elements of the array in reverse order of construction, without releasing the underlying storage.

The existing `delete` and `delete[]` forms retain their usual behavior: they destroy the object or array and release the associated storage.

Destruction without deallocation is particularly useful for objects constructed in-place and for custom memory management.

### 8. Allocation Operator Overloading

Gaïa allows the allocation and deallocation behavior of `new` and `delete` to be customized through the `extend` mechanism.

Two forms of customization are supported:

- A global customization declared using `extend {}`, which applies throughout the application.
- A type-specific customization declared using `extend T {}`, which applies to allocations of type `T`, including arrays of `T`.

Type-specific customizations take precedence over the global customization. They are not inherited by derived classes.

The following four operations can be customized independently:

- Single-object allocation.
- Array allocation.
- Single-object deallocation.
- Array deallocation.

The allocation functions receive the requested storage size and alignment and return a mutable byte reference.

The deallocation functions receive the storage reference, its size, and its alignment.

A global customization has the following general form:

```gaia
extend {
    fn new(size: Size, align: Size) -> [&]mut Byte
        throw (MemoryError);

    fn new[](size: Size, align: Size) -> [&]mut Byte
        throw (MemoryError);

    fn delete(ptr: [&]mut Byte, size: Size, align: Size);

    fn delete[](ptr: [&]mut Byte, size: Size, align: Size);
}
```

The language ensures that object construction and destruction follow the ordinary lifetime rules, independently of the allocation mechanism.

A deallocation operation must not throw an exception.

Only one effective global customization may exist within an application. Conflicting global customizations are a compilation error.

### 9. Allocation Errors

Allocation operations may fail and report their failure by throwing an exception derived from `MemoryError`.

`MemoryError` is the base class for memory-related exceptions. Custom allocators may define specialized exception types derived from this class to provide additional information about allocation failures.

Allocation exceptions participate in the ordinary exception propagation mechanism. Functions that may propagate allocation failures must declare the corresponding exception in their `throw` contract, unless they handle or transform it.

This also applies to higher-level abstractions that perform dynamic allocation internally. For example, container constructors and operations that may require additional storage must account for the possibility of a memory allocation failure.

Deallocation operations must not throw exceptions. This ensures that cleanup remains safe during exception propagation and object destruction.

## Reference Safety and Lifetime Diagnostics

### 1. General Principles

Gaïa does not enforce memory safety through a mandatory ownership or borrowing system.

Developers retain control over object lifetimes, references and memory management.

The language trusts developers to manage object lifetimes correctly and does not prohibit potentially unsafe operations solely because they may result in dangling references.

### 2. Dangling References

A dangling reference occurs when a reference refers to an object whose lifetime has ended.

Dangling references are generally permitted by the language's design.

However, situations where a dangling reference can be conclusively identified during compilation may produce a compilation error.

Example:

```gaia
fn foo() -> &Int32 {
    let i: Int32 = 42;
    return &i;
}
```

In this example, the returned reference refers to a local variable whose lifetime ends when the function returns.

The compiler may reject this code because the dangling reference is unambiguous.

### 3. Lifetime Warnings

The compiler may emit warnings when it detects situations that could potentially result in dangling references or invalid object lifetimes.

These diagnostics do not necessarily indicate that the code is invalid.

They indicate that the compiler has identified a potential lifetime issue that should be reviewed by the developer.

### 4. Diagnostic Configuration

Lifetime warnings must be configurable through compilation options.

The compiler must provide an option to promote these warnings to compilation errors.

Individual warnings may also be selectively disabled using source-level annotations.

The exact annotation syntax and diagnostic configuration mechanisms are specified separately.

### 5. Analysis Limitations

Lifetime diagnostics do not constitute a formal guarantee of memory safety.

The absence of lifetime warnings does not imply that a program is free from dangling references or other lifetime-related errors.

The compiler is not required to identify every possible lifetime violation.

## Lexical Scope

Gaïa uses lexical scoping.

The scope of a variable is determined by the block in which it is declared.

A variable is accessible from its declaration point until the end of its enclosing scope, subject to the language's visibility and accessibility rules.

```gaia
fn main() {
    let a = 42;

    {
        let b = 10;

        // Both a and b are accessible.
    }

    // a is accessible.
    // b is no longer accessible.
}
```

### 1. Object Lifetime

The lifetime of an object is governed by its storage duration and lifetime rules.

For ordinary automatic local variables, the object's lifetime ends when execution leaves its enclosing scope.

### 2. RAII

Gaïa adopts Resource Acquisition Is Initialization (RAII).

Resources are acquired during object initialization and released automatically when the corresponding object's lifetime ends.

Resource management is tied to object lifetime rather than requiring explicit cleanup operations.

### 3. Destruction

When an object's lifetime ends, its destructor is invoked according to the language's destruction order rules.

For local automatic variables, destruction occurs in reverse order of completed initialization within the relevant scope.

```gaia
class Resource {
    pub init(self) {
        print("Acquired");
    }

    pub deinit(self) {
        print("Released");
    }
}
```

```gaia
fn main() {
    let a = Resource();
    let b = Resource();

    // Destruction order:
    // b, then a.
}
```

## Object Lifecycle

### 1. Initialization

Classes may define a special method named `init`.

The `init` method is responsible for initializing an instance of its enclosing class.

It receives an explicit self parameter representing the instance being initialized.

```gaia
class Resource {
    pub init(self) {
        print("Acquired");
    }
}
```

### 2. Destruction

Classes may define a special method named `deinit`.

The `deinit` method is responsible for releasing resources owned by the instance when its lifetime ends.

It receives an explicit self parameter representing the instance being destroyed.

```gaia
class Resource {
    pub deinit(self) {
        print("Released");
    }
}
```

### 3. RAII Integration

The invocation of `init` and `deinit` is integrated into the object's lifetime management.

Initialization occurs when an instance is constructed.

Destruction occurs when the object's lifetime ends, following Gaïa's destruction order rules.

### 4. Visibility

The `pub` modifier makes the corresponding declaration publicly accessible.

Visibility rules are specified separately.

## Control Flow

### 1. Conditional Statements

Gaïa provides conditional statements through the `if` and `else` keywords.

The general syntax is:

```gaia
if condition {
    statements
} else if condition {
    statements
} else {
    statements
}
```

Parentheses around conditions are not required.

Conditions must produce a value compatible with `Bool`.

Implicit conversions to `Bool` are permitted when an appropriate implicit conversion exists.

Integer-to-`Bool` implicit conversions are not permitted.

Boolean conversions may occur either when evaluating the condition itself or during the resolution of operators requiring boolean operands.

This includes, but is not limited to, the `!`, `&&` and `||` operators.

The `&&` and `||` operators retain short-circuit evaluation semantics.

#### 1.1 Logical Operators

The logical operators `&&` and `||` cannot be overloaded by user-defined operators.

These operators retain their built-in short-circuit evaluation semantics.

The right-hand operand is evaluated only when required by the logical operation.

Implicit conversions to `Bool` are permitted for their operands.

The unary logical negation operator `!` may be overloaded.

### 2. Switch Statements

Gaïa provides multi-branch conditional statements through the `switch` keyword.

The general syntax follows the traditional C++ switch statement structure.

```gaia
switch value {
    case 1:
        statements
        break;

    case 2:
        statements
        break;

    default:
        statements
        break;
}
```

#### 2.1 Case Labels

Each `case` specifies one or more values matching the switch expression.

Multiple values may share the same execution branch using the `|` operator.

Example:

```gaia
switch value {
    case 1 | 2 | 3:
        print("Small");
        break;

    case 10:
        print("Ten");
        break;

    default:
        print("Other");
        break;
}
```

#### 2.2 Range Labels

Case labels may specify ranges using the range operators.

The `..` operator represents an inclusive range.

The `...` operator represents a range excluding its upper bound.

Example:

```gaia
switch value {
    case 1..10:
        print("Between 1 and 10");
        break;

    case 10...20:
        print("Between 10 and 19");
        break;

    default:
        print("Other");
        break;
}
```

#### 2.3 Case Scope

Each `case` introduces its own lexical scope.

Variables declared within a case are accessible only within that case.

Their lifetime ends when execution leaves the corresponding case.

Example:

```gaia
switch value {
    case 1:
        let message = "Hello";
        print(message);
        break;

    case 2:
        let message = "World";
        print(message);
        break;
}
```

Variables declared in one case cannot be accessed from another case.

#### 2.4 Fallthrough

Gaïa requires explicit fallthrough using the `continue` keyword.

A case that reaches its end without executing either `break` or `continue` constitutes a compilation error.

Example:

```gaia
switch value {
    case 1:
        print("One");
        continue;

    case 2:
        print("Two");
        break;

    default:
        print("Other");
        break;
}
```

When `continue` transfers execution to the next case, local variables belonging to the previous case are destroyed before the next case begins executing.

Using `continue` in the last case of a switch statement, when no subsequent case exists, produces at least a compiler warning.

The compiler may promote this diagnostic to an error according to the configured diagnostic rules.

### 3. Loop Statements

Gaïa supports the traditional C++ loop constructs.

#### 3.1 While Loop

The `while` statement repeatedly executes its body while its condition evaluates to `true`.

```gaia
while condition {
    statements
}
```

#### 3.2 Do-While Loop

The `do-while` statement executes its body before evaluating its condition.

```gaia
do {
    statements
} while condition;
```

#### 3.3 For Loop

The traditional `for` statement supports initialization, condition and iteration expressions.

```gaia
for (initialization; condition; iteration) {
    statements
}
```

Example:

```gaia
for (let mut i = 0; i < 10; ++i) {
    print(i);
}
```

The initialization expression is executed once before the first iteration.

The condition is evaluated before each iteration.

The iteration expression is executed after each completed iteration.

#### 3.4 Range-Based For Loop

Gaïa supports range-based iteration through the `in` keyword.

```gaia
for value in values {
    statements
}
```

The iteration variable is declared within the loop scope.

### 4. Break and Continue Statements

The `break` and `continue` statements control the execution of enclosing control structures.

#### 4.1 Break

The `break` statement terminates the execution of its target control structure.

Without an explicit label, it targets the nearest compatible enclosing structure.

#### 4.2 Continue

The `continue` statement transfers execution according to the semantics of its target control structure.

For loops, it advances execution to the next iteration.

For switch statements, it performs an explicit fallthrough to the next case.

Without an explicit label, `continue` targets the nearest enclosing compatible control structure.

When targeting a switch statement, `continue` transfers execution to its next case.

### 5. Labeled Control Structures

#### 5.1 General Principles

Gaïa supports labels on control structures that accept `break` and `continue` statements.

Labels allow these statements to explicitly identify the control structure they target.

#### 5.2 Label Declaration

A label is declared by prefixing a supported control structure with an identifier followed by a colon.

The general syntax is:

```gaia
label: control_structure {
    statements
}
```

Example:

```gaia
foo: while condition {
    statements
}
```

#### 5.3 Labeled Break and Continue

The `break` and `continue` statements may specify a label identifying their target control structure.

Example:

```gaia
foo: while some_condition() {
    bar: for i in values() {
        if i > 42 {
            break foo;
        }

        if i % 2 == 0 {
            continue bar;
        }
    }
}
```

A labeled `break` terminates the specified control structure.

A labeled `continue` applies the continuation behavior of the specified control structure.

#### 5.4 Label Resolution

A label must identify an enclosing control structure compatible with the corresponding statement.

Referencing an undefined, inaccessible or incompatible label produces a compilation error.

Labels must be unambiguous within their applicable scope.

## Move Semantics

### 1. Overview

Gaïa supports move semantics to allow the ownership of a value to be transferred without requiring an additional copy.

A move expresses the intent to transfer a value to another operation. However, using the `move` keyword does not guarantee that a transfer will actually take place. The selected operation must support move semantics for the transfer to occur.

Move semantics are integrated into overload resolution. The `move` keyword does not perform an operation after overload resolution; instead, it changes the category of the argument considered during overload resolution.

### 2. Temporary and Persistent Values

Temporary values can be transferred automatically when the selected operation supports move semantics.

Persistent values require an explicit `move` keyword to be considered for transfer.

For example:

```gaia
fn consume(move value: Foo) {}

fn test(mut foo: Foo) {
    consume(Foo());       // The temporary may be transferred automatically.
    consume(move foo);    // The persistent value is explicitly offered for transfer.
}
```

A persistent value passed without `move` cannot select a move parameter.

A temporary value does not have to be transferred. If no suitable move operation is selected, it can be copied or passed by reference according to the usual overload resolution rules.

### 3. Argument Categories and Conversions

For overload resolution, temporary values and explicitly moved values are treated as belonging to an internal argument category.

This category is not a type exposed by the language. It is an implementation concept used to determine the conversions available during overload resolution.

An argument in this category supports the following conversions:

- An exact match with a `move` parameter of the corresponding type.
- An implicit conversion to a value parameter of the corresponding type.
- An implicit conversion to a reference parameter, through the conversion to a value followed by automatic referencing.

The conversion to a value is a no-op, but still contributes to the conversion cost. Consequently, when all other aspects are equivalent, a value parameter is a better match than a reference parameter for such an argument.

A persistent value that is not explicitly moved does not belong to this category. It supports the usual conversions to value and reference parameters, including automatic referencing when applicable, but cannot match a `move` parameter.

All these conversions participate in the normal overload resolution algorithm. No additional priority rules are introduced specifically for move semantics.

### 4. Move Parameters

A parameter declared with the `move` keyword receives its argument by transfer:

```gaia
fn consume(move value: Foo) {
    // value is mutable and may be moved again.
}
```

A move parameter is automatically mutable. This is specific to move parameters; ordinary value parameters remain immutable unless explicitly declared with `mut`.

When a transfer takes place, the parameter reuses the storage of the source value. No additional object construction is semantically required.

The same principle applies to temporary values. Their storage may be reused to initialize a move parameter.

These rules describe the observable semantics of the transfer. They do not require a particular physical memory layout or guarantee that object addresses remain identical.

Move parameters may themselves be moved into other operations:

```gaia
fn forward(move value: Foo) {
    consume(move value);
}
```

After such a transfer, the parameter is considered moved, subject to the move analysis rules.

### 5. Move Failure

The `move` keyword expresses an explicit intent to transfer a value, but does not guarantee that the selected operation performs a transfer.

If an explicit move does not result in an actual transfer, the compiler emits the `memory-move-not-performed` warning.

This warning does not apply when a temporary value is copied or passed by reference without an explicit move request.

### 6. Moving Through References

Moving a value through a mutable reference (`&mut T`) is permitted, but emits the `memory-move-through-reference` warning.

This warning is emitted regardless of how the mutable reference was obtained, including local references, attributes, function return values, or other expressions.

Moving a value through a constant reference (`&T`) is forbidden.

When the target of a mutable reference can be identified by the move analysis, the target's move state is updated accordingly.

### 7. Self-Move

Moving a value into itself is diagnosed with the `memory-self-move` warning.

### 8. Destruction of Moved Values

Moving a value does not end the lifetime of the source object.

As in C++, a moved-from object remains valid but has an indeterminate state. Its destructor is still invoked normally when its lifetime ends, including during ordinary scope exit or other normal destruction sequences.

The moved-from state must therefore remain compatible with the invocation of the object's destructor. A move operation must not leave the source object in a state that makes its normal destruction invalid.

### 9. Operations on Moved Values

An operation performed on a variable in the `Moved` or `Maybe moved` state emits the `memory-use-after-move` warning, unless the operation is a reassignment of the entire variable.

The following operations are considered potentially unsafe:

- Accessing a member through `.` or `->`, whether for reading or writing.
- Calling an instance method on the variable.
- Accessing an overloaded operator through the variable, including implicit operator invocations.
- Applying the `as` conversion operator to the variable, regardless of the conversion being performed.

Calling a `static` method through an instance does not constitute an operation on the instance itself and therefore does not emit `memory-use-after-move`. However, the compiler emits a remark indicating that calling a static method through an instance can reduce readability.

A moved-from object remains valid and its operations remain callable. However, because its state is indeterminate, the behavior of these operations is not necessarily defined and may be unsafe.

The `memory-use-after-move` warning therefore indicates a potentially dangerous operation rather than a language-level restriction. The compiler does not attempt to determine whether a particular operation is safe for the moved-from state.

Destruction is an exception to these rules: the compiler-generated or user-defined destructor is invoked normally, even when the variable is in the `Moved` or `Maybe moved` state.

## Move Analysis

### 1. Overview

The compiler performs a control-flow-based analysis to track the initialization and move state of local variables.

The analysis is performed within function and method bodies. It includes their parameters, which are treated as local variables for this purpose.

The analysis is local and does not inspect the bodies of invoked functions or methods. It does not perform interprocedural analysis.

### 2. Move States

Each tracked variable has one of the following abstract states:

- `Initialized`: the variable is initialized and may be used normally.
- `Moved`: the variable has been moved.
- `Maybe moved`: the variable may have been moved on at least one possible execution path.

A variable remains valid after being moved, but its state is indeterminate. The compiler does not guarantee that its previous value is preserved.

Any operation on a moved or potentially moved variable that is subject to move-use diagnostics under the rules defined in `Move Semantics` emits the `memory-use-after-move` warning, unless the operation is a reassignment of the entire variable.

The warning includes a note for each distinct move location that may have caused the invalid use. Each location is reported only once, even if it reaches the diagnostic through multiple control-flow paths.

Reassigning the entire variable restores its state to `Initialized`.

Partial reassignment does not restore the state of the entire variable. For example, assigning an attribute after moving its containing object does not make the object initialized again.

### 3. Control-Flow Analysis

Move analysis is based on the control-flow graph (CFG). The compiler considers the possible execution paths and merges their states at control-flow join points.

When several paths reach the same point:

- A variable remains `Initialized` if it is initialized on every incoming path.
- A variable is `Moved` if it is moved on every incoming path.
- A variable is `Maybe moved` if its state differs between incoming paths, or if it is potentially moved on at least one path.

`Moved` and `Maybe moved` both cause `memory-use-after-move` when the variable is used.

### 4. Conditional Branches

Conditional statements and expressions create separate control-flow branches.

For example, an `if` statement creates a branch for each possible outcome of its condition. The resulting states are merged at the corresponding join point.

Conditional expressions (`?:`) similarly create two mutually exclusive branches, one for each operand.

### 5. Loops

For the purposes of move analysis, `while` and `for` loops are treated like conditional branches.

The compiler considers that execution may either enter or skip the loop body. The body is analyzed once, and its resulting state is merged with the state of the path that skips the body.

The analysis does not attempt to model repeated iterations of the loop.

A `do-while` loop is treated as an ordinary sequential block. Its body is analyzed once, without modeling subsequent iterations.

### 6. Control-Flow Transfers

Control-flow transfers are represented by the corresponding edges in the CFG:

- `return` terminates the current path and exits the function.
- `throw` transfers execution to the appropriate exception handler, or exits the function if no handler applies.
- `break` and `continue` transfer execution to their respective target control structures.

The target of a `break` or `continue` statement is determined according to the standard Gaïa control-flow rules. An explicit label identifies the target structure; otherwise, the nearest compatible structure is selected.

For `switch` statements, the CFG follows the standard Gaïa `switch` semantics, including the explicitly specified branching mode at the end of each `case`.

These transfers do not require additional move-specific rules. Their effects are handled through the usual CFG state propagation and merging.

### 7. Exception Handling

Exception handling constructs introduce control-flow paths according to their semantics.

For prefix `try`:

```gaia
try riskyOperation();
```

The normal execution path continues after the expression. An exception causes the current function to exit through exception propagation.

For postfix `catch`:

```gaia
riskyOperation() catch error {
    fallback();
}
```

The exception cases are handled exhaustively by the `catch` expression. Normal and exceptional paths converge after the construction, unless a path terminates explicitly.

For a `try` block with `catch` clauses:

```gaia
try {
    riskyOperation();
} catch error {
    fallback();
}
```

The CFG represents the normal execution path and the exceptional paths leading to compatible `catch` clauses.

In this case, the exception types declared by invoked functions and methods are taken into account to determine which `catch` clauses may be reached.

The declared exception types are not used for CFG branching in prefix `try` or postfix `catch` expressions.

Within a `try` block, `return` exits the function, while `throw` transfers execution to an exception handler. `break` and `continue` are not applicable in this context.

Within a `catch` block, both `return` and `throw` may terminate the current path.

When normal and exceptional paths converge, their move states are merged as usual. If all paths terminate unconditionally, no common state needs to be computed.

### 8. Short-Circuit Operators

Short-circuit operators create explicit control-flow branches.

This applies to:

- `&&`
- `||`
- `??`
- `?.`

The CFG represents the conditional evaluation of the relevant operand or access. The resulting states are merged after the expression.

Consequently, a move occurring only on a path where a short-circuited operand is evaluated makes the corresponding variable `Maybe moved` after the expression, when another path leaves it initialized.

### 9. Pattern Matching

A `match` expression creates a branch for each pattern that may match.

The resulting states are merged at the end of the expression.

Pattern guards are not supported in the first version of the language and are therefore not considered by this analysis.

### 10. Reference Target Tracking

The CFG tracks the targets of local references whenever their provenance can be determined locally.

A reference may be associated with one or more possible target variables.

When a reference is initialized from another reference, the target set is copied.

When a reference is reassigned, its previous target set is replaced by the target set of the new value.

If the new target cannot be determined, the compiler abandons target tracking for that reference.

At control-flow join points, the possible target sets of a reference are merged by taking their union.

When a reference may target several variables, an operation through that reference is considered to affect every tracked possible target.

If at least one tracked possible target is moved or potentially moved, reading through the reference emits `memory-use-after-move`.

Only targets whose states can be tracked locally participate in this analysis. Targets outside this scope are ignored.

### 11. Calls and Reference Provenance

The analysis does not inspect the bodies of invoked functions or methods.

In particular:

- References returned by function or method calls are not assigned tracked target provenance based on the called function's implementation.
- Passing a variable through a mutable reference to a function or method does not change its move state.
- The compiler optimistically assumes that the called operation does not move the referenced value.

The `memory-move-through-reference` warning provides a safeguard for moves performed through mutable references in locally analyzed code.

### 12. Lambdas

Lambda bodies and their captured references are excluded from move analysis in the first version of the language.

## Function System

### 1. Function Declaration

Functions are declared using the `fn` keyword.

The general syntax is:

```gaia
fn identifier(parameters) [-> ReturnType] {
    statements
}
```

### 2. Function Parameters

Function parameters must specify their types.

The general syntax is:

```gaia
identifier: Type
```

Parameters may define default values using the `=` operator.

Example:

```gaia
fn connect(host: String, port: UInt16 = 8080) {
    print(host);
}
```

### 3. Return Types

Functions may specify their return type using `->`.

When no return type is specified, the return type defaults to the empty tuple type `()`.

Example:

```gaia
fn do_something() {
    print("Hello");
}

fn do_something_else() -> () {
    print("Hello");
}
```

### 4. Return Statement

The `return` keyword terminates the current function execution.

A return statement may provide a return value compatible with the function's declared return type.

### 5. Function Overloading

Gaïa supports function overloading.

Multiple functions may share the same identifier when their signatures are distinguishable.

Instance methods may also be overloaded according to the form of their `self` parameter.

The following forms of `self` are considered distinct for overload resolution:

- `self`
- `mut self`
- `move self`

Example:

```gaia
class Example {
    pub fn process(self) {
        print("Shared access");
    }

    pub fn process(mut self) {
        print("Mutable access");
    }

    pub fn process(move self) {
        print("Ownership transfer");
    }
}
```

### 6. Default Parameters

Function parameters may specify default values.

Default values are specified using the `=` operator.

### 7. Function Templates

Gaïa supports function templates.

Template parameter declaration, deduction and instantiation rules are specified separately.

### 8. Function Types

Function types describe callable entities through their parameter types and return type.

The general syntax is:

```gaia
fn(ParameterTypes) -> ReturnType
```

Example:

```gaia
let callback: fn(Int32, Int32) -> Int32 = add;
```

#### 8.1 Function Compatibility

Regular functions and non-capturing lambda expressions share the same function type when their signatures are identical.

They are interchangeable in contexts expecting that function type.

#### 8.2 Non-Capturing Lambdas

A lambda expression without captures produces a value of its corresponding function type.

Such lambdas do not require a separate callable object representation.

#### 8.3 Capturing Lambdas

A lambda expression with captures produces a callable object containing its capture context.

Its type explicitly describes its capture types and callable signature.

The general syntax is:

```gaia
fn [CaptureTypes] (ParameterTypes) -> ReturnType
```

Example:

```gaia
let offset = 10;

let add_offset: fn [&Int32] (Int32) -> Int32 =
    fn [&] (value: Int32) -> Int32 {
        return value + offset;
    };
```

The capture type list describes the data stored in the callable object's capture context.

#### 8.4 Callable Type Representation

Capturing callable types are distinct from ordinary function types.

Their type representation includes:

- Capture types and reference modes.
- Function parameter types.
- Return type.

The capture context is part of the callable object's representation.

#### 8.5 Capture Mutability

Capture mutability must be explicitly specified.

The compiler must not infer capture mutability from the operations performed inside the lambda body.

Capture declarations specify both the capture mode and its mutability.

The following forms are proposed:

```gaia
[&Type]       // Immutable reference capture
[&mut Type]   // Mutable reference capture
[Type]        // Immutable value capture
[mut Type]    // Mutable value capture
```

The resulting callable type includes the capture mode and mutability of each captured value.

A lambda cannot modify a captured value unless its capture declaration explicitly permits such modification.

#### 8.6 Callable Mutability

The mutability of a callable variable and the mutability of its captured state are independent concepts.

Variable mutability determines whether the variable holding a callable can be reassigned.

Capture mutability determines whether the captured data can be modified by the callable.

For value captures, the `mut` modifier explicitly determines whether the captured copy is mutable.

Example:

```gaia
let i = 42;

let callback = fn [mut i] () {
    i = i + 1;
};
```

In this example, the lambda owns a mutable copy of `i`.

The callable variable itself remains immutable and cannot be reassigned.

Declaring the callable variable as mutable only permits reassignment:

```gaia
let mut callback = fn [mut i] () {
    i = i + 1;
};
```

It does not implicitly modify the mutability of its captured state.

### 9. Lambda Expressions

Lambda expressions are introduced using the `fn` keyword.

The general syntax is:

```gaia
fn [captures] (parameters) [-> ReturnType] {
    statements
}
```

Lambda expressions produce callable values.

#### 9.1 Capture Syntax

Gaïa adopts the capture conventions of C++.

Supported capture forms include:

- `[&]`: Capture by reference.
- `[=]`: Capture by value.
- `[&value]`: Capture a specific variable by reference.
- `[value]`: Capture a specific variable by value.
- `[this]`: Capture the enclosing instance.
- `[&this]`: Capture the enclosing instance by reference.

Capture lists may combine multiple capture declarations, following the applicable capture rules.

#### 9.2 Lambda Conversion

Lambdas without captures are convertible to function pointers when their signatures are compatible.

Lambdas with captures produce callable objects and cannot be represented by ordinary function pointers.

Example:

```gaia
let callback: fn(Int32) -> () = fn (value: Int32) {
    print(value);
};
```

#### 9.3 Capturing Lambdas

Capturing lambdas produce callable objects containing their captured state.

Example:

```gaia
let value = 42;

let callback = fn [&] () {
    print(value);
};
```

#### 9.4 Explicit Capture Types

Gaïa supports an explicit capture type notation for lambda expressions.

The general syntax is:

```gaia
fn [CaptureTypes] (parameters) [-> ReturnType] {
    statements
}
```

Capture types describe the types and reference modes of the data stored in the lambda's capture context.

This notation makes the memory layout requirements of a capturing lambda more explicit and provides developers with better insight into the structure of the resulting callable object.

Example:

```gaia
fn [&Int32] (Int32) -> ()
```

In this example, the capture context contains an immutable reference to an `Int32`.

The capture type notation does not imply any additional memory safety guarantees.

### 10. Instance Methods

Instance methods must declare an explicit `self` parameter as their first parameter.

Gaïa provides three dedicated forms of self declaration.

#### 10.1 Shared Immutable Reference

```gaia
(self)
```

Equivalent to:

```gaia
(self: &Self)
```

#### 10.2 Shared Mutable Reference

```gaia
(mut self)
```

Equivalent to:

```gaia
(self: &mut Self)
```

#### 10.3 Ownership Transfer

```gaia
(move self)
```

Equivalent to:

```gaia
(move self: Self)
```

Example:

```gaia
class Player {
    health: Int32 = 100;

    pub fn get_health(self) -> Int32 {
        return self.health;
    }

    pub fn damage(mut self, amount: Int32) {
        self.health = self.health - amount;
    }

    pub fn consume(move self) {
        print("Player consumed");
    }
}
```

### 11. Constant Functions

A constant function is a function explicitly declared as eligible for compile-time evaluation using the `const` modifier.

```gaia
const fn factorial(n: UInt64) -> UInt64 {
    if n <= 1 {
        return 1;
    }

    return n * factorial(n - 1);
}
```

A `const fn` function may be evaluated at compile time whenever it is invoked in a context requiring a constant expression. It may also be called normally at runtime.

Constant functions may use any language construct or operation. No separate syntax or restricted language subset is imposed on them. However, an operation can only be evaluated at compile time if its semantics permit compile-time execution. If an operation cannot be evaluated in that context, an error is reported when its execution is required to produce a compile-time value.

Constant functions may call other constant functions, including recursively. This restriction applies transitively: every function executed during compile-time evaluation must itself be declared with `const fn`. Calling an ordinary function during such evaluation is not permitted.

The result of a constant function may be used to initialize a constant or as a non-type template argument.

```gaia
const FactorialOfFive = factorial(5);

class FixedArray<T, N: Size> {
    // ...
}

type FactorialArray<T> = FixedArray<T, factorial(5)>;
```

## Operator Overloading

### 1. General Principles

Gaïa supports operator overloading through instance methods.

Operators are declared as methods using their corresponding operator symbol as the method name.

The general syntax is:

```gaia
pub fn operator(self, parameters) [-> ReturnType] {
    statements
}
```

Example:

```gaia
class Vector2 {
    pub fn +(self, other: &Self) -> Self {
        return Vector2(
            self.x + other.x,
            self.y + other.y
        );
    }
}
```

### 2. Unary and Binary Operators

The distinction between unary and binary operators is determined by the number of explicit parameters.

An operator with no explicit parameters is unary.

An operator with one explicit parameter is binary.

The `self` parameter represents the operand on which the method is invoked and is not included in the parameter count.

### 3. Extension Operators

Operators may be overloaded for types that are not directly defined by the developer.

Such overloads are declared through the `extend` mechanism.

Extension operators follow the same declaration and resolution rules as operators defined directly inside a class.

Example:

```gaia
extend Int32 {
    pub fn +(self, other: &CustomType) -> CustomType {
        // ...
    }
}
```

### 4. Assignment Operators

Assignment operators may be overloaded like other operators. The assignment operator `=` is an ordinary overloadable operator, and its behavior may be customized for different source parameter types.

Assignment operators must respect the mutability requirements of their receiver.

#### 4.1 Initialization and Assignment

The `=` symbol used in a variable declaration does not invoke the assignment operator. In a declaration such as:

```gaia
let foo = Foo("bar", 42);
```

`=` only associates the name `foo` with the result of the initializer expression. The object is constructed through `Foo::init()`.

By contrast, `=` used in an assignment expression invokes the applicable assignment operator:

```gaia
let mut foo = Foo("bar", 42);
foo = Foo("baz", 24);
```

The syntactic context determines whether `=` denotes declaration initialization or assignment.

#### 4.2 Default Assignment Operator

When no assignment operator accepting `Self` is explicitly declared for a class, the compiler generates a default assignment operator for that class. This generated operator accepts only the same class type (`Self`) as its source operand. Explicit assignment overloads for other source types do not replace this default operator.

The default implementation assigns each instance attribute individually, using the assignment operator available for that attribute. Consequently, an attribute's own overloaded or default assignment behavior is respected.

The default assignment operator is not generated for other source types, even when an implicit conversion to `Self` exists.

#### 4.3 Assignment After Implicit Conversion

When an assignment expression's source operand is not `Self`, but can be implicitly converted to `Self`, the compiler first performs the applicable implicit conversion and then invokes the assignment operator for `Self`.

For example:

```gaia
class Foo {
    pub implicit init(mut self, value: Int32) {
        // ...
    }

    pub fn =(mut self, other: &Self) {
        // ...
    }
}

let mut foo = Foo(42);
foo = 24;
```

In the final statement, `24` is implicitly converted to `Foo` through the converting initializer `Foo::init(mut self, value: Int32)`. The resulting `Foo` value is then passed to the assignment operator. The conversion mechanism and assignment behavior remain distinct.

### 5. Compound Assignment Operators

Compound assignment operators, such as `+=`, `-=`, `*=`, and `/=`, may be explicitly overloaded or generated automatically.

Automatic generation is permitted when the corresponding assignment and binary operators are both available and compatible.

For example, when `=` and `+` are compatible, the compiler may generate `+=`.

The generated operation is semantically equivalent to:

```gaia
pub fn +=(mut self, other: &Self) {
    self = self + other;
}
```

Generated operators follow the ordinary overload resolution and conversion rules of Gaïa.

An explicitly declared compound assignment operator takes precedence over its automatically generated counterpart.

### 6. Comparison Operators

Comparison operators may be explicitly overloaded.

The supported comparison operators include:

- `==`
- `!=`
- `<`
- `>`
- `<=`
- `>=`

Gaïa also provides the `<=>` operator, allowing multiple comparison operations to be derived from a single method.

#### 6.1 Three-Way Comparison

The `<=>` operator returns a value representing the ordering relationship between two operands.

The language does not impose a dedicated return type for this operator.

Instead, comparison result values are provided by enums defined in the standard library.

A conventional ordering enum may contain the following values:

```gaia
enum Ordering {
    Less = -1,
    Equal = 0,
    Greater = 1,
    Unordered = 2
}
```

The numeric values and their corresponding enum members are defined by the standard library.

The compiler does not assign special semantics to these enums or their underlying numeric values.

#### 6.2 Automatic Comparison Generation

When a type defines `<=>`, the compiler may automatically generate the comparison operators that are not explicitly defined.

The generated operators are semantically equivalent to comparisons against the corresponding ordering values.

| Operator | Generated condition |
|---|---|
| `==` | Result equals `Equal` |
| `!=` | Result differs from `Equal` |
| `<` | Result equals `Less` |
| `>` | Result equals `Greater` |
| `<=` | Result equals `Less` or `Equal` |
| `>=` | Result equals `Greater` or `Equal` |

The generated operators use the equality and logical operations applicable to the return type of `<=>`.

#### 6.3 Partial Ordering

The `Unordered` result represents an ordering relationship that cannot be established.

This is particularly useful for floating-point comparisons involving values such as `NaN`.

When the result is `Unordered`:

- `==` evaluates to `false`.
- `!=` evaluates to `true`.
- `<` evaluates to `false`.
- `>` evaluates to `false`.
- `<=` evaluates to `false`.
- `>=` evaluates to `false`.

#### 6.4 Explicit Comparison Operators

Explicitly declared comparison operators take precedence over automatically generated counterparts.

When a type defines `<=>` and only some comparison operators explicitly, the compiler generates only the missing operators.

If `<=>` is not defined, no comparison operators are generated automatically.

### 7. Indexing Operator

The indexing operator `[]` is overloadable.

It may accept a variable number of parameters.

Example:

```gaia
class Matrix {
    pub fn [](self, row: Size, column: Size) -> Float32 {
        // ...
    }
}
```

### 8. Function Call Operator

The function call operator `()` is overloadable.

It may accept a variable number of parameters.

Example:

```gaia
class Callable {
    pub fn ()(self, value: Int32) -> Int32 {
        return value * 2;
    }
}
```

Objects implementing this operator may be invoked using ordinary function call syntax.

### 9. Deleted Operators and Implicit Operator Generation

The `delete` modifier can be applied to any operator declaration, including operators that would otherwise be generated implicitly by the compiler.

A deleted operator remains part of the overload set and participates normally in overload resolution. If overload resolution selects a deleted operator, the expression is ill-formed and a compilation error is reported. The compiler must not silently select another overload merely because the best matching overload is deleted.

This mechanism applies uniformly to all implicitly generated operators, regardless of how they are derived. This includes:

- Special member operations, such as default constructors, copy and move constructors, assignment operators, and destructors.
- Compound assignment operators that can be generated from the corresponding binary operator and assignment operator.
- Comparison operators derived from the three-way comparison operator (`<=>`).

An operator is generated implicitly when its required underlying operators are available and their signatures and types satisfy the requirements for that generation. An operator may itself be generated from other implicitly generated operators, allowing implicit generation to form a chain of dependencies.

For example, an assignment operator may be generated from the assignment operators of a class's attributes. This generated assignment operator can then be used to generate compound assignment operators.

An explicit declaration always takes precedence over implicit generation. This includes both ordinary operator definitions and deleted operator declarations. Consequently, declaring an operator as deleted prevents its implicit generation without affecting the operators that would otherwise have been used to generate it.

For example:

```gaia
class Number {
    pub fn +(self, other: Number) -> Number { ... }

    // The assignment operator may be generated implicitly.
    pub delete fn +=(mut self, other: Number);
}
```

In this example, `a = a + b` remains valid, while `a += b` is rejected because the corresponding operator has explicitly been deleted.

Similarly, comparison operators derived from `<=>` can be independently defined or deleted:

```gaia
class Version {
    pub fn <=>(self, other: Version) -> Ordering { ... }

    pub delete fn ==(self, other: Version);
    pub delete fn !=(self, other: Version);
}
```

Here, the ordering operators (`<`, `<=`, `>`, and `>=`) remain available, while equality comparisons (`==` and `!=`) are prohibited.

Deleting an implicitly generated operator does not affect the generation or availability of other operators in its dependency chain. Each operator is considered independently when determining whether it can be generated.

### 10. Inherited Operators

Operators declared as instance methods are inherited according to the same rules as other instance methods. Inherited operators participate in overload resolution, including the usual implicit conversions applied to their parameters.

An inherited operator may operate on the base subobject of a derived instance without requiring access to the derived class's additional attributes or implementation details.

A derived class may override an inherited operator or explicitly delete it. A deleted declaration prevents the corresponding operation from being selected through the derived class interface, without removing the original declaration from its base class.

### 11. Extension Operators

Operators declared through an extension follow the same rules as other extension methods. They are associated with the extended type and become candidates for overload resolution wherever the extension is accessible.

Extension operators may therefore participate in overload resolution for derived types as well, provided that the extension applies to one of their base classes and the required conversions are valid.

## Operator Overloading and Precedence

### 1. General Rules

Gaïa distinguishes operator precedence and associativity from operand evaluation order.

Precedence and associativity determine how an expression is grouped into an abstract syntax tree. They do not determine the order in which its operands are evaluated.

Unless an operator explicitly defines short-circuit evaluation, operands are evaluated from left to right. This rule also applies to overloaded operators: their operands are evaluated from left to right before the overloaded operation is invoked.

Parenthesized expressions are evaluated as a unit before being used by the enclosing expression.

Operators may be overloaded using functions whose names consist of the corresponding operator symbol. The receiver follows the ordinary function receiver rules (`self`, `mut self`, or `move self`), and the remaining operands are declared as ordinary parameters.

For example:

```gaia
fn +(self, other: Self) -> Self;
fn -(self) -> Self;
fn +=(mut self, other: Self);
```

The number and nature of operands determine whether an operator is used in prefix, infix, or postfix form. Prefix and postfix increment and decrement have dedicated declaration syntax, described below.

An operator may be unavailable for a type if it has neither a built-in implementation nor an applicable overload. Operators are not implicitly synthesized unless a specific synthesis rule is defined below.

### 2. Operator Precedence and Associativity

The following table lists operators from highest to lowest precedence.

| Precedence | Operators | Associativity |
|---|---|---|
| Postfix | `()`, `[]`, `.`, `->`, `?.`, postfix `++`, postfix `--` | Left |
| Conversion | `as` | Left |
| Prefix | prefix `++`, prefix `--`, unary `+`, unary `-`, `!`, `~`, unary `*`, unary `&`, `new`, `delete` | Right |
| Multiplicative | `*`, `/`, `%` | Left |
| Additive | `+`, `-` | Left |
| Shift | `<<`, `>>` | Left |
| Relational | `<=>`, `<`, `<=`, `>`, `>=` | Left |
| Equality | `==`, `!=` | Left |
| Bitwise AND | binary `&` | Left |
| Bitwise XOR | `^` | Left |
| Bitwise OR | `\|` | Left |
| Logical AND | `&&` | Left |
| Logical OR | `\|\|` | Left |
| Null coalescing | `??` | Right |
| Conditional | `?:` | Right |
| Assignment | `=`, `+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `\|=`, `^=`, `<<=`, `>>=` | Right |

Operators in the same precedence group have equal precedence.

The associativity of prefix operators is right-to-left. Postfix operators are left-to-right.

For example:

```gaia
value as Int16 as Int32 as Int64
```

is grouped as:

```gaia
((value as Int16) as Int32) as Int64
```

Similarly, assignment is right-associative:

```gaia
a = b = c
```

is grouped as:

```gaia
a = (b = c)
```

The left-to-right operand evaluation rule remains in effect independently of these grouping rules.

### 3. Member Access and Indirection

#### 3.1 Member access: `.`

The `.` operator performs member lookup and access. It automatically dereferences references when necessary.

It is a built-in operator and cannot be overloaded.

#### 3.2 Arrow access: `->`

The `->` operator is overloadable.

An overload of `->` must return a non-nullable reference (`&T`). The compiler then performs ordinary member lookup and access on the referenced object.

The overload therefore determines which object is accessed, but does not implement member lookup itself.

#### 3.3 Nullable member access: `?.`

The `?.` operator provides nullable member access.

An overload of `?.` must return a nullable reference (`*T`). The compiler checks this reference before performing member lookup:

- If the reference is null, the operation returns null without accessing a member.
- Otherwise, the compiler performs ordinary member lookup and access on the referenced object.

The `?.` operator may be synthesized from the `!` and `->` operators when both are available and no explicit `?.` overload is provided.

### 4. Arithmetic Operators

The arithmetic operators `+`, `-`, `*`, `/`, and `%` may be overloaded.

The unary forms of `+` and `-` may also be overloaded independently of their binary forms.

The `%` operator has a built-in implementation for integer types only. Floating-point remainder operations are provided through library functions rather than a built-in `%` operation.

### 5. Increment and Decrement

The prefix and postfix forms of `++` and `--` may be overloaded independently.

Their declaration syntax is special:

```gaia
fn ++(mut self) -> &Self;  // Prefix increment
fn (mut self)++ -> Self;   // Postfix increment

fn --(mut self) -> &Self;  // Prefix decrement
fn (mut self)-- -> Self;   // Postfix decrement
```

Prefix increment and decrement return a mutable reference to the modified object. Postfix increment and decrement return the value produced by the postfix operation.

These operators may be explicitly provided, synthesized, or unavailable according to the applicable operator-generation rules.

### 6. Bitwise Operators

The bitwise operators `&`, `|`, `^`, and `~` may be overloaded. The binary forms of `&`, `|`, and `^` and the unary form of `~` are distinct operator overloads.

The shift operators `<<` and `>>` may also be overloaded.

Built-in shift operations are not permitted on signed integer types. A signed value must first be explicitly converted to an unsigned type, or a suitable library function must be used.

Bitwise compound assignment operators (`&=`, `|=`, `^=`, `<<=`, and `>>=`) follow the compound-assignment generation rules described below.

### 7. Comparison Operators

The three-way comparison operator `<=>` is the fundamental comparison operator.

The operators `==`, `!=`, `<`, `<=`, `>`, and `>=` may be synthesized from `<=>` when no corresponding explicit overload or deletion is provided.

Each derived comparison operator may also be explicitly implemented or explicitly deleted independently.

The comparison operators are left-associative. They do not provide mathematical chained-comparison semantics.

### 8. Logical Operators

The logical operators `&&` and `||` are built-in and cannot be overloaded.

They use short-circuit evaluation:

- `&&` does not evaluate its right operand if its left operand evaluates to `false`.
- `||` does not evaluate its right operand if its left operand evaluates to `true`.

The unary logical negation operator `!` may be overloaded.

When no explicit `!` overload is provided, it may be synthesized from an implicit conversion to `Bool`.

### 9. Null Coalescing and Conditional Operators

The `??` operator dereferences a nullable reference or evaluates a fallback expression when the reference is null.

Its right operand is evaluated only when the left operand is null. The operator is right-associative.

The conditional operator `?:` evaluates its condition and then evaluates only the selected branch. It is right-associative.

Neither `??` nor `?:` can be overloaded.

### 10. Assignment Operators

The assignment operator `=` may be overloaded using the ordinary operator-function syntax:

```gaia
pub fn =(mut self, other: &Self);
```

A default assignment operator is generated for assignment from the same type (`Self`). It performs member-wise assignment.

Assignment from a different source type is handled through implicit conversion: the source value is first converted to `Self`, and the resulting value is then assigned using the `Self` assignment operator.

Compound assignment operators may be explicitly declared, explicitly deleted, or synthesized by aggregating the corresponding binary operator with assignment behavior.

The applicable compound assignment operators are:

- Arithmetic: `+=`, `-=`, `*=`, `/=`, `%=`.
- Bitwise: `&=`, `|=`, `^=`.
- Shifts: `<<=`, `>>=`.

Compound assignment operators have the same precedence and associativity as `=`.

### 11. Function Call and Indexing Operators

The function call operator `()` may be overloaded to make an object callable.

The indexing operator `[]` may also be overloaded. It accepts any number of arguments, rather than being restricted to a single index.

Both operators follow the ordinary operator-function declaration and receiver rules.

### 12. Conversion Operator

The `as` operator performs an explicit conversion to the specified target type.

It is not overloaded directly. The conversion mechanisms defined by the language determine which conversions are available, including implicit conversions and dynamic conversions involving polymorphic types.

Other conversion operations are provided through library functions.

### 13. Allocation and Deallocation Operators

The `new` and `delete` operators use the prefix precedence group.

Their allocation and deallocation behavior may be customized through the dedicated `extend` mechanism. This customization is distinct from ordinary operator-function overloading.

The allocation and deallocation operations for single objects and arrays can be customized independently. Their signatures, precedence rules, and error behavior are specified in the Dynamic Allocation section.

### 14. Built-in Macros

`sizeof`, `alignof`, and `typeof` are macros, not ordinary operators.

Their resolution follows the general macro-resolution rules. Syntactically, they have the same binding priority as function calls, but their evaluation and semantic behavior are governed by the macro system.

`sizeof` and `alignof` obtain the size and alignment of a type or expression without evaluating the expression at runtime. `typeof` obtains type information through the language's compile-time semantic facilities.

These macros cannot be overloaded as operators.

### 15. Operators That Cannot Be Overloaded

For clarity, the following operators and constructs cannot be overloaded:

- `.` — built-in member access.
- `&&` and `||` — built-in short-circuit logical operations.
- `??` — built-in nullable-reference coalescing.
- `?:` — built-in conditional selection.
- `as` — language-defined conversion mechanism.

The macros `sizeof`, `alignof`, and `typeof` are governed by macro rules rather than operator overloading.

### 16. Operator Synthesis

Gaïa supports operator synthesis through a set of composition rules. These rules form a hierarchy: an operator synthesized at one level may itself be used to synthesize another operator at a subsequent level.

Synthesis is conditional. An operator is generated only when the required operations exist and their operand, parameter, and result types are compatible with the requirements of the synthesized operation.

An explicitly declared operator takes precedence over its synthesized counterpart. An operator may also be explicitly deleted to prevent its synthesis or use.

#### 16.1 Assignment-Based Synthesis

The assignment operator `=` may be synthesized from the assignment mechanisms of the underlying types. For aggregate types, this allows member-wise assignment to be generated according to the rules governing their constituent types.

Compound assignment operators may then be synthesized by combining an assignment operator with its corresponding binary operator.

For example:

- `+` and `=` may synthesize `+=`.
- `-` and `=` may synthesize `-=`.
- `*` and `=` may synthesize `*=`.
- `/` and `=` may synthesize `/=`.
- `%` and `=` may synthesize `%=`.
- `&` and `=` may synthesize `&=`.
- `|` and `=` may synthesize `|=`.
- `^` and `=` may synthesize `^=`.
- `<<` and `=` may synthesize `<<=`.
- `>>` and `=` may synthesize `>>=`.

The binary operator and the assignment operator must use compatible types for the compound assignment operator to be synthesized. The resulting operation must preserve the required semantics of the corresponding binary operation followed by assignment.

The same rules apply to all binary operators that are compatible with assignment.

#### 16.2 Increment and Decrement Synthesis

Prefix and postfix increment operators may be synthesized from the corresponding compound assignment operator when the type is compatible with addition by an integer value.

Similarly, prefix and postfix decrement operators may be synthesized from the corresponding compound assignment operator when the type is compatible with subtraction by an integer value.

For example:

- `+=` may synthesize `++` when addition by an integer value is supported.
- `-=` may synthesize `--` when subtraction by an integer value is supported.

Increment and decrement synthesis follows the same compatibility requirements as the underlying compound assignment operation. The generated prefix and postfix forms retain their respective return semantics.

#### 16.3 Comparison Synthesis

The three-way comparison operator `<=>` may synthesize the following comparison operators:

- `==`
- `!=`
- `<`
- `<=`
- `>`
- `>=`

Each of these operators may also be explicitly implemented or explicitly deleted independently.

#### 16.4 Nullable Member Access Synthesis

The nullable member access operator `?.` may be synthesized from the logical negation operator `!` and the arrow member access operator `->`.

This synthesis provides the nullable-reference check and the subsequent member access behavior defined for `?.`.

#### 16.5 Logical Negation Synthesis

The logical negation operator `!` may be synthesized from an implicit conversion to `Bool`.

The synthesized operator returns the logical negation of the converted Boolean value.

### 17. Summary of Synthesis Rules

The operator synthesis relationships can be summarized as follows:

| Available operations | Synthesized operator |
|---|---|
| Underlying type assignment mechanisms | `=` |
| A compatible binary operator and `=` | Corresponding compound assignment |
| A compatible `+=` and integer addition | Prefix and postfix `++` |
| A compatible `-=` and integer subtraction | Prefix and postfix `--` |
| `<=>` | `==`, `!=`, `<`, `<=`, `>`, `>=` |
| `!` and `->` | `?.` |
| Implicit conversion to `Bool` | `!` |

## Type Aliases

A type alias introduces an alternative name for an existing type using the `type` keyword.

```gaia
type Integer = Int32;
type StringList = List<String>;
```

A type alias does not create a new nominal type. The alias and the original type are considered identical for type checking, overload resolution, and type compatibility. An alias may be used anywhere its underlying type is valid.

Type aliases may use type inference only when an initializer is available through the language's applicable declaration rules. Type aliases do not introduce runtime values or generate additional types.

Generic type aliases are supported and are described in the **Templates** section. They follow the same template parameter, deduction, and constraint rules as other templates.

## Constants

A constant is a named value that must be fully evaluated at compile time. Constants are declared using the `const` keyword.

```gaia
const Pi: Float64 = 3.141592653589793;
const Answer = 42;
```

An initializer is mandatory in every constant declaration. A constant cannot rely on implicit default initialization, even if its type provides a default constructor.

The type of a constant may be explicitly specified. If omitted, the compiler infers it from the initializer expression.

The initializer must be a constant expression: its value must be determinable entirely at compile time. Such expressions may involve language primitives and operations that are valid during compile-time evaluation, as well as calls to functions declared with `const fn`.

A `const fn` function is explicitly permitted to participate in compile-time evaluation. Such a function may call other `const fn` functions, including recursively. Every function executed as part of a constant expression must be declared `const fn`. Calling an ordinary function during compile-time evaluation is not permitted, regardless of whether its implementation happens to be free of side effects.

Constants may have any type, provided that their initializer can produce a valid value of that type at compile time. This includes user-defined types when their construction is valid during compile-time evaluation.

Constants are immutable and their values are known at compile time. They may be used anywhere a constant expression is required, including as non-type template arguments.

Unlike immutable variables declared with `let`, constants do not represent runtime values whose initialization merely happens to be immutable. Their values are established during compilation.

## Classes

### 1. Class Declaration

Classes are declared using the `class` keyword.

The general syntax is:

````gaia
class ClassName {
    members...
}
````

A class may contain attributes and member functions, including constructors and destructors.

Class members are private by default.

The `pub` modifier makes a member publicly accessible from outside the class.

Example:

````gaia
class Player {
    name: String = "Unknown";
    health: Int32 = 100;

    pub fn get_health(self) -> Int32 {
        return self.health;
    }
}
````

### 2. Attribute Declaration

Attributes are declared by specifying their identifier, type and optional initializer.

The general syntax is:

````gaia
identifier: Type [= expression];
````

Attributes do not use the `let` or `mut` keywords.

The mutability of an attribute is inherited from the mutability of the enclosing instance access.

Consequently:

- `self` provides immutable access to the instance and its attributes.
- `mut self` provides mutable access to the instance and its attributes.
- `move self` transfers ownership of the instance.

Attribute initializers are optional.

Providing an initializer directly in the declaration is recommended whenever a meaningful default value exists.

### 3. Attribute Initialization

An attribute may be initialized either through its declaration initializer or through a constructor.

An initializer declared alongside an attribute provides its default initialization value.

When no declaration initializer is provided, the attribute may rely on the default constructor of its type.

An attribute without a declaration initializer is only valid when either:

- Every constructor of the enclosing class guarantees its initialization.
- Its type provides a default constructor that can be invoked automatically.

The compiler must ensure that every attribute is initialized before it is used.

### 4. Constructor Initialization

Constructors are declared using the special `init` method.

A constructor may explicitly initialize attributes by assigning values to them through `self`.

When an attribute is explicitly initialized by a constructor before any operation requires its default initialization, the constructor-provided value is used directly. Its declaration initializer or default constructor is not invoked.

Example:

````gaia
class Player {
    name: String = "Unknown";
    health: Int32 = 100;

    pub init(mut self, name: String, health: Int32) {
        self.name = name;
        self.health = health;
    }
}
````

In this example, both attributes are initialized directly using the constructor parameters. Their declaration initializers are not evaluated.

### 5. Default Initialization

Default initialization is performed whenever an attribute has not yet been explicitly initialized and its initialization cannot be guaranteed before its next use.

The compiler must invoke the declaration initializer when one exists. Otherwise, it must invoke the default constructor of the attribute's type.

Default initialization is also performed when a constructor completes without explicitly initializing an attribute.

This mechanism ensures that attributes always have a valid initialized state before they are accessed.

### 6. Initialization Safety

A constructor must never read or otherwise use an attribute before that attribute has been initialized.

The compiler performs control flow analysis to determine whether an attribute is guaranteed to be initialized before its first use.

An explicit initialization is considered guaranteed only when every possible execution path reaching the relevant point performs that initialization.

When initialization cannot be proven, default initialization must be performed before the potentially unsafe operation.

This includes, but is not limited to:

- Conditional initialization that does not cover every possible branch.
- Calls to instance methods before the initialization state of the attributes they may access is established.
- Other operations that may access an attribute whose initialization state is ambiguous.

Example of valid conditional initialization:

````gaia
class Container {
    value: Int32;

    pub init(mut self, value: Input) {
        if value.is_valid() {
            self.value = value.get();
        }
        else {
            self.value = make_default_value();
        }
    }
}
````

Both branches explicitly initialize the attribute. Therefore, no default initialization is required.

Example of conditional initialization requiring a default value:

````gaia
class Container {
    value: Int32 = 0;

    pub init(mut self, value: Input) {
        if value.is_valid() {
            self.value = value.get();
        }
    }
}
````

Since the attribute is not explicitly initialized on every possible execution path, its declaration initializer must be evaluated whenever the constructor does not initialize it explicitly.

The compiler must adopt a conservative approach whenever the initialization state of an attribute is ambiguous.

### 7. Static Members

Class members may be declared as static using the `static` modifier.

Static members belong to the class itself rather than to individual instances. They can be accessed using the class name and the `::` scope resolution operator.

Static attributes are initialized at program startup, independently of whether an instance of their class is ever created.

Static methods do not receive an instance parameter and may directly access other static members of their class.

Example:

```gaia
class Registry {
    static entries: Map<String, Int32> = Map();

    pub static fn count() -> Int32 {
        return Registry::entries.size();
    }
}
```

Static local variables may be declared inside static methods to provide lazy initialization.

Unlike static class attributes, static local variables are initialized only when execution first reaches their declaration.

Their initialization must be thread-safe. When multiple threads reach the declaration concurrently, initialization must occur exactly once, and other threads must wait until initialization is complete.

Once initialized, a static local variable retains its value for the remainder of the program's execution. Subsequent executions of its declaration do not trigger reinitialization.

Example:

```gaia
class Registry {
    pub static fn instance() -> Registry {
        static registry: Registry = Registry();
        return registry;
    }
}
```

Static class attributes and static local variables are destroyed automatically when the program terminates, provided their types have a destructor.

### 8. Method Declaration

Methods must explicitly declare whether they operate on an instance or on the class itself.

An instance method must declare an explicit `self` parameter. The receiver may use any of the supported ownership and mutability forms:

- `self` for immutable access.
- `mut self` for mutable access.
- `move self` to take ownership of the instance.

An instance method must not be declared with the `static` modifier.

A static method must be declared using the `static` modifier and must not declare a `self` parameter.

A method declaration is invalid if neither or both of these conditions are satisfied. Exactly one of the following must apply:

- The method declares a `self` parameter and is not static.
- The method is static and does not declare a `self` parameter.

Example:

```gaia
class Player {
    pub fn get_health(self) -> Int32 {
        return self.health;
    }

    pub fn set_health(mut self, health: Int32) {
        self.health = health;
    }

    pub static fn create() -> Player {
        return Player();
    }
}
```

### 9. Method Overloading

Methods support overloading using the same rules as free functions.

Multiple methods may share the same name, provided their signatures are distinguishable according to the general overload resolution rules.

Overloading applies equally to instance and static methods.

The presence or absence of the `self` parameter is part of the method signature and may distinguish otherwise identical overloads. The `static` modifier does not introduce a separate overload namespace.

Consequently, a static method and an instance method may share the same name.

Example:

```gaia
class Player {
    pub fn create(self, name: String) -> Player {
        // ...
    }

    pub static fn create() -> Player {
        // ...
    }

    pub fn set_health(mut self, health: Int32) {
        self.health = health;
    }

    pub fn set_health(mut self, health: Float32) {
        self.health = health as Int32;
    }
}
```

Method overload resolution follows the same rules as free function overload resolution, including the applicable implicit conversion rules.

### 10. Visibility

Class members are private by default. Their visibility can be explicitly modified using the following modifiers:

- `pub`: makes the member publicly accessible.
- `pub(sub)`: makes the member protected, accessible from the declaring class and its derived classes.
- No modifier: keeps the member private, accessible only from the class that declares it.

These visibility modifiers apply uniformly to both attributes and methods.

For example:

```gaia
class Base {
    pub public_field: Int32;
    pub(sub) protected_field: Int32;
    private_field: Int32;

    pub fn public_method(self) {}
    pub(sub) fn protected_method(self) {}
    fn private_method(self) {}
}
```

A member can also grant access to specific types by listing them in a visibility modifier:

```gaia
class Foo {
    pub(Bar, Baz) fn internal_task(self) {}
}
```

In this example, `Bar` and `Baz` are explicitly granted access to `internal_task`, even though the member is not publicly accessible.

This form of visibility is equivalent to the friendship mechanism found in C++. The granted access is limited to the explicitly listed types and follows these rules:

- Access is not inherited: derived classes of a granted type do not automatically receive the same access.
- Access is not transitive: types granted access by another type do not inherit that privilege.
- Access is not reciprocal: granting a type access to a member does not grant the declaring class access to the granted type's private members.

The listed types therefore receive access privileges only for the members that explicitly grant them access.

### 11. Multiple Inheritance

Gaïa supports multiple inheritance, following the same semantics as C++. A class may inherit from multiple base classes, each of which contributes its own subobject to the derived class.

The visibility of an inheritance relationship determines how the base class interface and the substitutability of the derived type are exposed:

- **Public inheritance (`pub`)**: the derived class can be used wherever its base class is expected, subject to the usual type compatibility rules.
- **Protected inheritance (`pub(sub)`)**: the inheritance relationship is accessible within the derived class and its own derived classes, but not from outside.
- **Private inheritance (default)**: the inheritance relationship is accessible only within the derived class itself.

Inheritance visibility can be understood similarly to the visibility of a conceptual member representing the base-class subobject. The key distinction from ordinary composition is that inheritance also establishes a relationship between types, which may allow a derived type to be substituted for its base type depending on the inheritance visibility.

For example:

```gaia
class Base {
    pub fn method(self) {}
}

class PublicDerived : pub Base {
}

class ProtectedDerived : pub(sub) Base {
}

class PrivateDerived : Base {
}
```

A derived class inherits the members of its base classes according to the visibility rules of the inheritance relationship and the visibility of the inherited members themselves.

### 12. Virtual Inheritance

Gaïa supports virtual inheritance using the `virtual` keyword, following the same semantics as C++.

Virtual inheritance ensures that a shared base class is represented by a single base subobject when it is inherited through multiple paths in a class hierarchy. This is particularly useful for resolving the diamond inheritance problem.

For example:

```gaia
class Base {
    pub fn method(self) {}
}

class Left : pub virtual Base {
}

class Right : pub virtual Base {
}

class Diamond : pub Left, pub Right {
}
```

In this example, `Diamond` contains only one `Base` subobject, shared by both `Left` and `Right`.

Non-virtual inheritance retains the usual C++ semantics: each inheritance path contributes its own base subobject, which may result in multiple instances of the same base class within a derived object.

### 13. Base Class Initialization

When a class inherits from one or more base classes, their constructors must be invoked as part of the derived class initialization.

Base class initialization uses a dedicated syntax within the derived class constructor:

```gaia
class Base {
    pub init(mut self, value: Int32) {
        self.value = value;
    }
}

class Derived : pub Base {
    pub init(mut self, value: Int32) {
        Base::init(value);
        self.value = value;
    }
}
```

A `Base::init(arguments)` statement appearing at the beginning of a constructor is treated as an initialization directive for the corresponding base subobject, rather than as an ordinary method call.

Explicit base initialization directives must appear before any other operation that depends on the state of the current instance. However, preliminary computations that do not access any attribute of the current instance are permitted before these directives. This allows constructor arguments to be computed before initializing the base classes.

For example:

```gaia
pub init(mut self, value: Int32) {
    let base_value = value * 2;
    Base::init(base_value);

    self.value = value;
}
```

A base class whose initialization is omitted is automatically initialized using its default constructor, provided one is available. If no default constructor exists and no explicit initialization is provided, the program is ill-formed.

The order in which base initialization directives appear in the constructor does not affect the actual construction order. Base classes are always initialized according to the inheritance order rules.

### 14. Virtual Base Initialization

Virtual base classes are initialized exclusively by the constructor of the most-derived class.

When a class is constructed as a base subobject of another class, its own constructor cannot determine the initialization of virtual base classes. Any initialization directives targeting virtual bases in such a constructor are ignored.

The most-derived class is responsible for explicitly initializing its virtual base classes when necessary. If their initialization is omitted, their default constructors are invoked when available. Otherwise, an explicit initialization is required.

Each virtual base subobject is initialized exactly once, regardless of how many inheritance paths lead to it.

### 15. Construction and Destruction Order

The construction and destruction order follows the same rules as C++.

Construction proceeds in the following order:

1. Virtual base classes are initialized first, following their order of appearance in the depth-first, left-to-right traversal of the inheritance graph.
2. Direct non-virtual base classes are initialized in their declaration order.
3. Instance attributes are initialized in their declaration order.
4. The constructor body is executed.

Destruction occurs in the exact reverse order:

1. The destructor body is executed.
2. Instance attributes are destroyed in reverse declaration order.
3. Direct non-virtual base classes are destroyed in reverse declaration order.
4. Virtual base classes are destroyed in the reverse order of their construction.

This ordering is independent of the order in which explicit base initialization directives appear in the constructor.

### 16. Destructors

A class may declare a single destructor using the `deinit` keyword. Destructors cannot be overloaded.

A destructor uses the same receiver syntax as other instance methods:

```gaia
class Resource {
    pub deinit(mut self) {
        // Release resources
    }
}
```

The destructor is invoked automatically when an instance reaches the end of its lifetime.

The destructor body is executed before the destruction of the instance's attributes and base classes. Attributes and base classes are then destroyed in the reverse order of their construction, following the rules defined in the construction and destruction order section.

A class does not need to declare a destructor explicitly. If no destructor is provided, the compiler generates a default destructor that performs the required destruction of its attributes and base classes.

### 17. Polymorphic Classes

A class can be declared polymorphic using the `virtual class` declaration.

A polymorphic class has a virtual method table (vtable), enabling dynamic dispatch for its virtual methods. Its destructor is automatically virtual, ensuring that instances are correctly destroyed when accessed through a base class reference or pointer.

A class derived from a polymorphic class is itself polymorphic and inherits this property, even if it does not declare any virtual methods of its own.

For the initial version of Gaïa, a polymorphic class may only inherit from classes that already have a virtual destructor. Consequently, every class in a polymorphic inheritance hierarchy must belong to a polymorphic hierarchy.

A class cannot declare a virtual destructor independently of being polymorphic. The `virtual` modifier cannot be applied to `deinit`, since destructor virtuality is determined by the polymorphic nature of the class.

### 18. Virtual Methods and Overrides

Methods can participate in dynamic dispatch by using the `virtual` modifier.

A virtual method can only be declared within a polymorphic class or a class derived from one.

When a derived class provides a new implementation for an inherited virtual method, it must use the `override` modifier instead of `virtual`.

The compiler verifies that an overridden method matches an existing virtual method in a base class. Declaring `override` without a matching virtual method is a compilation error.

For example:

```gaia
virtual class Shape {
    pub virtual fn area(self) -> Float64;
}

class Circle : pub Shape {
    pub override fn area(self) -> Float64 {
        return 3.14159 * self.radius * self.radius;
    }
}
```

Virtual methods retain their virtual nature throughout the inheritance hierarchy. Further derived classes can override them without having to redeclare them as `virtual`.

### 19. Final Classes and Methods

The `final` modifier prevents further inheritance or overriding.

A class declared `final` cannot be used as a base class. A polymorphic class may also be declared `final`, retaining its polymorphic behavior while preventing further derivation.

A virtual method can be declared `final` to prevent derived classes from overriding it.

An overridden method can also be declared `final`, thereby ending further overrides at that point in the inheritance hierarchy.

For example:

```gaia
virtual class Shape {
    pub virtual fn area(self) -> Float64;
}

class Circle : pub Shape {
    pub final fn area(self) -> Float64 {
        return 3.14159 * self.radius * self.radius;
    }
}

virtual class FinalShape final {
    pub virtual fn area(self) -> Float64;
}
```

Attempting to derive from a `final` class or override a `final` method results in a compilation error.

### 20. Abstract Classes and Methods

A polymorphic class becomes abstract when it declares at least one virtual method without an implementation.

An abstract method is declared using the `virtual` modifier without providing a method body:

```gaia
virtual class Shape {
    pub virtual fn area(self) -> Float64;
}
```

A class containing at least one abstract method cannot be instantiated directly.

A derived class remains abstract as long as it does not provide implementations for all inherited abstract methods. Once all abstract methods have been implemented, the derived class becomes concrete and can be instantiated, unless it declares additional abstract methods of its own.

Abstract classes may declare attributes, constructors, destructors, and implemented methods. They may also inherit from other abstract classes.

Constructors of abstract classes are executed normally when the class is initialized as a base subobject of a concrete derived class. This allows abstract classes to initialize their own attributes and establish their invariants.

There is no separate interface construct. Abstract classes provide the same inheritance and polymorphism mechanisms as other classes.

### 21. Virtual Method Calls During Construction and Destruction

Virtual method dispatch is restricted during construction and destruction to prevent calls from reaching implementations belonging to parts of an object that are not yet fully constructed or have already been destroyed.

A direct, unqualified call to a virtual method from within a constructor or destructor generates a compiler warning.

The warning can be promoted to an error through the general diagnostic promotion mechanism.

To explicitly invoke a particular implementation, the method must be called using a qualified name:

```gaia
virtual class Base {
    pub init(mut self) {
        Base::initialize();
    }

    pub virtual fn initialize(self) {}

    pub deinit(mut self) {
        Base::initialize();
    }
}

class Derived : pub Base {
    pub override fn initialize(self) {}
}
```

A qualified call explicitly selects the implementation belonging to the specified class and does not perform dynamic dispatch.

This warning applies only to direct virtual method calls appearing in the body of a constructor or destructor. Calls performed indirectly through other methods are not subject to this diagnostic in the initial version of the language.

### 22. Inherited Method Overloads

Methods inherited from base classes are automatically included in the overload sets of the derived class. Unlike C++, no `using` declaration is required to make inherited overloads available alongside methods declared in the derived class.

Declaring a method with a different signature does not hide inherited overloads with the same name. All accessible inherited overloads remain available and participate in overload resolution.

When multiple base classes provide methods with the same name and signature, the corresponding declarations remain distinct. An unqualified call is ambiguous if overload resolution cannot identify a unique declaration, even when the candidate methods have otherwise identical signatures.

A method can be explicitly selected from a particular base class using qualified member access:

```gaia
class A {
    pub fn process(value: Int32) {}
}

class B {
    pub fn process(value: Int32) {}
}

class C : pub A, pub B {}

let instance = C();
instance.A::process(42);
instance.B::process(42);
```

Qualified member access selects the method through the specified base-class subobject. It can therefore be used to resolve ambiguities caused by multiple inheritance. If the specified base class occurs more than once in the inheritance hierarchy and the qualification does not identify a unique subobject, the access remains ambiguous.

### 23. Overriding Methods from Multiple Base Classes

A single method declaration in a derived class can override multiple inherited virtual methods when they have compatible signatures and satisfy the overriding requirements.

This allows a derived class to provide one common implementation for identical virtual methods inherited from different base classes.

```gaia
virtual class A {
    pub virtual fn process(self, value: Int32) {}
}

virtual class B {
    pub virtual fn process(self, value: Int32) {}
}

class C : pub A, pub B {
    pub override fn process(self, value: Int32) {}
}
```

The inherited base-class subobjects remain distinct unless virtual inheritance makes them shared. Only the final overrider is shared by the corresponding virtual methods.

### 24. Deleted Methods

A method can be explicitly declared as deleted using the `delete` modifier. A deleted method remains part of its overload set and participates in overload resolution, but attempting to call it is a compile-time error.

```gaia
class Base {
    pub fn reset() {}
}

class Derived : pub Base {
    pub delete fn reset();
}
```

In this example, calls to `reset` through the interface of `Derived` are rejected. The declaration does not remove the original method from the base-class subobject. Explicitly qualifying the call through `Base` can still access the base-class implementation.

Conversely, if a method is declared as deleted in a base class, it remains unavailable through that base-class interface, including through qualified access.

The `delete` modifier can also be used to disable implicitly generated special member functions or explicitly declared operations.

For example, a class can prevent copy assignment by deleting its assignment operator:

```gaia
class NonCopyable {
    pub delete fn =(mut self, other: &Self);
}
```

Deleted declarations take precedence over implicitly generated operations with the same signature. The compiler must not generate an operation that conflicts with an explicitly deleted declaration.

### 25. Inherited Attributes

Attributes inherited from base classes remain members of their respective base-class subobjects. They are accessible through instances of derived classes according to the visibility rules of inheritance and member declarations.

When multiple base classes provide an attribute with the same name, an unqualified access is ambiguous if the lookup identifies multiple possible declarations. The compiler does not arbitrarily select one declaration, even when one of the declarations is introduced in an intermediate base class.

An ambiguous attribute can be explicitly selected using qualified member access:

```gaia
class A {
    pub value: Int32;
}

class B : pub A {}
class C : pub A {}
class D : pub B, pub C {}

let instance = D();
instance.B::A::value = 10;
instance.C::A::value = 20;
```

Qualified member access selects the attribute through the specified inheritance path. If multiple paths lead to the same virtual base-class subobject, they designate the same attribute and do not introduce ambiguity.

### 26. Inherited Static Members

Static attributes and methods belong to the class in which they are declared, rather than to individual instances or base-class subobjects.

Static members are inherited and can be accessed through derived classes when their names are unambiguous. However, if multiple base classes provide static members with the same name, access through the derived class is ambiguous.

In such cases, the declaring class must be explicitly specified:

```gaia
class A {
    pub static count: Int32 = 0;
}

class B {
    pub static count: Int32 = 0;
}

class C : pub A, pub B {}

// Ambiguous:
// C::count;

// Explicit qualification:
A::count;
B::count;
```

### 27. Member Lookup in Multiple Inheritance

Member lookup in multiple inheritance considers all applicable declarations throughout the inheritance hierarchy. If lookup identifies multiple possible declarations, an unqualified access is ambiguous.

Gaïa does not implicitly prioritize a declaration introduced in an intermediate base class over another declaration inherited through a different path.

Explicit qualification can be used to select a particular declaration and, when necessary, a particular base-class subobject.

Virtual inheritance does not introduce ambiguity when multiple inheritance paths lead to the same shared virtual base-class subobject.

For example:

```gaia
class A {
    pub value: Int32;
}

class B : pub virtual A {}
class C : pub virtual A {}
class D : pub B, pub C {}

let instance = D();

// All accesses designate the same shared A subobject.
instance.value;
instance.B::A::value;
instance.C::A::value;
```

### 28. Member Access Through Self

Member access through `self` follows a local lookup rule that differs from ordinary member lookup on an instance.

When resolving `self.attribute` inside a class method, the compiler first searches for an attribute declared directly in the class defining that method. If such an attribute exists, it takes precedence over inherited attributes with the same name.

If the current class does not declare the requested attribute, lookup continues through its base classes. If multiple possible declarations remain, the access is ambiguous and requires explicit qualification.

This rule ensures that the meaning of attribute accesses within a class does not change merely because additional base classes are introduced into a derived class.

```gaia
class A {
    pub value: Int32;
}

class B : pub A {
    pub value: Int32;

    pub fn update(mut self) {
        // Refers to B::value.
        self.value = 42;

        // Explicitly refers to A::value.
        self.A::value = 10;
    }
}
```

### 29. Qualified Member Access

A member inherited from a particular base class can be explicitly selected using the declaring class as a qualifier:

```gaia
instance.Base::method();
instance.Base::attribute;
```

Qualified member access selects the corresponding base-class declaration and bypasses ambiguities that would otherwise arise during unqualified lookup.

For virtual methods, qualification explicitly selects the implementation associated with the specified class and suppresses dynamic dispatch, as with qualified virtual function calls in C++.

For non-virtual methods and attributes, qualification selects the corresponding member in the specified base-class subobject.

When the specified base class occurs multiple times in the inheritance hierarchy, the qualification must identify a unique base-class subobject. Otherwise, the access remains ambiguous.

### 30. Constructor Inheritance

Constructors are not inherited implicitly. Each class defines its own set of constructors, independently of the constructors declared by its base classes. This ensures that constructing a derived class always requires an explicit decision about how its base subobjects are initialized.

A class may explicitly introduce constructors from one of its base classes using a qualified constructor declaration:

```gaia
class Base {
    pub init(mut self, value: Int32) {}
    pub init(mut self, name: String) {}
}

class Derived : pub Base {
    pub Base::init;
}
```

A declaration of the form `Base::init;` introduces all ordinary constructor overloads declared by `Base` into the constructor set of `Derived`. Individual overloads may also be introduced selectively by specifying their signatures:

```gaia
class Derived : pub Base {
    pub Base::init(mut self, value: Int32);
}
```

Introduced constructors become constructors of the derived class. Invoking one initializes the corresponding base subobject using the selected base constructor and initializes the derived class's own attributes according to their declaration initializers and default initialization rules.

The visibility modifier on the introduction declaration determines the accessibility of the introduced constructor through the derived class.

Constructors declared directly in the derived class may overload introduced constructors. If a constructor declared in the derived class has the same signature as an introduced constructor, the derived declaration takes precedence. Other introduced overloads remain available.

Only ordinary constructors are introduced through this mechanism. Copy and move constructors follow their own generation and deduction rules and are not inherited through constructor declarations.

### 31. Default Constructor Generation

A default constructor is implicitly generated when all of the following conditions are met:

- Every instance attribute either has a declaration initializer or has a type that provides a default constructor.
- Every direct and virtual base class can be default-constructed.
- No constructor other than a copy or move constructor has been explicitly declared in the class.

The implicitly generated default constructor initializes base subobjects and instance attributes according to the normal construction rules. Attributes with declaration initializers use those initializers; other attributes are initialized using their type's default constructor.

An explicitly declared ordinary constructor, including a deleted constructor, prevents implicit generation of the default constructor. Explicitly declaring a copy or move constructor does not, by itself, prevent its generation.

A default constructor declared in a base class is not automatically available in a derived class. It must be explicitly introduced using the constructor introduction mechanism if it is to be used as a constructor of the derived class.

### 32. Copy and Move Constructor Generation

Copy and move constructors are generated independently.

An implicit copy constructor is generated if every base subobject and every instance attribute can be copy-constructed. Its implementation copy-constructs each base subobject and attribute from the corresponding subobject of the source instance.

An implicit move constructor is generated if every base subobject and every instance attribute can be move-constructed. Its implementation move-constructs each base subobject and attribute from the corresponding subobject of the source instance.

The availability of one operation does not imply the availability of the other. In particular, the compiler does not fall back to copy construction when move construction is unavailable, or to move construction when copy construction is unavailable. A user-defined constructor may implement either behavior explicitly.

Explicitly declaring a copy constructor does not prevent the generation of a move constructor, and explicitly declaring a move constructor does not prevent the generation of a copy constructor. Ordinary user-defined constructors do not affect the generation of either operation.

A user-defined destructor prevents implicit generation of the move constructor. An implicitly generated destructor or an explicitly deleted destructor does not have this effect.

Copy and move constructors of base subobjects participate in the corresponding generation process of the derived class. They are handled automatically and do not need to be explicitly introduced using the constructor introduction mechanism.

### 33. Implicit Destructor Generation

If a class does not explicitly declare a destructor, the compiler automatically generates one. Unlike other special member functions, a destructor is always generated and cannot be implicitly deleted.

The generated destructor invokes the destructors of all instance attributes and base subobjects. Attribute destructors are invoked in reverse declaration order, followed by base class destructors in reverse construction order. Virtual base subobjects are destroyed exactly once, according to the previously defined destruction order.

A class must be able to invoke the destructor of every base subobject and instance attribute it owns. If a base class has a private destructor, deriving from that class is ill-formed because the derived class cannot invoke the base destructor.

### 34. Destructor Visibility

The visibility of an implicitly generated destructor is determined by the visibility of the destructors of its base classes.

If all base class destructors are public, the generated destructor is public by default. If at least one base class destructor is protected and none is private, the generated destructor is protected by default.

An explicitly declared destructor may specify its own visibility, independently of the default visibility determined by its base classes. In particular, a class may explicitly declare a public destructor even when its generated destructor would otherwise be protected.

The visibility of destructors does not affect the destruction order or the automatic invocation of destructors for attributes and base subobjects.

### 35. Construction Failure

If the construction of an object fails, the object's destructor is not invoked because the object never reaches a fully constructed state.

However, all base subobjects and instance attributes whose construction completed successfully are destroyed normally. Their destructors are invoked in the reverse order of their construction, following the usual destruction rules.

Subobjects whose construction failed are not destroyed. This ensures that destructors are only invoked for fully constructed objects.

### 36. Static Attribute Initialization and Destruction

Static attributes are initialized in the order in which the compiler discovers them during compilation.

At program termination, initialized static attributes are destroyed in the exact reverse order of their initialization. An attribute whose initialization did not complete successfully is not destroyed.

### 37. Copying Derived Objects into Base Objects

Copying an object of a derived class into an object of a base class copies only the corresponding base subobject. This applies to both copy construction and copy assignment.

The operation uses the copy constructor or copy assignment operator of the base class, respectively. Attributes and base subobjects belonging exclusively to the derived class are not copied.

This behavior is commonly referred to as object slicing.

In contrast, converting a pointer to a derived class into a pointer to one of its base classes does not copy or slice the object. The pointer refers to the corresponding base subobject of the original object, and its dynamic type remains unchanged.

### 38. Polymorphic Destruction and Access Control

When an object is destroyed through a pointer to a polymorphic base class, destructor accessibility is checked using the static type of the pointer and the context initiating destruction.

Once access has been granted, the actual destructor is selected dynamically through the virtual dispatch mechanism. The destructor corresponding to the object's dynamic type is invoked, even if that destructor is protected or private.

This distinction allows a base class to control access to destruction through its own interface while still ensuring that the correct derived destructor is executed.

## Tuples

Tuples are anonymous aggregate types containing an ordered sequence of elements. Each element has its own type and is accessed by its zero-based index.

A tuple type is written as a comma-separated sequence of element types enclosed in parentheses:

```gaia
(Int32, String, Bool)
```

This represents a tuple containing three elements: an `Int32` at index `.0`, a `String` at index `.1`, and a `Bool` at index `.2`.

Tuple types are structurally typed. Two tuple types are identical if and only if they contain the same number of elements and the corresponding element types are identical in the same order.

The order and number of elements are therefore significant. For example, `(Int32, String)` and `(String, Int32)` are distinct types.

Tuple values can be constructed by explicitly specifying their type:

```gaia
let value = (Int32, String, Bool)(42, "foo", true);
```

The type may also be inferred from the supplied elements:

```gaia
let value = (42, "foo", true);
```

The following syntax is used for tuple literals:

```gaia
let empty = ();          // Empty tuple
let single = (42,);      // Single-element tuple
let pair = (42, "foo");  // Two-element tuple
```

Parentheses without a trailing comma do not create a tuple when they contain a single expression. Thus, `(42)` is equivalent to `42`, whereas `(42,)` is a single-element tuple.

A tuple's mutability is inherited from the variable containing it. All its elements share the same mutability, and individual elements cannot independently be made mutable or immutable.

```gaia
let point = (10, 20);
let mut position = (10, 20);

position.0 = 15; // Valid
point.0 = 15;    // Error: immutable tuple
```

### 1. Tuple Conversions

Implicit conversions between tuple types are performed element by element, following the same conversion rules used for function and method arguments.

A conversion between two tuple types requires both tuples to have the same number of elements. Each source element must be implicitly convertible to the corresponding destination element type.

The order of elements is preserved. If any element cannot be converted, the tuple conversion is invalid.

```gaia
let source: (Int32, Int32) = (10, 20);
let destination: (Int64, Int64) = source;
```

### 2. Tuple Destructuring

Tuples can be destructured when declaring variables. Each declared variable corresponds to an element of the source tuple, in order.

Individual variables may specify their own type and mutability:

```gaia
let x, y = (10, 20);
let x: Int32, mut y: Int64 = (10, 20);
```

The number of declared variables must exactly match the number of source elements, unless a rest element is specified using `...`.

A rest element captures all remaining elements into a new tuple. It may appear at most once in a destructuring declaration. Elements before and after it are matched normally, and all remaining elements are collected into the tuple assigned to the rest variable.

```gaia
let x, ...y = (1, 2, 3);  // x = 1, y = (2, 3)
let ...x, y = (1, 2, 3);  // x = (1, 2), y = 3
let x, ..._ = (1, 2, 3); // Remaining elements are ignored
```

When a rest element is present, the source tuple must contain at least as many elements as there are ordinary variables in the declaration.

The value captured by a rest element is always a tuple, regardless of the number of captured elements. This also applies when the source is a structure rather than a tuple.

### 3. Destructuring Assignment

Tuple destructuring can also be used in assignment expressions. In this case, the assignment targets are enclosed in parentheses and correspond to the source elements in order.

```gaia
let mut x = 0;
let mut y = 0;

(x, y) = (10, 20);
```

Unlike destructuring declarations, destructuring assignments require an exact match between the number of targets and the number of source elements. Rest elements are not supported in destructuring assignments.

### 4. Tuple Expansion in Function Calls

The `...` operator can also be used in an argument list to expand a tuple into individual function arguments.

Each element of the tuple becomes a separate argument, preserving its original order. Multiple expansions may appear in the same argument list.

```gaia
my_func(...tuple, true, 42);
```

This is syntactic sugar equivalent to explicitly passing each tuple element:

```gaia
my_func(tuple.0, tuple.1, tuple.2, true, 42);
```

After expansion, overload resolution and argument type checking follow the usual function and method call rules. Consequently, an expansion is valid only if the resulting argument list is accepted by the selected function or method.

## Structures

Structures (`struct`) are named aggregate types whose elements, called fields, have explicit names and types.

Unlike tuples, structures use nominal typing. Each structure declaration introduces a distinct type identified by its name, even if another structure has exactly the same fields with the same types.

```gaia
struct Point2D {
    x: Float64;
    y: Float64;
}

struct Vector2D {
    x: Float64;
    y: Float64;
}
```

`Point2D` and `Vector2D` are distinct types despite having identical field declarations.

Structure fields are accessed by name:

```gaia
let point = Point2D {
    x: 10.0,
    y: 20.0
};

let x = point.x;
```

The order of field declarations is significant. It determines the order of fields in the structure's memory representation and the order in which fields are processed during destructuring, copying, and moving.

Structure fields do not have individual visibility modifiers. Their mutability is inherited from the structure instance, following the same rules as tuple elements.

Structures do not directly declare methods. However, because they are named types, they can be extended using the `extend` mechanism. Extensions may provide methods without modifying the original structure declaration.

### 1. Structure Construction

Structures are constructed using named field initializers. Positional construction is not supported.

```gaia
struct Person {
    age: Int32;
    name: String;
    active: Bool = true;
}

let person = Person {
    age: 42,
    name: "Alice"
};
```

The order of field initializers does not need to match the declaration order.

A field may be omitted from the construction expression if it has a default initializer or if its type provides a default constructor.

A field without a declaration initializer and without a default constructor must be explicitly initialized during construction.

Every field is therefore initialized before the structure instance becomes available for use.

### 2. Structure Conversions and Destructuring

Structures use nominal typing and do not support implicit conversions to or from other structure types, even when their fields have identical names and types.

Implicit conversions between structures and tuples are also not supported, regardless of whether their elements correspond exactly.

When a value of another structure type or a tuple must be used to construct a structure, the conversion must be expressed explicitly by constructing a new instance and providing its fields individually.

```gaia
struct A {
    x: Int32;
    y: String;
}

struct B {
    x: Int64;
    y: String;
}

let b = B {
    x: 42,
    y: "foo"
};

let a = A {
    x: b.x,
    y: b.y
};
```

The usual implicit conversion rules still apply to each field initializer independently.

Structures can be destructured using the same syntax as tuples. Fields are extracted in declaration order, regardless of their names.

```gaia
struct Person {
    age: Int32;
    name: String;
}

let person = Person {
    age: 42,
    name: "Alice"
};

let age, name = person;
```

The `...` rest element can be used in structure destructuring as well. The captured remaining fields are always represented as a tuple, not as another structure.

## Member Pointers

Member pointers provide a way to refer to non-static members of a `class` or `struct` independently of a specific object instance.

They can refer to data members or member functions. Member pointers retain the type of the referenced member and the type of objects on which they can be applied.

### 1. Member Pointer Types

Member pointer types identify both the owning type and the type of the referenced member.

The following forms are supported:

- `T::*U`: nullable pointer to a member of type `U` applicable to objects of type `T`.
- `T::&U`: non-nullable pointer to a member of type `U` applicable to objects of type `T`.

The member type `U` is mandatory. A member pointer type cannot be specified without identifying the type of the referenced member.

For data members, `U` is the declared type of the member.

For member functions, `U` is the corresponding function type, including its parameters, return type, and the qualifications imposed by its explicit `self` parameter.

Member pointers follow the same nullability and conversion rules as ordinary references. In particular, a non-nullable member pointer can be implicitly converted to its nullable counterpart. Converting a nullable member pointer to a non-nullable one requires the usual nullability check.

The owning type does not need to be the type in which the member was originally declared. A member pointer may refer to an inherited member as long as that member is applicable to the owning type and can be identified unambiguously.

### 2. Obtaining Member Pointers

The address-of-member syntax `&Type::member` obtains a member pointer.

The resulting type identifies the specified `Type` as its owning type and retains the type of the referenced member.

Obtaining a member pointer is subject to the usual access control rules. A member pointer to a private or protected member can only be obtained from a context in which that member is accessible.

Once obtained, a member pointer can be stored, returned, or passed to another context. Using it does not require the member to be accessible from the context in which the pointer is used.

Static members are not eligible for member pointers. Taking the address of a static member produces an ordinary pointer to the corresponding variable or function, without retaining any information about its declaring type.

Constructors (`init`) and destructors (`deinit`) cannot be addressed through member pointers.

### 3. Applying Member Pointers

The `.*` and `->*` operators apply a member pointer to an object or an object pointer, respectively.

- `object .* member` applies the member pointer to an object.
- `pointer ->* member` applies the member pointer through an object pointer or reference.

The usual automatic dereferencing rules apply to the object operand.

For convenience, the ordinary member access syntax may also be used with a member pointer when its interpretation is unambiguous. For example, `object.member` may be used where `object .* member` would otherwise be required.

For member functions, applying a member pointer produces a callable member reference that can be invoked using the usual function call syntax.

Applying a member pointer is subject to its nullability and compatibility requirements. Applying a nullable member pointer requires the usual nullability handling.

### 4. Inheritance and Virtual Dispatch

Member pointers support conversions associated with class inheritance, following the language's inheritance compatibility rules.

A member pointer may refer to a member declared in a base class when that member is applicable to the owning type. This includes inherited members, provided that the member can be identified unambiguously.

Conversions between member pointer types are permitted when the source and destination owning types are compatible through inheritance. Such conversions must preserve the identity and applicability of the referenced member, including any required pointer adjustment for multiple inheritance.

Applying a pointer to a virtual member function preserves normal virtual dispatch. The implementation invoked is determined by the dynamic type of the object, according to the usual virtual dispatch rules.

### 5. Mutability

Member pointers do not introduce independent mutability qualifications.

For data members, access and modification are governed by the mutability of the object to which the member pointer is applied.

For member functions, mutability requirements are determined by the explicit `self` parameter, which is part of the member function's signature. These requirements are therefore preserved by the member pointer type.

## Enumerations

Gaïa provides two forms of enumerations: simple enumerations (`enum`) and variant enumerations (`enum struct`).

Both forms define a finite set of named alternatives. The `implicit` modifier can be used with either form to introduce their variant names directly into the enclosing scope, without requiring qualification by the enumeration name.

If two declarations introduce the same name into a scope where they conflict, the compiler reports a duplicate declaration error. No implicit priority or precedence is applied.

### 1. Simple Enumerations

A simple enumeration defines a set of named constants:

```gaia
enum Color {
    Red,
    Green,
    Blue
}
```

Each enumerator is accessible through its enumeration type:

```gaia
let color = Color::Red;
```

The `implicit` modifier makes the enumerators directly accessible without qualifying them with the enumeration name:

```gaia
implicit enum State {
    Enabled,
    Disabled
}

let state = Enabled;
```

#### 1.1 Enumerator Values

Each enumerator may be assigned an explicit integer constant value. If no value is specified, the enumerator receives the value immediately following the value of the preceding enumerator. The first enumerator defaults to zero.

Explicit values may refer to previously declared constants or other constant expressions.

```gaia
const ValueForB: Int64 = 42;

enum Values {
    A = 5,
    B = ValueForB,
    C,
    D = 10,
    E
}
```

In this example, `A` has the value `5`, `B` has the value `42`, `C` has the value `43`, `D` has the value `10`, and `E` has the value `11`.

Enumerator values are not required to be unique. Multiple enumerators may therefore represent the same underlying value.

#### 1.2 Underlying Type

An enumeration has an integer underlying type.

When no underlying type is explicitly specified, the compiler selects the smallest integer type capable of representing all enumerator values.

The selected type is unsigned if all values are non-negative, and signed if at least one value is negative.

An explicit underlying type can be specified after the enumeration name:

```gaia
enum Flags : Int64 {
    Read = 1,
    Write = 2,
    Execute = 4
}
```

When an underlying type is explicitly specified, all enumerator values must be representable by that type. Otherwise, the declaration is ill-formed.

### 2. Variant Enumerations

Variant enumerations (`enum struct`) define a closed set of named alternatives, each of which may optionally carry associated data.

Unlike simple enumerations, variant enumerations do not represent integer constants. Each value belongs to exactly one of the alternatives declared by its enumeration.

A variant may take one of three forms:

- A variant without associated data.
- A variant carrying a tuple of values.
- A variant carrying an anonymous structure of named fields.

```gaia
enum struct Message {
    Quit,
    Write(String),
    Move {
        x: Float64;
        y: Float64;
    }
}
```

In this example, `Quit` carries no data, `Write` carries a single-element tuple, and `Move` carries an aggregate with two named fields.

Variants are constructed by specifying their enumeration and variant names:

```gaia
let quit = Message::Quit;
let write = Message::Write("Hello");
let move = Message::Move {
    x: 10.0,
    y: 20.0
};
```

The `implicit` modifier makes variant constructors directly accessible without qualifying them with the enumeration name:

```gaia
implicit enum struct Result {
    Ok(Int32),
    Error(String)
}

let result = Ok(42);
```

Variant enumerations are closed types. All their variants must be declared in the original enumeration declaration. Extensions cannot introduce additional variants.

Because the set of variants is known at compile time, the compiler can determine whether a pattern matching expression covers every possible alternative.

### 3. Extensions

Variant enumerations are named types and can therefore be extended using the `extend` mechanism.

Extensions may provide additional methods without modifying the original enumeration declaration. However, they cannot change its set of variants or the data associated with existing variants.

```gaia
enum struct Result {
    Ok(Int32),
    Error(String)
}

extend Result {
    pub fn is_ok(self) -> Bool {
        ...
    }
}
```

As with structures, variants themselves are simple aggregates and do not directly declare methods or individual field visibility modifiers.

## Pattern Matching

Gaïa provides the `match` control-flow construct to select and execute a branch according to the value of an expression.

Unlike an expression, `match` does not produce a value. Each branch is an independent statement block and does not need to produce a result of a common type.

```gaia
match value {
    First => {
        handle_first();
    },
    Second => {
        handle_second();
    },
    _ => {
        handle_other();
    }
}
```

A `match` construct can be used with enumeration types, as well as other types whose values can be compared numerically.

### 1. Value Patterns

For types supporting numerical comparison, patterns may specify individual constant values or ranges.

The following types are supported:

- Integer types.
- Floating-point types.
- Boolean values.
- Character values.

String values are not supported as patterns in the current version of the language. Their support may be considered in a future version.

A pattern may contain multiple alternatives separated by `|`. All alternatives in the same branch share the same statement block.

```gaia
match value {
    First | Second => {
        handle_common_case();
    },
    0..255 => {
        handle_byte_range();
    },
    _ => {
        handle_other();
    }
}
```

Range syntax follows the same rules as those defined for `switch`:

- `..` defines a range inclusive of both endpoints.
- `...` defines a range inclusive of its lower endpoint and exclusive of its upper endpoint.

Range endpoints must be constant expressions compatible with the type being matched.

Alternative patterns and range patterns are intended for matching simple values and cannot be combined with variant destructuring when doing so would introduce ambiguity. The compiler reports ambiguous patterns rather than attempting to infer their intended interpretation.

### 2. Variant Patterns

Variant enumerations can be matched by specifying their individual variants.

A variant without associated data is matched directly. Variants carrying positional or named data can be destructured as part of the pattern.

```gaia
match message {
    Message::Quit => {
        handle_quit();
    },
    Message::Write(text) => {
        handle_write(text);
    },
    Message::Move { x, y } => {
        handle_move(x, y);
    }
}
```

Variant names follow the same qualification rules as their declarations. Enumerators introduced through an `implicit enum struct` may be used without qualifying them with their enumeration name.

### 3. Destructuring Patterns

Destructuring patterns follow the same rules as ordinary tuple and structure destructuring.

For positional data, elements are matched in their declared order:

```gaia
match value {
    Data::Values(first, _, last) => {
        process(first, last);
    }
}
```

For named fields, fields are also matched in declaration order. A field may be explicitly associated with a differently named local variable using the `field: local` syntax.

```gaia
match message {
    Message::Move {
        x: local_x,
        y: local_y,
        ...
    } => {
        process(local_x, local_y);
    }
}
```

When no explicit local name is provided, the field name is used as the local variable name.

The following rules apply to both positional and named destructuring:

- `_` ignores the corresponding element or field.
- `...name` captures all remaining elements or fields into a tuple named `name`.
- `..._` ignores all remaining elements or fields.
- At most one `...` element is permitted in a pattern.
- Without `...`, the pattern must account for every element or field.
- The captured remainder is always a tuple, including when it contains zero or one element.

The order of elements and fields in a destructuring pattern must respect their declaration order.

### 4. References and Mutability

Unlike ordinary destructuring declarations, which create copies of the extracted values, destructuring in a `match` creates references to the corresponding elements or fields of the matched value.

Consequently, no copy of the destructured data is performed. Access through the resulting local variables operates directly on the original value.

The mutability of these references can be specified individually in the pattern. Mutable references are only permitted when the matched expression provides mutable access to the corresponding value.

```gaia
match message {
    Message::Move { x: mut local_x, y: local_y, ..._ } => {
        local_x = 42.0;
        // Modifies the original x field.
    }
}
```

All ordinary reference conversion, mutability, borrowing, and lifetime rules apply to references introduced by destructuring patterns.

### 5. Exhaustiveness

A `match` construct must account for every possible value of the matched expression.

For variant enumerations, this means covering every declared variant. For other supported types, the compiler verifies that the patterns cover the possible values according to their type and the specified ranges.

A default pattern (`_`) may be used to cover all values not matched by preceding branches:

```gaia
match result {
    Result::Ok(value) => {
        process(value);
    },
    _ => {
        handle_error();
    }
}
```

The default pattern is optional when all possible values are already covered.

### 6. Redundant and Unreachable Patterns

The compiler diagnoses redundant or unreachable branches with a warning.

This includes, for example:

- A branch matching values already covered by preceding branches.
- A branch appearing after a default pattern (`_`).
- A branch whose entire set of possible values is already covered by previous patterns.

These diagnostics can be promoted to errors through the standard diagnostic configuration mechanism.

## Annotations

### 1. General Principles

Gaïa provides a general-purpose annotation mechanism.

Annotations allow metadata and additional directives to be associated with language elements.

Annotations are introduced using the `@` prefix followed by an annotation identifier and an optional parameter list.

The general syntax is:

```gaia
@annotation_name(parameters)
```

### 2. Annotation Association

Annotations may be associated with supported language elements, including:

- Modules
- Types
- Variables
- Functions
- Methods
- Expressions
- Other syntactic elements

The exact set of supported targets depends on the annotation's definition.

### 3. Multiple Annotations

Multiple annotations may be associated with the same language element.

Each annotation is independently declared using the standard annotation syntax.

Example:

```gaia
@inline
@deprecated("Use new_function instead")
fn old_function() {
}
```

### 4. Annotation Parameters

Annotations may accept parameters.

Annotation parameters follow the standard expression syntax of Gaïa. Annotation-specific parameter formats may additionally define accepted unquoted values.

For example, hyphens are permitted in unquoted annotation arguments. Quoted arguments may be used when values contain spaces or other special characters.

The number, types and semantics of accepted parameters depend on the corresponding annotation definition.

Example:

```gaia
@deprecated("Use new_function instead")
fn old_function() {
}
```

### 5. Annotation Semantics

Annotations do not have a universal behavior.

Their semantics are defined individually.

An annotation may influence:

- Compiler diagnostics
- Semantic analysis
- Code generation
- Optimization
- Other compiler behaviors

### 6. Annotation Placement and Scope

Annotations are associated with the language element or expression to which they are syntactically attached.

For annotations placed inline within an expression, the annotation applies to the syntactic element directly created by the following token.

Parentheses may be used to explicitly associate an annotation with an entire expression.

An annotation applies to a single syntactic element. However, its semantics may also affect elements contained within that element's syntax tree.

The exact attachment rules and supported placement locations depend on the annotation's definition.

### 7. Extensibility

The annotation system is designed to support future extensions.

Future versions of Gaïa may allow user-defined annotations and annotation processing through the language's metaprogramming facilities.

## Compiler Diagnostics

### 1. Diagnostic Categories

Gaïa compiler diagnostics are classified into four categories:

| Category | Description |
|---|---|
| `error` | A problem preventing correct compilation. |
| `warning` | A potential problem or suspicious practice that does not prevent compilation by default. |
| `note` | Additional information associated with another diagnostic. |
| `remark` | Informational output that does not necessarily indicate a problem. |

Errors prevent successful compilation.

Warnings do not prevent compilation by default, but may be promoted to errors through diagnostic configuration.

Notes and remarks do not affect compilation success and cannot be promoted to errors.

A note generally provides additional context for another diagnostic, such as identifying the declaration involved in an error.

A remark may be emitted independently, for example to report an optimization performed by the compiler.

### 2. Diagnostic Identifiers

Every compiler diagnostic has a unique identifier.

Diagnostic identifiers are independent of diagnostic message text and remain stable across changes to the wording of diagnostic messages.

Identifiers use lowercase, hyphen-separated words and follow a hierarchical naming convention.

The first components identify the diagnostic domain, while subsequent components identify the specific diagnostic.

Examples:

- `numeric-floating-point-precision-loss`
- `numeric-integer-overflow`
- `memory-invalid-alignment`
- `memory-use-after-move`

Diagnostic identifiers are used to configure and selectively control diagnostics.

### 3. Warning Configuration

Warnings are enabled by default and have the `warning` level.

Each warning can be assigned one of the following levels:

- `error`: Promotes the warning to an error and prevents successful compilation.
- `warning`: Emits the diagnostic as a warning.
- `ignore`: Suppresses the diagnostic entirely.

Only warnings can be configured this way. Errors cannot be disabled or downgraded, and notes and remarks cannot be promoted.

Warning levels may be configured at the project or module level.

The project-level configuration provides the initial configuration. A module-level configuration inherits this configuration and may selectively override it.

Configuration rules use diagnostic identifiers as selectors. Selectors may take one of three forms:

- An exact diagnostic identifier.
- A hierarchical prefix followed by `-*`, selecting all diagnostics belonging to that prefix.
- `*`, selecting all warnings.

Wildcards are only permitted at the end of a selector.

Examples:

```text
numeric-* = error
numeric-floating-point-precision-loss = warning
memory-* = ignore
```

Configuration rules are evaluated in their order of declaration. When multiple rules match the same warning, the last matching rule determines its effective level.

More specific configuration levels override inherited rules. Unselected warnings retain their previously established levels.

### 4. Warning Annotations

Warning levels may also be configured locally through annotations.

The `@warnings` annotation assigns a level to the selected warnings within the scope of a declaration.

Its syntax is:

```gaia
@warnings(level, selectors...)
```

The `level` parameter must be one of `error`, `warning` or `ignore`.

Multiple selectors may be specified in a single annotation.

Multiple `@warnings` annotations may be applied to the same declaration. Each occurrence selectively overrides the levels established by previous occurrences.

For example:

```gaia
@warnings(error, *)
@warnings(warning, numeric-floating-point-precision-loss)
@warnings(ignore, style-*)
class StrictCode {
}
```

In this example, all warnings are promoted to errors, except for floating-point precision loss warnings, which remain warnings, and warnings belonging to the `style` domain, which are suppressed.

The `@warnings` annotation is reserved for declarations, including modules, types, functions and methods.

### 5. Local Warning Suppression

The `@ignore` annotation provides a shorthand for locally suppressing selected warnings.

Its syntax is:

```gaia
@ignore(selectors...)
```

It is semantically equivalent to:

```gaia
@warnings(ignore, selectors...)
```

Unlike `@warnings`, `@ignore` may be applied to any syntactic element that supports annotations, including expressions and instructions.

For example:

```gaia
@ignore(numeric-floating-point-precision-loss)
fn calculate() {
    let value = 0.1f32 + 0.2f32;
}
```

An annotation may also be placed inline within an expression:

```gaia
let value = @ignore(numeric-floating-point-precision-loss) (0.1f32 + 0.2f32);
```

In this case, the parentheses associate the annotation with the entire expression.

An annotation affects the annotated syntactic element and its descendants in the syntax tree. Consequently, diagnostics emitted while processing any of these elements are subject to the annotation.

Local suppression always takes effect, even if the corresponding warning has been promoted to an error by a project or module configuration.

### 6. Configuration Inheritance and Scope

Warning configuration follows a selective inheritance model.

The effective configuration is established through the following levels:

1. Project-level configuration.
2. Module-level configuration.
3. Annotations applied to declarations.
4. Annotations applied to individual syntactic elements.

Configuration levels are applied in order, from the most global to the most local. At each level, rules are evaluated in their order of declaration. The last matching rule determines the effective level for a given warning at that level.

Rules at a more local level override inherited settings only for the warnings they select. All other warning levels remain unchanged.

Each source fragment maintains its own annotation context. Annotations applied within one fragment do not affect other fragments, even when they belong to the same module.

Annotations applied to nested declarations override inherited settings only for the warnings they select.

The last applicable annotation takes precedence over previous annotations for the warnings it selects.

### 7. Diagnostic Context

Warning configuration is evaluated through the compiler's diagnostic context.

When the compiler enters a syntax tree node containing a `@warnings` or `@ignore` annotation, the annotation introduces a new configuration override for that node and its descendants.

When the compiler leaves that node, the override ceases to apply and the previous configuration is restored.

The effective warning level is determined by the active diagnostic context at the moment the diagnostic is emitted.

The compiler should preferably emit diagnostics during a single compilation phase. However, some diagnostics may require information only available during a later phase.

If diagnostics are emitted across multiple phases, the compiler must preserve the effective diagnostic configuration so that annotations have the same effect regardless of the phase in which a diagnostic is emitted.

The implementation strategy used to preserve and restore diagnostic contexts is left to the compiler.

### 8. Unknown Diagnostic Identifiers

The compiler must report unknown diagnostic identifiers used in warning configuration or annotations.

This allows misspelled identifiers and obsolete diagnostic references to be detected.

A hierarchical or global wildcard selector remains valid even if it does not currently match any known warning.

## Templates

### 1. General Principles

Gaïa supports compile-time templates.

Templates are instantiated at compile time and support specialization, type parameters and value parameters.

Templates follow a generic-style syntax similar to that used by modern programming languages.

Gaïa follows a *Substitution Failure IS an Error* principle.

An invalid template substitution produces an explicit compilation error unless the declaration is constrained using `requires`.

When a declaration is constrained, its constraints are evaluated before the declaration is generated. If the constraints are not satisfied, the declaration is not generated for the corresponding template arguments.

Consequently, attempting to use a declaration that was not generated because its constraints were not satisfied results in an error indicating that the requested declaration does not exist.

This behavior applies uniformly to classes, structures, functions, methods and type aliases.

### 2. Template Parameters

Template parameters are declared using angle brackets.

By default, a template parameter represents a type. An unconstrained type parameter is equivalent to one explicitly constrained using the `type` concept.

The following declarations are equivalent:

```gaia
class Foo<T> {
}

class Foo<T: type> {
}
```

Non-type template parameters can be declared by specifying their type.

Example:

```gaia
class Array<T, N: Size> {
}
```

Template parameters may be declared at different levels, including classes and their member functions.

Example:

```gaia
class Foo<T> {
    pub fn bar<U>(self) {
    }
}
```

### 3. Concepts and Constraints

Concepts define compile-time requirements on types and expressions.

They are parameterized declarations that evaluate whether their arguments satisfy the specified requirements.

Concepts may be composed using logical operators and may contain expression requirements.

#### 3.1 Constrained Template Parameters

Template parameters may be constrained directly using the `:` syntax.

Example:

```gaia
class Foo<T: Fooable> {
}
```

This syntax is equivalent to:

```gaia
class Foo<T> requires Fooable<T> {
}
```

The `type` concept represents the set of all types and is implicitly assumed when a template parameter has no explicit constraint.

#### 3.2 Requires Clauses

The `requires` keyword introduces constraints on generic declarations.

Constraints may be applied to classes, structures, functions, methods and type aliases.

A declaration is generated only when all its associated constraints are satisfied.

When a constraint is not satisfied, the corresponding declaration is not generated for the requested template arguments.

This mechanism also allows multiple declarations with the same name to coexist when their constraints differ.

Example:

```gaia
class List<T> {
    pub fn sort(self) requires Sortable<T> {
        // ...
    }

    pub fn sort(self) requires !Sortable<T> {
        // ...
    }
}
```

Only the applicable declaration is generated for a given instantiation.

#### 3.3 Generic Operation Validation

The compiler analyzes operations performed on generic types.

An operation is considered validated when its validity is guaranteed by the applicable concept constraints.

When an operation cannot be validated through these constraints, the compiler generates a warning.

This warning indicates that the generic implementation relies on a capability that is not formally guaranteed by its constraints.

Such warnings may be promoted to compilation errors through the standard diagnostic configuration mechanism.

This mechanism allows generic implementations to use operations without explicitly constraining every required capability, while notifying the developer that the corresponding requirements are not formally established.

#### 3.4 Higher-Level Generic Constraints

Requires clauses may validate generic parameters declared at a higher level.

This allows individual methods to introduce additional requirements without constraining the entire enclosing type.

Example:

```gaia
class List<T> {
    pub fn sort(self) requires Sortable<T> {
        // ...
    }
}
```

In this example, `List<T>` does not require `T` to implement `Sortable`.

Only the `sort` method requires that constraint.

Consequently, other operations on `List<T>` remain available regardless of whether `T` satisfies `Sortable`.

#### 3.5 Generic Type Aliases

Type aliases may also be generic and constrained.

Example:

```gaia
type Foo<T> = Bar<Baz<T>>
    requires Barable<T> && Bazable<T>;
```

The alias is generated only when all its constraints are satisfied.

A type alias does not introduce a new type identity. It refers to the type specified by its aliased expression.

### 4. Specialization

Templates support explicit specialization through the `specialize` keyword.

Class specialization:

```gaia
specialize class Foo<Bool> {
}
```

Function specialization:

```gaia
specialize fn Bar::bar<Bool>(self) {
}
```

An explicit specialization is always associated with a specific generic declaration.

It replaces the instantiation of that declaration corresponding to the explicitly specified template arguments.

An explicit specialization does not introduce an independent overload candidate and does not participate separately in overload resolution.

### 5. Template Instantiation

Template instantiation occurs at compile time.

Invalid substitutions produce explicit compilation errors.

The compiler must not silently discard invalid template declarations as an overload resolution fallback mechanism.

### 6. Variadic Templates

Gaïa supports variadic templates following the principles of C++ variadic templates.

A variadic template parameter is declared using the `...` suffix.

Variadic parameters may be used in class and function templates.

Parameter packs may be expanded using the `...` operator.

The compiler performs pack expansion during template instantiation.

Variadic templates support the same general expansion principles as C++.

### 7. Fold Expressions

Gaïa supports fold expressions following the principles introduced in C++17.

Fold expressions allow a parameter pack to be reduced using a binary operator.

The four C++17 fold expression forms are supported:

- Unary left fold.
- Unary right fold.
- Binary left fold.
- Binary right fold.

Fold expressions are evaluated during template instantiation and follow the operator semantics of their expanded expressions.

### 8. Non-Type Template Parameters

Template parameters may represent values rather than types. A non-type template parameter must explicitly specify its type.

```gaia
class Array<T, N: Size> {
    // ...
}
```

A non-type template argument must be a constant value. It may be provided either as a constant expression or as a named constant declared with `const`. Named constants may be declared in any module, provided they are accessible from the context in which the template is instantiated.

Non-type template parameters are not restricted to a predefined list of primitive types. Any type is admissible, provided that a constant value of that type can be supplied and compared at compile time. This includes primitive types, enumerations, tuples, structures, and user-defined types satisfying these requirements.

The compiler uses compile-time comparison of non-type template arguments to distinguish template specializations and instantiations. Consequently, the relevant type must support comparison of its constant values during compilation.

```gaia
const DefaultCapacity: Size = 128;

class Buffer<T, Capacity: Size> {
    // ...
}

type DefaultBuffer<T> = Buffer<T, DefaultCapacity>;
type SmallBuffer<T> = Buffer<T, 16>;
```

Non-type template arguments follow the same compile-time evaluation rules as other constant expressions.

## Template Argument Deduction

### 1. General Principles

Template argument deduction preserves the exact type of the provided argument unless the template parameter declaration specifies otherwise.

No implicit removal of references, pointers or mutability qualifiers is performed during deduction.

### 2. Direct Type Deduction

For a parameter declared as `T`, the deduced type corresponds exactly to the argument type.

Example:

```gaia
fn foo<T>(value: T) {
}
```

The parameter `T` may represent any type, including references, pointers and arrays.

### 3. Structured Type Deduction

Template parameters may be deduced from a specific type structure.

Example:

```gaia
fn foo<T>(value: &T) {
}
```

In this case, the argument must match a non-nullable reference and `T` represents the referenced type.

### 4. Type Transformations

Type transformations may be used in template parameter declarations.

Example:

```gaia
fn foo<T>(value: RemovePtr<T>) {
}
```

The transformation determines the expected parameter type while `T` represents the original deduced type.

### 5. Constrained Deduction

Template parameters may be constrained using concepts, including negated concepts.

Example:

```gaia
fn foo<T: !IsPtr>(value: T) {
}
```

The compiler only accepts template arguments satisfying the specified constraints.

### 6. Explicit Arguments and Default Parameters

Template arguments may be explicitly specified partially or entirely.

Parameters that are not explicitly specified are deduced whenever possible.

Parameters that cannot be deduced may use their default value, if one is defined.

The resolution follows this order:

1. Explicitly specified arguments are assigned first.
2. Remaining arguments are deduced from function parameters.
3. Unresolved parameters use their default values.
4. Any remaining unresolved parameter produces a compilation error.

Explicitly specified parameters do not participate in template argument deduction.

Implicit conversions are applied only after template argument resolution.

Template parameters with default values must be declared after all parameters without default values.

Example:

```gaia
fn make_boxed<T, Args...>(args: Args...) -> Box<T> {
    return Box<T>(...args);
}

class Vector<T, Allocator = DefaultAllocator<T>> {
}
```

## Overload Resolution

### 1. General Principles

Gaïa supports function overloading between regular functions and function templates.

Overload resolution selects the most appropriate candidate according to the function signatures, template arguments and applicable constraints.

If multiple candidates remain indistinguishable after applying the overload resolution rules, compilation fails with an ambiguity error.

### 2. Non-Template Function Preference

When a non-template function and a function template provide equally good matches for a given call, the non-template function is preferred.

This preference only applies when both candidates are otherwise equivalent in overload resolution.

A function template may still be selected when it provides a better match.

Example:

```gaia
fn process(value: Int32) {
    print("Int32");
}

fn process<T>(value: T) {
    print("Generic");
}

process(42);    // Calls the non-template overload
process(3.14);  // Calls the template overload
```

### 3. Constraint-Based Overload Resolution

When multiple function templates are otherwise equivalent candidates, the compiler considers their associated constraints.

A candidate whose constraints are strictly more specific than those of another candidate is preferred.

Constraint ordering follows a subsumption-based model inspired by C++20.

Example:

```gaia
fn process<T>(value: T) {
    print("Generic");
}

fn process<T>(value: T) requires Integral<T> {
    print("Integral");
}

process(42);    // Calls the Integral overload
process(3.14);  // Calls the Generic overload
```

When the constraints of multiple candidates cannot be ordered, the overload resolution may result in an ambiguity.

Constraint-based overload resolution applies to distinct generic declarations that participate in the same overload set.

Explicit specializations are not independent overload candidates. They remain associated with their respective generic declarations and replace the corresponding instantiations.

### 4. Ambiguous Overloads

If multiple candidates are equally suitable and cannot be distinguished by the overload resolution rules, the compiler reports an ambiguity error.

The compiler must not arbitrarily select one of the candidates.

### 5. Conversion Sequence Ranking

#### 5.1 General Principles

Implicit conversion sequences are ranked according to the number of conversion steps required to transform the source type into the destination type.

The compiler must prefer conversion sequences requiring fewer steps over those requiring more steps.

#### 5.2 Conversion Step Counting
Every individual conversion constitutes one conversion step.

This applies equally to standard conversions and user-defined conversions.

The nature of a conversion does not independently influence its ranking.

The following operations each constitute one conversion step:

- Standard type conversions.
- User-defined implicit conversions.
- Implicit address-of operations.
- Automatic pointer dereferencing.

A sequence containing multiple operations requires one step for each operation.

For example, a sequence containing one user-defined conversion and one standard conversion requires two steps, just like a sequence containing two user-defined conversions.

#### 5.3 Numeric Conversion Sequences

Numeric conversions participate in conversion sequence ranking in the same manner as other implicit conversions.

The compiler must not assign any additional priority to numeric conversions based on their category.

A direct numeric conversion constitutes one conversion step, while a sequence of multiple numeric conversions constitutes one step per individual conversion.

Only numeric conversions explicitly permitted by the Numeric Conversions section participate in implicit conversion sequences.

#### 5.4 Exact Matches

An exact match is always preferred over any conversion sequence.

When the source type exactly matches the destination type, no conversion is performed.

#### 5.5 Ambiguous Conversion Sequences

When multiple conversion sequences require the same number of steps, the conversion is considered ambiguous.

The compiler must report an ambiguity error rather than arbitrarily selecting one of the available sequences.

#### 5.6 Conversion Sequence Examples

Consider the following conversion paths:

```gaia
A -> D
A -> B -> D
A -> C -> D
```

The compiler selects `A -> D` because it requires fewer conversion steps.

However, the following conversion paths produce an ambiguity:

```gaia
A -> B -> D
A -> C -> D
```

Both sequences require two conversion steps. Consequently, neither can be preferred.

### 6. Conversion Path Resolution

#### 6.1 General Principles

Implicit conversion resolution is performed by searching for valid conversion paths between the source type and the destination type.

The compiler must identify the shortest valid conversion path.

No arbitrary limit is imposed on the number of conversion steps within a conversion path.

#### 6.2 Shortest Path Preference

When multiple conversion paths exist between a source type and a destination type, the compiler must prefer paths requiring fewer conversion steps.

Longer conversion paths must not influence the resolution when a shorter valid path exists.

#### 6.3 Ambiguous Conversion Paths

When multiple distinct conversion paths require the same minimum number of conversion steps to reach the destination type, the conversion is considered ambiguous.

The compiler must report an ambiguity error.

An ambiguity encountered in a conversion path invalidates that conversion sequence when it affects the resolution of the requested destination type.

Ambiguities involving unrelated conversion paths or intermediate types must not independently invalidate the requested conversion.

#### 6.4 Cycle Detection

The compiler must detect cycles during conversion path exploration.

A type must not appear more than once within the same conversion path.

When a cycle is detected, the compiler must abandon the corresponding path without affecting other conversion paths.

#### 6.5 Deterministic Resolution

Conversion path resolution must produce deterministic results.

The order in which conversion paths are explored must not influence the selected conversion path or the detection of ambiguities.

### 7. Multiple Argument Conversion Ranking

#### 7.1 General Principles

When resolving overloads with multiple arguments, the compiler compares the conversion sequences of each argument independently.

A candidate must not be preferred based on the total number of conversion steps across all arguments.

#### 7.2 Candidate Comparison

A candidate is considered better than another candidate when:

- Its conversion sequence is no worse for every argument.
- Its conversion sequence is strictly better for at least one argument.

Conversion sequences are compared according to the conversion ranking rules defined in this specification.

#### 7.3 Incomparable Candidates

When multiple candidates are equally suitable or when each candidate provides a better conversion for at least one different argument, neither candidate is preferred.

If no other overload resolution rule can distinguish them, compilation fails with an ambiguity error.

Example:

```gaia
fn process(a: Int32, b: Float64) {
    print("A");
}

fn process(a: Float64, b: Int32) {
    print("B");
}

let a: Int32 = 10;
let b: Int32 = 20;

process(a, b); // Compilation error: ambiguous overload
```

### 8. Default Arguments and Overload Conflicts

#### 8.1 General Principles

Default arguments do not define independent overloads.

A function with default arguments is considered callable through every valid argument count supported by its default parameters.

#### 8.2 Conflicting Declarations

Two function declarations are considered conflicting when their callable signatures overlap as a result of default arguments.

Such declarations produce a compilation error.

Example:

```gaia
fn process(value: Int32) {
}

fn process(value: Int32, count: Int32 = 0) {
    // Compilation error: conflicting callable signature
}
```

The compiler must detect these conflicts during declaration analysis rather than deferring them to overload resolution.

### 9. Instance Method Overload Resolution

#### 9.1 General Principles

Instance methods may be overloaded according to their `self` parameter.

The applicable receiver form is determined by the access capabilities of the calling expression and whether ownership transfer is explicitly requested.

#### 9.2 Mutable Receiver Preference

When the calling expression provides mutable access to an instance, a method accepting `mut self` is preferred over an otherwise equivalent method accepting `self`.

The immutable receiver form is considered only when no applicable mutable receiver overload is available.

Example:

```gaia
class Example {
    pub fn process(self) {
        print("Immutable");
    }

    pub fn process(mut self) {
        print("Mutable");
    }
}

let mut object = Example();

object.process(); // Calls mut self
```

#### 9.3 Immutable Receiver

The `self` parameter represents immutable access to the instance.

It is selected when mutable access is unavailable or when no applicable `mut self` overload exists.

#### 9.4 Ownership Transfer

The `move self` parameter represents ownership transfer of the instance.

An overload accepting `move self` is only considered when the calling expression explicitly requests ownership transfer using the `move` keyword.

Ownership transfer must never occur implicitly as a consequence of overload resolution.

Example:

```gaia
class Example {
    pub fn process(self) {
        print("Immutable");
    }

    pub fn process(move self) {
        print("Move");
    }
}

let object = Example();

object.process();      // Calls self
move object.process(); // Calls move self
```

#### 9.5 Receiver Form Distinction

The following receiver forms represent distinct parameter types and access modes:

- `self`: `&Self`
- `mut self`: `&mut Self`
- `move self`: `Self`, with explicit ownership transfer

Their applicability is determined before comparing the remaining function parameters.

An overload requiring an access mode unavailable to the calling expression is not a viable candidate.

### 10. Template Argument Deduction and Conversions

#### 10.1 General Principles

Template argument deduction is performed using the actual types of the provided arguments.

Implicit conversions must not be applied during template argument deduction.

The compiler must first determine the template arguments before performing implicit conversions required by the resulting parameter types.

#### 10.2 Type Transformations

Type transformations applied to template parameters do not modify the deduced template argument.

They only determine the resulting parameter type.

Example:

```gaia
fn process<T>(value: RemovePtr<T>) {
}

let value: &Int32 = ...;

process(value);
```

In this example:

- `T` is deduced as `&Int32`.
- `RemovePtr<T>` evaluates to `Int32`.
- The resulting parameter type is `Int32`.
- The argument is automatically dereferenced when passed to the function.

#### 10.3 Implicit Pointer Operations

Implicit address-of operations and automatic pointer dereferencing may be performed after template argument deduction.

These operations follow the standard conversion ranking rules defined in this specification.

### 11. Explicit Specialization

#### 11.1 General Principles

Gaïa supports explicit template specialization through the `specialize` keyword.

An explicit specialization replaces the corresponding generic instantiation rather than introducing an independent overload candidate.

Example:

```gaia
fn process<T>(value: T) {
    print("Generic");
}

specialize fn process<Bool>(value: Bool) {
    print("Boolean");
}

process(42);    // Generic
process(true);  // Boolean
```

#### 11.2 Specialization and Constraints

An explicit specialization must satisfy all constraints associated with the generic declaration it specializes.

A specialization that does not satisfy these constraints produces a compilation error.

Example:

```gaia
fn process<T>(value: T) requires Integral<T> {
    print("Integral");
}

specialize fn process<Int32>(value: Int32) {
    print("Int32");
}
```

The specialization is valid because `Int32` satisfies `Integral<Int32>`.

The following specialization is invalid if `String` does not satisfy `Integral<String>`:

```gaia
specialize fn process<String>(value: String) {
    print("String");
}
```

#### 11.3 Specialization Selection

An explicit specialization is selected whenever its associated generic declaration is selected and the explicitly specified template arguments match the requested instantiation.

The specialization replaces the corresponding instantiation of that declaration.

It does not take precedence over specializations or overloads belonging to unrelated generic declarations. The selection of the generic declaration itself is determined by the ordinary overload resolution rules.

#### 11.4 Ambiguous Specializations

If multiple explicit specializations are applicable and cannot be distinguished by the language's resolution rules, compilation fails with an ambiguity error.

The compiler must not arbitrarily select one of the specializations.

#### 11.5 Partial Specialization

Partial specialization is not supported in the current version of Gaïa.

## Extensions

### 1. General Principles

Extensions provide syntactic sugar for associating ordinary functions with existing types.

They allow types to interact without requiring direct dependencies between their original declarations.

Extensions do not modify the underlying definition of the extended type.

### 2. Extension Declarations

Extensions are declared using the `extend` keyword.

Example:

```gaia
extend List<String> {
    fn join(self, sep: &String) {
        // ...
    }
}
```

Template extensions are also supported.

Example:

```gaia
extend<T> Baz<T> {
    fn process(self, command: &Command) {
        // ...
    }
}
```

### 3. Extension Scope and Visibility

An extension must be declared before it is used.

Extensions may be declared in two contexts:

- Alongside the declaration of the type that provides the integration.
- Within the code that requires the integration between otherwise unrelated types or modules.

Extensions are therefore explicitly introduced rather than being globally available merely because their target type is known.

### 4. Extension Methods

Functions declared inside an extension behave syntactically as methods of the extended type.

However, extensions remain ordinary functions from a semantic perspective.

Their invocation syntax is equivalent to calling the corresponding function with the extended object as its first argument.

### 5. Interoperability

Extensions allow independent modules and types to cooperate without introducing dependencies between their original implementations.

Example:

```gaia
extend File {
    pub fn write(self, document: &DomDocument) {
        // ...
    }
}
```

This allows functionality involving both `File` and `DomDocument` to be implemented without requiring either type to know about the other.

### 6. Extensions and Inheritance

An extension declared for a class also applies to classes derived from that class, regardless of whether the extension was accessible when the derived class was declared.

However, extension methods become candidates for overload resolution only in contexts where the corresponding extension is accessible. Their applicability to a derived type does not make the extension itself globally visible.

Extensions do not modify the definition of the extended type. They only introduce additional public methods and do not grant access to the type's private or protected members.

In particular, extension methods do not participate in the rules governing the implicit generation or deletion of constructors, assignment operators, destructors, or other special member functions.

## Concepts

### 1. General Principles

Concepts define compile-time requirements on types and expressions.

They are parameterized declarations that evaluate whether their arguments satisfy the specified requirements.

Concepts may be composed using logical operators and may contain expression requirements.

### 2. Concept Declaration

Concepts are declared using the `concept` keyword.

The general syntax is:

```gaia
concept ConceptName<Parameters> = Expression;
```

Example:

```gaia
concept Fooable<T> = Barable<T> && Bazable<T>;
```

### 3. Concept Composition

Concepts may be combined using logical operators.

Supported operators include:

- `&&`: Logical conjunction.
- `||`: Logical disjunction.
- `!`: Logical negation.

Concept composition allows complex requirements to be built from simpler concepts.

### 4. Requires Expressions

The `requires` expression allows requirements to be defined in terms of expressions.

Its general syntax is:

```gaia
requires(parameters) {
    requirements...
}
```

Parameters are local to the requires expression and are used to describe expressions that must be valid.

#### 4.1 Requires Parameters

Parameters declared within a requires expression follow the same declaration syntax and mutability rules as ordinary function parameters.

Parameter mutability must be explicitly specified.

Examples:

```gaia
requires(value: T) {
    value.size();
}

requires(mut value: T) {
    value.clear();
}
```

The declared mutability determines which operations are valid within the requires expression.

A requirement involving a mutable operation must explicitly declare its corresponding parameter as mutable.

#### 4.2 Parameter Mutability and Ownership

Parameters within requires expressions follow the same rules as ordinary function parameters.

This includes the `self` parameter.

The following parameter forms are supported:

- `value: T`: immutable reference.
- `mut value: T`: mutable reference.
- `move value: T`: value transfer.

Concept requirements may therefore validate methods according to their receiver mutability and ownership requirements.

### 5. Expression Requirements

An expression requirement validates that an expression is well-formed.

An optional return-type constraint may be specified using `->`.

Example:

```gaia
concept Sortable<T> = requires(a: T, b: T) {
    { a < b } -> ConvertibleTo<Bool>;
};
```

The expression `a < b` must be valid and its result must satisfy `ConvertibleTo<Bool>`.

### 6. Template Constraints

Concepts may be used directly as template parameter constraints or inside `requires` clauses.

Example:

```gaia
class Foo<T: Fooable> {
}
```

Equivalent to:

```gaia
class Foo<T> requires Fooable<T> {
}
```

### 7. Type Declarations and Requirements

The `type` keyword is used for type aliases, associated type requirements and explicit type parameter constraints.

#### 7.1 Type Aliases

The `type` keyword declares a type alias.

Example:

```gaia
type FooRef = &Foo;
type StringList = List<String>;
```

#### 7.2 Associated Type Requirements

The `type` keyword may be used inside a requires expression to verify that a type member exists and refers to a valid type.

Example:

```gaia
concept Container<T> = requires {
    type T::ValueType;
};
```

#### 7.3 Type Parameter Constraints

The `type` keyword may explicitly constrain a generic parameter to represent a type.

Example:

```gaia
class Foo<T: type> {
}
```

## Error Handling

Gaïa provides two complementary error-handling mechanisms: native exceptions and explicit result values.

Native exceptions are part of the language and provide a mechanism for propagating exceptional conditions through the call stack. Alternatively, the standard library provides a `Result<T, E>` type for APIs that prefer explicit error handling without exceptions.

`Result<T, E>` is an ordinary standard-library type, implemented as a union representing either a successful value of type `T` or an error value of type `E`. Its behavior is comparable to `std::expected` in C++.

Neither mechanism implicitly converts into the other. Conversion between exceptions and result values must always be explicit.

## Exceptions

### 1. Throwing Exceptions

An exception is an arbitrary value thrown to represent an exceptional condition. The language does not impose a common base class or a specific exception type.

The `throw` keyword raises an exception using the provided value.

```gaia
throw RuntimeError("Unexpected operation");
throw "Invalid input";
throw 42;
```

The exception value is preserved as an exception context and remains valid for as long as it can still be accessed, including from an active exception handler.

The standard library provides predefined exception types to facilitate common error-handling scenarios. These types derive from a common `Exception` base class.

Consequently, declaring `throw (Exception)` covers all standard-library exception types derived from `Exception`, but does not cover arbitrary exception types or primitive values.

Custom exception types may derive from `Exception`, but are not required to do so.

### 2. Exception Contracts

Every function and method must declare the exception types it may allow to propagate through its interface.

The `throw` clause is part of the function signature and explicitly lists the exception types that may escape the function.

```gaia
fn make_value() -> Int32 throw (RuntimeError, LogicError) {
    // ...
}
```

A function may only allow exceptions covered by its declared contract to propagate to its caller. An exception that is neither handled locally nor covered by the function's `throw` clause results in a compile-time error.

An exception type listed in a `throw` clause covers values of that type and values compatible with it according to the language's type compatibility rules. In particular, declaring a base exception type also covers its derived types.

Multiple exception types may be declared in the same clause.

```gaia
fn perform_operation() -> Int32 throw (Exception, Int32) {
    // ...
}
```

A declaration without a `throw` clause represents an empty exception contract. Such a function cannot allow any exception to propagate beyond its execution.

### 3. Propagating Exceptions

The `try` keyword explicitly propagates exceptions from an expression to the caller.

```gaia
fn caller() -> Int32 throw (RuntimeError) {
    let value = try make_value();
    return value;
}
```

Every exception that can escape the evaluated expression must be covered by the current function's exception contract. Otherwise, the compiler reports an error.

The `try` keyword may also precede a block containing multiple operations.

### 4. Catching Exceptions

Exceptions can be handled locally using `catch` clauses.

A `catch` clause specifies the type of exception it handles. The exception is exposed to the handler through a reference.

```gaia
foo() catch error: &RuntimeError {
    print(error);
    bar();
}
```

When used without a preceding `try`, the `catch` clauses must exhaustively cover every exception that the protected expression may raise. Otherwise, the declaration is invalid.

Alternatively, `try` may be combined with `catch` to allow partial exception handling.

```gaia
try foo() catch error: &RuntimeError {
    print(error);
    bar();
}
```

This is a shorthand for the following form:

```gaia
try {
    foo();
}
catch error: &RuntimeError {
    print(error);
    bar();
}
```

In this form, exceptions not handled by the available `catch` clauses propagate to the caller and must be covered by the current function's exception contract.

Multiple `catch` clauses may be associated with the same expression or block.

```gaia
try foo()
catch error: &FileError {
    handle_file_error(error);
}
catch error: &RuntimeError {
    handle_runtime_error(error);
}
catch error: &Exception {
    handle_generic_error(error);
}
```

Handlers are examined in declaration order. The first handler whose type is compatible with the dynamic type of the exception is executed.

More specific exception types must therefore be handled before their respective base types. A handler that can never be selected because an earlier handler already covers its entire exception category is considered unreachable and produces a compile-time diagnostic.

A handler may also omit its type:

```gaia
try foo()
catch error {
    handle_unexpected_error(error);
}
```

An untyped `catch` handles any exception not already handled by preceding clauses, regardless of its type. It must be the final handler in the sequence.

Typed handlers may catch any type, including primitive types and types unrelated to the standard-library `Exception` hierarchy.

### 5. Rethrowing Exceptions

The `throw;` statement rethrows the exception currently being handled.

Unlike throwing a new value, rethrowing preserves the original exception context and its dynamic type.

```gaia
fn process() throw (Exception) {
    try operation()
    catch error: &FileError {
        log(error);
        throw;
    }
}
```

The rethrown exception remains subject to the current function's exception contract or to any enclosing handler capable of handling it.

A bare `throw;` is only valid within an active exception handler.

## Exception Contracts and Function Types

Exception contracts are an integral part of function signatures and function types.

This applies uniformly to ordinary functions, methods, local functions, lambda functions, function pointers, and overloaded operators.

A function's exception contract may be explicitly declared or, where supported, inferred from its body. In either case, the resulting contract is part of its function type.

```gaia
let operation = fn() throw (RuntimeError) {
    throw RuntimeError("Failure");
};

let callback: fn() -> Int32 throw (RuntimeError);
```

Function types with different exception contracts are distinct types. Assignments, argument passing, and other conversions must respect exception-contract compatibility.

A function with a more restrictive exception contract may be used where a function with a more permissive contract is expected. The reverse is not permitted.

### 1. Virtual Methods

The exception contract is part of the signature of a virtual method and must be respected by every override.

An overriding method may restrict the exception contract of its base method, but must never broaden it.

For example, if a base method declares `throw (Exception)`, an override may declare `throw (RuntimeError)` or no exception contract at all.

However, an override declaring an exception type not covered by the base method's contract is invalid.

This guarantees that a virtual call made through a base-class interface can never propagate an exception that the base interface does not declare.

### 2. Operators

Overloaded operators may declare exception contracts in the same manner as ordinary functions and methods.

When an overloaded operator may throw an exception, its use must occur in an exception-aware context, such as a `try` expression or a `catch` construct.

```gaia
let result = try a + b;
```

An overloaded operator with a non-empty exception contract cannot be used as an ordinary built-in operation in a context that does not account for its exceptions.

Intrinsic language operators are unaffected by this restriction.

### 3. Constructors and Conversions

Constructors may declare exception contracts, including ordinary constructors and explicit conversion constructors.

A constructor that throws an exception causes the construction to fail. The resulting object is not considered constructed.

Implicit conversion constructors declared with `implicit init` cannot declare an exception contract. Implicit conversions must never introduce an exception that would require explicit exception handling.

A conversion that may throw must therefore use an explicit constructor invocation.

```gaia
class FileHandle {
    pub init(mut self, path: String) throw (FileError) {
        // ...
    }
}

let handle = try FileHandle(path);
```

### 4. Destructors

Destructors declared with `deinit` cannot declare an exception contract.

A destructor cannot allow exceptions to propagate. Any operation that may throw must be handled locally and exhaustively.

An unhandled potentially throwing operation inside a destructor is a compile-time error.

This restriction ensures that automatic destruction and stack unwinding cannot introduce an additional unhandled exception.

## Exceptions in Templates and Concepts

Templates must explicitly declare the exception contracts of their functions and methods. Exception contracts are not inferred from the concrete types used during instantiation.

During template instantiation, the compiler verifies that every operation performed on substituted types respects the declared exception contract.

If an operation may propagate an exception that is neither handled locally nor covered by the template's declared contract, instantiation fails with a compile-time error.

This follows the language's Substitution Failure Is an Error rule.

Concepts and inline requirements may constrain the exception contracts of the functions and methods they require.

```gaia
concept Transformer<F, Input, Output> =
    requires(f: F, input: Input, output: Output) {
        fn F::invoke(self, value: Input) -> Output throw (RuntimeError);
    };
```

An implementation satisfies such a requirement only if its function signature is compatible with the required exception contract. In particular, it may provide a more restrictive contract, but cannot declare additional exceptions outside the required contract.

## Stack Unwinding and Object Destruction

When an exception propagates through the call stack, all local variables whose scopes are exited are destroyed.

Local variables are destroyed in the reverse order of their declarations.

Destruction follows the normal object lifetime rules of the language. Destructors are invoked for fully constructed objects, and their attributes and base subobjects are destroyed according to the established destruction order.

If construction of an object fails, its destructor is not invoked. Only the attributes and subobjects whose construction completed successfully are destroyed, in the reverse order of their construction.

Stack unwinding does not perform any implicit state recovery beyond normal object destruction.

### 1. Resource Management and RAII

Resource cleanup and state restoration must rely on RAII.

Destructors are responsible for releasing resources and restoring invariants when objects leave their scopes, including during exception propagation.

No implicit recovery operation is performed during exception handling other than normal destruction and the explicit execution of `catch` handlers.

A `catch` handler may perform any ordinary operation permitted by the language, including throwing another exception. Exceptions raised within a handler are subject to the normal exception-contract rules and may be handled by enclosing handlers.

## Exception Pointers

The standard library provides an exception-pointer type analogous to `std::exception_ptr` in C++.

This type allows an active exception to be captured and its context to be preserved independently of the current exception handler.

An exception pointer may be copied, stored, and transferred between threads. It preserves the original exception value and its dynamic type.

An exception pointer may represent the absence of an exception.

Capturing an exception and subsequently rethrowing it are explicit operations. Rethrowing an exception through an exception pointer restores the original exception context without reconstructing a new exception value.

The precise storage, allocation, and lifetime-management mechanisms are implementation details, provided that the observable lifetime guarantees of exception contexts are respected.

## Exceptions and Threads

In the initial language version, a function that may allow an exception to propagate cannot be executed directly as a thread entry function.

Exceptions must be handled within the originating thread or explicitly transferred using the standard exception-pointer mechanism.

A thread may capture an active exception and communicate its exception pointer to another thread. The receiving thread may then explicitly rethrow the original exception and handle it according to its own exception contract.

Exception propagation between threads is never implicit.

## Result Values and Exceptions

The standard library provides `Result<T, E>` as an alternative to native exceptions.

`Result<T, E>` is a regular union type that represents either a successful value or an error value. It provides functionality comparable to `std::expected`.

Using `Result` does not introduce an exception contract by itself. Its errors are ordinary values and must be handled through the mechanisms provided by the type.

Conversion between `Result` values and exceptions is always explicit.

An error value may be explicitly thrown as an exception. Conversely, an exception may be explicitly captured and used to construct an error value in a `Result`.

No automatic conversion between these two error-handling mechanisms is performed.

## Modules and Compilation

### 1. Modules and Fragments

A module is an independent compilation and distribution unit. It defines its own namespace and constitutes the smallest unit that can produce a standalone compiled artifact importable by other modules.

A module is declared using the `module` keyword:

```gaia
module Network {
    export class Connection {}
    export type Port = UInt16;
}
```

The source file containing the module declaration is its entry point. A module may be divided into multiple source files to organize its implementation and public interface.

Such additional source files are called *fragments*. A fragment belongs to a single module and does not constitute an independently importable module. It may nevertheless produce intermediate compilation artifacts to support incremental compilation.

A fragment is semantically part of its enclosing module, but has its own visibility scope. In particular, declarations that are not explicitly exported are accessible only within the fragment in which they are declared.

Fragments are imported using a dot-prefixed path:

```gaia
import .Network;
import .Network.Tcp;
```

An import without a leading dot refers to an independent module:

```gaia
import Collections;
import Network;
```

Fragment paths are resolved relative to the source file containing the import declaration.

A fragment may import other fragments located in the same directory or in one of its descendant directories. It cannot import fragments located in a parent or sibling directory. Parent fragments and the module entry point are responsible for aggregating their descendant fragments.

Fragments may depend on one another cyclically, provided that their dependencies respect these directory hierarchy rules. The compiler collects declarations across the relevant fragments before resolving their references, so forward declarations are not required merely to handle dependencies between fragments.

Such cyclic dependencies do not remove the ordinary restrictions on type completeness. For example, a type cannot directly contain itself, or participate in an infinitely sized recursive containment relationship. Indirection through references or pointers may be used to break such cycles.

### 2. Namespaces

Namespaces provide logical name scopes independently of modules and fragments.

A namespace may be declared in multiple places, including in different fragments of the same module. These declarations contribute to the same namespace:

```gaia
namespace Collections {
    class List {}
}
```

```gaia
namespace Collections {
    class Dictionary {}
}
```

Both declarations belong to the same `Collections` namespace.

Namespaces do not create compilation units, modules, or independently importable artifacts.

Each module has its own namespace. Importing or re-exporting declarations from another module does not flatten their namespaces. Declarations remain accessible through their original module and namespace qualification.

For example, importing a module named `Standard` does not make its `Collections` namespace members available directly under `Standard`. They remain accessible through their qualified names, such as `Standard::Collections::List`.

### 3. Visibility and Export

Declarations are local to their fragment by default. A declaration must be explicitly exported to be accessible outside that fragment.

The `export` keyword makes a declaration part of the fragment's exported interface:

```gaia
export class TcpConnection {}
export type Port = UInt16;
```

An exported declaration is accessible to fragments that import its defining fragment, and may be exposed through the module's public interface by re-exporting that fragment.

A declaration without `export` remains accessible only within its defining fragment, even when another fragment belongs to the same module.

#### 3.1 Namespace Export

The `export` keyword may also be applied to a namespace declaration.

An exported namespace exports the declarations associated with that namespace within the exported namespace definition:

```gaia
export namespace Collections {
    class List {}
    class Dictionary {}
}
```

In this example, both `List` and `Dictionary` are exported.

A namespace declared without `export` does not automatically export its contents. Individual declarations must be explicitly marked:

```gaia
namespace Collections {
    export class List {}
    class InternalNode {}
}
```

Here, `List` is exported, whereas `InternalNode` remains local to its fragment.

### 4. Importing and Re-exporting Fragments

The `import` keyword makes the exported declarations of an imported fragment available to the importing fragment.

Importing a fragment does not automatically re-export its declarations. To expose them further, the importing fragment must explicitly use `export import`.

For example:

```gaia
// Tcp.gaia
export class TcpConnection {}
```

```gaia
// Transport.gaia
import .Tcp;
export import .Udp;
```

```gaia
// Network.gaia
module Network {
    export import .Transport;
}
```

In this example, `TcpConnection` is accessible within `Transport`, but is not re-exported by it. The declarations exported by `Udp` are re-exported through `Transport` and consequently become part of the public interface of `Network`.

Each aggregation level must explicitly re-export the declarations it intends to expose.

Importing an independent module does not make that module part of the importing module's public interface. Module imports cannot be re-exported using `export import`.

A module may, however, expose declarations whose types originate from another module. This does not automatically make the originating module an imported module of its consumers.

### 5. Name Resolution and Conflicts

Import order does not affect name resolution. The compiler considers the complete set of declarations and imports relevant to a fragment when resolving names.

Multiple import paths that ultimately refer to the same declaration do not create an ambiguity. The compiler recognizes the identity of the imported declaration.

Conversely, two distinct declarations that introduce the same accessible name in a given scope constitute a conflict. Such conflicts are compilation errors.

A conflict between an imported declaration and a local declaration is also an error. A local declaration cannot silently shadow an imported declaration.

Declarations in different fragments of the same module must not accidentally share the same name. They must either belong to different namespaces or use distinct names.

Declarations originating from different modules are distinguished by their respective module namespaces. Their names do not conflict merely because their unqualified names are identical.

### 6. Module Dependencies

Modules explicitly declare their dependencies in project or module configuration rather than embedding dependency declarations in source-level import statements.

An import identifies a module by name only:

```gaia
import Collections;
import Network;
```

Dependency versions and constraints are specified separately in the relevant configuration.

Dependencies are classified according to their role:

- **Build-time dependencies (`buildtime`)** are required to compile the module itself, but are not necessarily required by consumers.
- **Interface dependencies (`interface`)** are required to compile code that consumes the module's public interface. This includes dependencies needed to understand types or declarations exposed by that interface.
- **Runtime dependencies (`runtime`)** are required when executing code that uses the module.

A dependency may belong to more than one category.

Module metadata records its dependencies, their roles, and their version constraints. Dependencies are resolved recursively, without automatically making transitive dependencies available as source-level imports to consumers.

Compiler-provided modules have their own versions and cannot be arbitrarily replaced by user-provided modules.

#### 6.1 Dependency Isolation and Versions

Each module is compiled in its own dependency context. Its compilation uses the versions of its dependencies specified by its own configuration, independently of the dependency versions used by other modules in the same application.

Consequently, two modules may depend on different versions of the same dependency.

For example, one module may be compiled against `Collections` version 1.x while another is compiled against version 2.x.

The final linking or loading stage is responsible for resolving the resulting dependencies. Depending on the selected linking mode and the compatibility of the modules involved, multiple versions may coexist.

A static link may incorporate dependency implementations into the resulting artifact. A dynamic link may load separately versioned libraries.

The ability to use multiple versions simultaneously depends on more than source-level compatibility. Binary compatibility, symbol isolation, type identity, and shared state must also be taken into account.

When a dependency version changes, affected compiled artifacts must be rebuilt to ensure consistency. The compiler and build system may use dependency metadata and build configuration to determine which artifacts are affected.

### 7. Compiled Module Artifacts

A compiled module produces a single standalone artifact containing the information necessary for its use by other modules and its eventual execution.

Conceptually, such an artifact contains several distinct sections:

- **Module metadata**, including module identity, version information, compiler and ABI compatibility information, public declarations, and dependency information.
- **Binary data**, containing the compiled implementation.
- **Resources**, when applicable.

The metadata is used by the compiler to resolve imports, check types, and perform overload resolution without requiring access to the original source files.

The binary data is used by the linker or runtime loader according to the selected linking mode.

The precise physical format of these artifacts is implementation-defined and is specified separately from the language semantics.

Cross-compilation may produce distinct artifacts for different target platforms or architectures.

### 8. Linking

Gaïa supports both static and dynamic linking.

Each module declares a linking preference and the linking modes it supports.

The linking preference is a recommendation, not a mandatory constraint. Unless explicitly specified otherwise, a module's linking preference is `static`.

The module's supported linking modes define its actual compatibility constraints. A module may support static linking, dynamic linking, or both.

The Gaïa runtime and standard library follow the same default preference and are statically linked unless the project explicitly requests another compatible mode.

#### 8.1 Project Linking Policy

A project defines a linking policy that determines how the preferences of its dependencies are handled.

The default policy is `follow`, meaning that each dependency is linked according to its own linking preference.

A project may instead explicitly request `static` or `dynamic` linking.

The effective linking mode is determined independently for each module:

- Under the `follow` policy, the module's declared preference is used.
- If the project explicitly requests a mode that differs from the module's preference but is supported by that module, the project's request takes precedence.
- If the project requests a mode that the module does not support, compilation or linking fails with an error.

Consequently, a project using the default `follow` policy may contain a mixture of statically and dynamically linked modules.

A project-wide linking request does not override a module's technical compatibility constraints.

## Macros and Reflection

### 1. Overview

Gaïa provides a unified compile-time metaprogramming system based on macros. Macros are meta-functions that manipulate the syntactic representation of Gaïa programs.

Unlike ordinary functions, macros do not operate on evaluated runtime values. Their parameters and return values are metasyntactic elements representing portions of program syntax or semantic information made available by the compiler.

Reflection is integrated into this system through built-in macros. There is no separate reflection subsystem: all compile-time inspection and semantic queries are performed through the macro mechanism.

### 2. Compilation Phases

Compilation takes place in two main phases.

During the first phase, the lexer processes the source code into tokens, and the parser converts those tokens into an Abstract Syntax Tree (AST).

During the second phase, the compiler analyzes the AST and produces the resulting program. Macro evaluation takes place during this phase.

When the compiler encounters a macro invocation, it evaluates the macro, replaces the invocation with the AST returned by the macro, and resumes compilation using the resulting syntax.

Macro evaluation therefore occurs within the compiler's semantic analysis phase and can access information already known to the compiler at that point.

The availability of semantic information depends on the compilation state when the macro is evaluated. Declarations encountered earlier may already be known, while other declarations or types may still be incomplete or unresolved.

### 3. Macro Declarations and Invocation

A macro is declared using the `macro` keyword, followed by a declaration otherwise resembling an ordinary function declaration.

For example:

```gaia
macro typeof(expr: Expression) -> Type {
    // ...
}
```

Macro parameters and return values use metasyntactic types rather than ordinary Gaïa types.

Macro arguments are passed as AST representations. Their expressions are not evaluated before being passed to the macro.

A macro returns a metasyntactic element representing the syntax to insert in place of its invocation. The returned element is then compiled as part of the surrounding program.

Macros may invoke other macros, including built-in macros. Recursive macro invocations are also permitted, provided that evaluation eventually terminates.

The result of a macro must be valid in the syntactic context where the invocation occurs. For example, a declaration cannot be inserted where an expression is required.

### 4. Metasyntactic Types

Metasyntactic types form a dedicated type system used exclusively by the metaprogramming subsystem.

They provide semantics analogous to ordinary Gaïa types, including type identity, hierarchies, specialization and polymorphism. However, they are not actual Gaïa types.

Metasyntactic types have the following restrictions:

- Their definitions are entirely controlled by the language.
- Users cannot declare new metasyntactic types.
- They cannot be used outside macro evaluation.
- They cannot be used as types of ordinary variables, attributes, function parameters or return values.
- They cannot be stored in ordinary program data.

The metasyntactic type hierarchy allows a value to be tested against a general category even when it represents a more specialized syntactic element. For example, `Identifier` is encompassed by `Expression`.

The exact set of metasyntactic types and their relationships is defined by the language.

Metasyntactic values represent compiler-managed syntactic or semantic information. They do not behave as ordinary objects:

- Manipulating them does not create copies of the represented elements.
- They are immutable.
- They cannot be referenced using Gaïa's ordinary reference mechanisms.
- They remain valid for as long as they are accessible during macro evaluation.

Their internal representation, storage and lifetime management strategy are implementation details of the compiler.

### 5. AST Inspection and Construction

Syntactic elements are represented by structured metasyntactic values, using structures and enumerations provided by the language.

For example, expressions can be represented by a hierarchy conceptually similar to:

```gaia
enum struct Expression {
    Literal(LiteralExpression),
    Identifier(IdentifierExpression),
    Binary(BinaryExpression),
    Unary(UnaryExpression),
    FunctionCall(FunctionCallExpression),
    MemberAccess(MemberAccessExpression),
    // ...
}

struct BinaryExpression {
    operator: BinaryOperator;
    left: Expression;
    right: Expression;
}
```

The actual set of expression categories and their representation are defined by the language.

AST elements can be inspected, traversed, compared where meaningful, and used to construct new elements.

AST construction uses the ordinary structure and enumeration construction syntax of Gaïa. No separate quoting syntax or AST construction language is required.

For example:

```gaia
macro add(lhs: Expression, rhs: Expression) -> Expression {
    return Expression::Binary {
        operator: BinaryOperator::Add,
        left: lhs,
        right: rhs
    };
}
```

Constructing or inspecting an AST element does not, by itself, trigger semantic analysis.

A syntactically valid AST element does not necessarily represent a semantically valid program fragment. Semantic validity is checked when the element is inserted into the program and compiled, or when a macro explicitly requests semantic information about it.

AST elements are immutable. Any transformation produces new syntactic elements rather than modifying existing ones.

### 6. Built-in Macros

Built-in macros are part of the same macro system as user-defined macros. They are provided by the compiler and expose compile-time information and operations.

They can be divided into two broad categories.

#### 6.1 Compiler Information

Some built-in macros return compile-time constants describing the compilation environment, such as the build configuration, target architecture, target operating system or compiler version.

For example:

```gaia
build_type()
```

These results are metasyntactic values and can be inspected or compared by other macros.

#### 6.2 Semantic Queries

Other built-in macros explicitly request semantic information from the compiler about a syntactic element.

For example:

```gaia
typeof(expr)
```

This macro asks the compiler to determine the type of the expression represented by `expr`.

Semantic queries are evaluated in the context of the current compilation state. The compiler may need to resolve identifiers, determine expression types or inspect declarations before returning the requested information.

If the requested information is not available, the built-in macro raises a fatal compilation error.

Such errors cannot be intercepted by the calling macro. Macros that need to account for potentially unavailable information must use built-in test macros instead.

#### 6.3 Built-in Tests

Built-in test macros allow macros to check properties of syntactic or semantic elements without raising an error when the tested property is not satisfied.

Examples include:

- `is_defined(element)`, to test whether an element is defined or resolved.
- `is_expression(element)`, to test whether an element belongs to the expression category.
- `is_complete(type)`, to test whether a type is fully defined.

The metasyntactic type hierarchy and polymorphism determine the relationships between syntactic categories. For example, an identifier also satisfies a test for an expression.

The exact set of built-in tests is defined by the language.

### 7. Semantic Analysis Is Explicit

Passing an AST element to a macro does not automatically require the compiler to analyze it semantically.

A macro can inspect an expression's syntax, transform it or discard it without requiring the expression to be semantically valid.

Semantic analysis occurs only when the compiler needs it to compile the resulting program or when a macro explicitly requests semantic information through a built-in macro.

This distinction allows macros to generate conditional code without requiring every possible branch to be semantically valid in every compilation configuration.

For example:

```gaia
macro assert(expr: Expression) -> Expression {
    if build_type() == "debug" {
        return expr;
    }

    return Expression {};
}
```

In a release build, the expression may be discarded without requiring its semantic analysis.

Conversely, if a macro explicitly invokes `typeof(expr)`, the compiler must analyze that expression at that point. If the required information cannot be determined, compilation fails.

### 8. Symbols and Identifiers

A `Symbol` is a special metasyntactic type representing the textual name of an identifier.

It behaves similarly to a string for construction and comparison, but is intended specifically for symbol names.

An identifier's symbol is textual information, not a direct reference to a compiler declaration.

Constructing an identifier from a symbol does not resolve that identifier. Name resolution takes place when the generated AST is compiled in its insertion context.

Macros can therefore construct identifiers dynamically, inspect their names and use them to build expressions and declarations.

### 9. Unique Identifiers and Name Resolution

Once generated AST is reinserted into the program, it is compiled according to the ordinary name resolution rules of Gaïa.

Macros may request the compiler to generate unique identifiers. These identifiers allow generated declarations to avoid collisions with existing names.

Macros may also preserve or construct identifiers referring to existing symbols. This allows generated code to intentionally reference declarations outside the macro-generated syntax.

No automatic isolation of identifiers is imposed on generated code. Name resolution follows the ordinary rules of the language, with unique identifier generation available when needed.

### 10. Annotations

Annotations are syntactic metadata associated with declarations and other language elements.

They are represented uniformly by a symbol and a list of symbol arguments:

```gaia
struct Annotation {
    symbol: Symbol;
    arguments: Symbol[];
}
```

The interpretation of an annotation depends on the component that consumes it. The annotation representation itself does not impose any intrinsic semantic meaning.

For example:

```gaia
@deprecated("use something else")
@ignore(memory-self-move)
@hack(do_the_thing)
```

The compiler may interpret certain annotations, such as `@deprecated` or `@ignore`, while user-defined macros may inspect and interpret their own annotations.

Annotations can be associated with types, declarations, attributes and other syntactic elements supported by the language.

Macros can inspect annotations while traversing the AST and use them to determine what code to generate.

For example, a macro may inspect a class declaration, find methods carrying a particular annotation and generate corresponding wrapper declarations.

### 11. Macro Evaluation Restrictions

Macro evaluation is pure and isolated from ordinary program execution.

Macros cannot perform side effects or access external resources. In particular, they cannot:

- Access the filesystem.
- Read environment variables.
- Perform system calls.
- Execute ordinary runtime functions.
- Directly modify compiler state or the compilation environment.

Only metasyntactic elements, built-in macros and operations provided by the metaprogramming subsystem are available during macro evaluation.

Ordinary `const fn` functions are not automatically available to macros. Compile-time function evaluation and macro evaluation are distinct mechanisms.

### 12. Macro Visibility and Modules

Macro declarations follow the ordinary declaration and visibility rules of Gaïa.

They can be declared in modules and module fragments, exported and imported like other declarations.

Their availability is therefore determined by the same module visibility and name resolution rules as ordinary declarations.

Name conflicts involving macros follow the ordinary declaration conflict rules.

### 13. Expansion and Compilation

Macro expansion is part of the compiler's AST analysis phase.

The compiler evaluates each macro invocation, inserts the resulting AST at the invocation site and continues compilation using the resulting syntax.

Generated AST is subject to the same parsing-independent semantic checks, name resolution rules, type checking and other compilation rules as source-written AST.

Macros may generate expressions, statements, declarations, types and other syntactic elements, provided that the generated elements are valid in their insertion context.

The macro system does not bypass the language's semantic rules. It provides a mechanism for generating and transforming syntax before that syntax is compiled normally.

## Concurrency and Memory Model

### 1. Concurrency Model

Gaïa does not provide a built-in thread management or scheduling system.

Thread creation, termination, synchronization and scheduling are handled by libraries. This allows applications to choose the execution model best suited to their requirements and the target platform.

The standard library may provide basic facilities for working with native threads, while other libraries may implement higher-level abstractions such as thread pools, coroutines, asynchronous tasks or alternative scheduling systems.

The language does not impose a particular concurrency abstraction or execution policy.

Future language versions may introduce additional syntax or compiler support to facilitate the integration of such abstractions without requiring a specific execution model.

### 2. Shared Memory and Data Races

Gaïa follows a permissive memory model similar to that of C++.

The language does not impose static restrictions on sharing data between threads. Sharing and synchronization are the responsibility of the programmer and the libraries being used.

A data race occurs when two or more threads access the same memory location concurrently, at least one access is a write, and the accesses are not properly synchronized.

A data race results in undefined behavior.

The memory model defines the synchronization and ordering guarantees required to prevent data races and establish visibility between threads.

In the absence of concurrent access, the compiler is free to apply the usual optimizations without having to account for hypothetical unsynchronized accesses from other threads.

Data that is local to a thread or used exclusively in a single-threaded context therefore requires no special concurrency handling.

### 3. Synchronization

Synchronization mechanisms are provided by libraries rather than built into the language.

The standard library is expected to provide common synchronization facilities, including:

- Locks and mutexes for protecting shared data and critical sections.
- Signaling and notification mechanisms for coordinating threads.
- Atomic operations for indivisible access to shared values.
- Channels for exchanging data between threads.

Libraries may provide additional synchronization abstractions or combine these mechanisms to implement higher-level concurrency models.

The language does not prescribe a particular synchronization API.

### 4. Atomic Operations

Atomic operations are initially provided through the standard library.

Their implementation may rely on compiler facilities, foreign function interfaces (FFI), native system primitives or processor instructions, depending on the target platform.

The language does not initially prescribe a dedicated atomic type system or a specific syntax for atomic operations.

The implementation of atomic operations must nevertheless respect the memory model and provide the synchronization and ordering guarantees specified by their interfaces.

Future compiler annotations or other compiler directives may be introduced to express properties that the compiler must preserve when optimizing such operations.

The exact requirements and mechanisms will be determined as the standard library and its implementations evolve.

### 5. Volatile Accesses and Memory Barriers

Compiler directives may be used to constrain optimization and code generation.

For example, an annotation such as `@volatile` may indicate that accesses to a particular object or memory location must follow specific compiler restrictions.

Similarly, memory barriers may require the compiler to preserve particular ordering constraints between memory operations.

These directives are distinct from atomic operations:

- Volatile access constrains certain compiler optimizations but does not make an operation atomic.
- Atomic operations provide indivisible access and may establish synchronization relationships.
- Memory barriers constrain the ordering of memory operations.

Volatile accesses alone do not prevent data races or establish inter-thread synchronization.

The exact semantics and available annotations will be specified according to the requirements of the compiler and standard library implementations.

### 6. Communication Between Threads

The standard library may provide channels and other communication facilities for exchanging data between threads.

The preferred communication model is based on transferring values rather than sharing references.

When a value is transferred by move, the ordinary ownership and move semantics of Gaïa apply. The sender relinquishes ownership of the transferred value, and the receiver becomes its owner.

Reference exchange is not prohibited, but requires an appropriate mechanism that guarantees reference validity and lifetime safety.

Such mechanisms must preserve the existing ownership, lifetime and memory model guarantees of Gaïa. They must not introduce exceptions to the language's ordinary lifetime rules.

### 7. Exceptions Across Threads

Exceptions cannot propagate directly from one thread into another.

Each thread has its own exception handling context. An exception escaping a thread's execution context must be handled according to the rules provided by the thread management library.

Libraries may explicitly capture an exception using `ExceptionPtr` and transfer it to another thread.

The receiving thread may then explicitly rethrow the captured exception within its own execution context.

This mechanism follows the ordinary exception handling rules of Gaïa and does not introduce implicit cross-thread exception propagation.

### 8. Thread Termination and Resource Lifetime

Thread termination and shutdown policies are the responsibility of the libraries managing the threads.

The language does not introduce special lifetime or destruction rules for thread-local resources.

Objects owned by a thread remain subject to the ordinary construction, ownership, destruction and exception unwinding rules of Gaïa.

Resources must therefore be destroyed according to the usual lifetime rules when their owning execution context ends.

Libraries are responsible for ensuring that their thread management policies are compatible with these rules.

## Native Interoperability

Gaïa provides interoperability with native C and C++ code. It can import declarations from native headers and modules, compile inline native code, and expose selected Gaïa functions and variables through the C ABI.

Native interoperability relies on Clang for parsing, semantic analysis, and compilation of C and C++ code. Gaïa does not attempt to reimplement C or C++ language rules or native ABI behavior.

### 1. Importing Native Code

Native headers can be imported using the `import` declaration with an explicit language specifier:

```gaia
import "C" <stdio.h>;
import "C++" <vector>;
import "C++" "mylib.hpp";
```

The language specifier determines whether the imported code is processed as C or C++.

C++20 named modules can also be imported when supported by the selected Clang toolchain:

```gaia
import "C++" std;
```

Support for named C++ modules is optional and depends on the capabilities of the underlying toolchain.

All declarations made accessible by an imported header or module are made accessible to Gaïa, including declarations originating from transitively included headers.

Native namespaces are preserved exactly as declared. In particular, C++ namespaces are neither flattened nor remapped.

### 2. Inline Native Code

Native code can be embedded directly in a Gaïa module using an inline import block:

```gaia
import "C++" {
    void foo(int value) {
        // C++-specific operations
    }
};
```

C code can be embedded in the same way:

```gaia
import "C" {
    #include <stdio.h>

    void print_value(int value) {
        printf("%d\n", value);
    }
}
```

Each inline block is an independent native translation unit. It is compiled separately by Clang using the corresponding C or C++ language semantics.

Inline blocks are fully isolated from one another:

- A block cannot access declarations from another inline block.
- A block cannot implicitly access declarations from the surrounding Gaïa module.
- Declarations and definitions required by a block must be provided within that block or through its explicitly included headers.
- Preprocessor definitions, including macros, are local to the block and cannot affect other blocks or independently imported headers.

Declarations made available by an inline block are exposed to Gaïa in the same way as declarations imported from a native header.

The compiled results of inline blocks are incorporated into their containing Gaïa module.

### 3. Native Types and Declarations

C and C++ types are mapped to equivalent Gaïa types whenever a compatible representation exists. This mapping is semantic rather than a literal translation of native declarations into Gaïa syntax.

The original C or C++ semantics remain in effect for native declarations and operations. Clang is responsible for determining their layout, alignment, calling conventions, and other ABI-related properties.

#### 3.1 Types

C and C++ structures and unions can be used directly as Gaïa types. Their native layout, fields, and alignment are preserved.

C++ classes can also be used as Gaïa types when their representation and operations can be correctly handled. This includes native inheritance hierarchies and polymorphic types.

Gaïa provides corresponding mechanisms for native C++ references and member pointers. C++ references are mapped to Gaïa references according to their mutability and the guarantees provided by the native declaration.

Native types retain their original identity and semantics. In particular, C++ types with different template specializations are distinct types.

#### 3.2 C++ Templates

C++ templates are handled entirely by the C++ compilation engine provided by Clang.

Gaïa does not implement C++ template instantiation, substitution, specialization, or overload resolution rules.

A C++ template specialization can be requested through ordinary Gaïa type usage:

```gaia
let values: std::vector<Int32>;
```

In this example, the C++ engine instantiates `std::vector` with a signed 32-bit integer type.

Once Clang has determined the specialization's layout, alignment, methods, and other relevant properties, Gaïa treats that specialization as a distinct external type.

#### 3.3 Methods and Overload Resolution

Methods of native C++ types can be called using ordinary Gaïa method-call syntax:

```gaia
let values: std::vector<Int32>;

values.push_back(42);
let size = values.size();
```

When a method is invoked on a native C++ type, Gaïa delegates overload resolution to Clang and adapts the call to the native C++ ABI.

This includes the handling of the implicit `this` parameter, references, arguments, return values, and virtual dispatch.

Gaïa does not reproduce C++ overload resolution rules.

#### 3.4 Object Lifetime and Special Member Functions

Native objects follow Gaïa's lifetime rules while preserving the semantics required by their native type.

Construction and destruction invoke the corresponding C++ constructors and destructors. Copy and move operations generated or selected by Gaïa must use the corresponding native C++ operations whenever required.

Gaïa-generated operations must never bypass native constructors, destructors, or overloaded assignment and transfer operators in a way that violates C++ object semantics.

#### 3.5 Native Variables

Native C and C++ variables can be accessed directly from Gaïa.

Their native qualifications, including `const` and `volatile`, are preserved when determining how they can be accessed and modified.

Their storage and lifetime remain governed by the native program and the corresponding native language rules.

### 4. Native Exceptions

C++ exceptions can propagate from native C++ code into Gaïa and can be handled using Gaïa's exception-handling mechanisms.

This requires a compatible exception ABI, runtime, and stack unwinding implementation.

Stack unwinding must correctly destroy both Gaïa and native C++ objects, according to their respective lifetime rules.

Gaïa exceptions must not escape from Gaïa code invoked by native C or C++ code. This restriction is enforced by the existing Gaïa language rules.

Consequently, exception propagation across the interoperability boundary is supported only from C++ into Gaïa, not from Gaïa into C or C++.

### 5. Native Preprocessor Macros

C and C++ preprocessor macros are not directly accessible from Gaïa.

Only the declarations and results produced after preprocessing are visible to Gaïa.

Preprocessor directives such as `#if` and `#ifdef` can affect which declarations are made available by an imported header or inline block.

Function-like macros may generate functions, types, variables, or other declarations that become accessible to Gaïa after preprocessing.

Macros and preprocessor constants do not automatically become Gaïa constants.

Native macros are not integrated into the Gaïa macro system.

Macros defined inside an inline native block remain confined to that block.

### 6. Exporting Gaïa Declarations

Gaïa functions and variables can be exposed to native code using the C ABI.

The `export "C"` declaration specifies that a declaration is made available through the C ABI:

```gaia
export "C" fn foo(value: Int32) -> Int32 {
    return value * 2;
}
```

This declaration specifies the ABI used when the function is exposed to native code. It does not, by itself, imply that the symbol must always be exported at the binary level.

Gaïa does not provide an equivalent mechanism for exporting declarations through a C++ ABI.

#### 6.1 Export Restrictions

Exported functions are subject to the following restrictions:

- Overloaded functions cannot be exported.
- An exported function cannot declare Gaïa exceptions in its signature.
- Gaïa exceptions must never escape through an exported function.
- The exported symbol name is exactly the name specified in the Gaïa declaration. No alternate name or renaming mechanism is provided.

Exported variables are also supported through the C ABI.

#### 6.2 Exported Types

Types used in exported function and variable declarations must be compatible with the C ABI.

The following types are permitted:

- Gaïa built-in and native types that have a corresponding C representation.
- External C types.
- External C++ types that Clang determines to be compatible with the C ABI.

The origin of an external type does not, by itself, prevent its use in an exported declaration. For example, a C++ structure or union can be used when it is compatible with the C ABI.

Other Gaïa-defined types cannot be exposed through this mechanism.

Clang is responsible for determining C ABI compatibility. Gaïa does not reimplement these compatibility checks.

### 7. Native Library Dependencies

Importing a native header or module does not automatically determine which native library provides its definitions.

Native library dependencies must therefore be declared explicitly in the project configuration.

The native standard library can be linked automatically by default, according to the selected platform and toolchain.

Gaïa does not attempt to discover other native libraries automatically. Their versions and version resolution are also outside the scope of Gaïa and remain the responsibility of the build environment and linker.

#### 7.1 Linkage Modes

Native libraries can be linked using either static or dynamic linkage.

- **Static linkage:** only the symbols actually used from the native library are incorporated into the resulting module. Native library symbols are not re-exported.
- **Dynamic linkage:** the resulting module depends on the native library at runtime.

The linkage mode is independent of the dependency modes described below.

#### 7.2 Dependency Modes

Native library dependencies can be classified using two independent modes:

- **`runtime`:** indicates that the native library is required at runtime.
- **`interface`:** indicates that the native library is required to consume the module's public interface.

These modes are not mutually exclusive.

A dynamically linked library always requires a `runtime` dependency. If its declarations are also used in the module's public interface, it additionally requires an `interface` dependency.

A statically linked library does not require a `runtime` dependency merely because it is used by the module. However, if native declarations from that library are exposed through the module's public interface, an `interface` dependency is required.

Dependency requirements propagate transitively through the module dependency graph. Each module declares its own dependencies, and the build system determines the dependencies required by consumers by traversing the dependency chain.

A module packages only its own symbols and dependency declarations. Native library symbols are never re-exported merely because they are used internally or referenced by an exported Gaïa declaration.

### 8. Native Compilation Environment

Gaïa uses Clang to compile native C and C++ code.

By default, Gaïa attempts to reproduce its own compilation environment when invoking Clang. This includes the target platform, architecture, toolchain, and other relevant compilation defaults.

Project configuration can provide additional parameters or override automatically determined values. These parameters are passed to Clang rather than interpreted through a separate Gaïa-specific native configuration system.

Configurable parameters include, but are not limited to:

- Header and module search paths.
- Compiler flags and other compilation options.
- Preprocessor macro definitions and undefinitions.
- C and C++ language standards.
- Platform-specific and toolchain-specific options.

#### 8.1 Configuration Scope and Inheritance

Native compilation parameters can be specified globally at the project level or locally for individual modules.

The same configuration mechanism is used at both levels.

A module inherits the global project configuration and can override individual parameters. When a parameter is defined at multiple levels, the definition closest to the module takes precedence. Parameters not overridden by the module remain inherited from the higher-level configuration.

The effective configuration of a module is strictly local to that module.

In particular, the native compilation configuration of an imported module does not affect the configuration used to compile its importer. Each module is compiled using its own effective native compilation environment.

### 9. Native Compilation Diagnostics

Errors encountered while parsing or compiling native code are reported through the Gaïa diagnostic system.

Gaïa emits an appropriate Gaïa error diagnostic describing the failure. The original Clang diagnostic is included as the detailed explanation of that error.

The original diagnostic information should be preserved as far as possible, including its message, severity, source location, and associated notes.

This allows native compilation failures to be reported consistently through Gaïa while retaining the detail and precision of Clang's diagnostics.

### 10. ABI Compatibility and Compilation Authority

Clang is the final authority for the analysis and compilation of native C and C++ code.

The C and C++ ABIs are selected automatically according to the target platform and toolchain, with project configuration available to adjust the native compilation environment when necessary.

Gaïa relies on Clang to determine whether a native declaration or operation can be correctly compiled and exposed through the selected ABI.

Any native construction that Clang cannot analyze, compile, or expose correctly results in an error.

Gaïa does not attempt to work around such limitations through emulation, alternative ABI implementations, or reinterpretation of native semantics.

## Low-Level Operations and Platform Capabilities

Gaïa does not provide dedicated language constructs for most low-level operations. Such operations are exposed through the standard library or platform-specific libraries, using native code where necessary.

This approach keeps the language independent of hardware and operating-system details while allowing programs to access low-level functionality when required.

### 1. Native Implementation of Low-Level Operations

The standard library may rely on native C or C++ code to implement operations that require direct access to hardware or platform facilities.

This includes, but is not limited to:

- Inline assembly.
- Processor intrinsics and specialized instructions.
- Access to hardware registers and privileged instructions.
- System calls and operating-system facilities.
- Unaligned memory accesses.
- Atomic operations and memory barriers.
- Low-level binary representation and manipulation.

These operations are exposed through standard library APIs rather than dedicated Gaïa language constructs.

The standard library may use inline native functions and other native facilities provided by the selected toolchain to implement these APIs.

Gaïa does not define a dedicated inline assembly syntax, intrinsic mechanism, or platform-specific instruction interface.

Such facilities may be introduced directly into the language or its standard library in a future version if concrete requirements justify doing so.

### 2. Standard and Platform-Specific Functionality

The standard library provides a consistent API for the standard functionality defined by Gaïa.

Standard APIs are platform-independent: their contracts do not expose platform-specific implementation details.

However, a standard library implementation is not required to provide functionality that cannot be supported by its target environment. For example, a target without the necessary facilities may not provide dynamic allocation or multi-threading support.

Platform-specific functionality is provided by separate platform-specific libraries rather than being incorporated into the standard library API.

This distinction allows the standard library to remain consistent across targets while still permitting access to platform-specific capabilities.

### 3. Feature Availability

The standard library defines feature availability macros as part of its public API.

These macros indicate whether a specific standard functionality is available in the selected standard library implementation.

Feature availability macros describe individual functional capabilities rather than broad platform characteristics or hardware properties.

Their granularity is defined at the level of independently usable capabilities. The list of supported features is maintained as part of the standard library specification.

Feature availability macros have the following properties:

- They indicate only whether the corresponding functionality is available.
- They do not describe implementation details, performance characteristics, or resource limits.
- Their names and semantics are defined by the standard library.
- They are not built-in language features and do not require individual compiler support.

More detailed information may be exposed through other generic macros, target-specific macros, or the standard library documentation.

Feature availability macros describe the availability of an API, not necessarily the availability of a corresponding hardware instruction or native system facility.

### 4. Standard Library Implementation Guarantees

The standard library guarantees the functionality and properties specified by its API contracts, not a particular implementation.

An implementation is free to choose any mechanism that satisfies the observable behavior and guarantees required by the corresponding API.

This freedom includes the use of native facilities, software implementations, alternative algorithms, or other implementation strategies.

An implementation may also adapt its behavior to the constraints of the target environment, provided that all specified guarantees remain satisfied.

For example, an API providing parallel execution may use a sequential implementation on a target without multi-threading support, provided that the API contract permits such behavior and its observable guarantees are preserved.

#### 4.1 Functional and Non-Functional Guarantees

API contracts may specify more than functional behavior.

They may also include guarantees and constraints concerning properties such as:

- Algorithmic complexity.
- Memory consumption.
- Resource usage.
- Alignment requirements.
- Other observable operational constraints.

An implementation must respect all guarantees specified by the API contract, including non-functional guarantees.

Consequently, an implementation cannot replace an algorithm with one having different complexity guarantees merely because both produce the same result.

#### 4.2 Canonical Implementations

Unless platform-specific constraints or other implementation requirements justify a different approach, the canonical implementation is the reference for standard library functionality.

Implementations should not diverge from the canonical implementation without a concrete justification.

Platform-specific adaptations are permitted when necessary to provide the specified functionality or satisfy its guarantees on the target environment.

Such adaptations must preserve the complete API contract, including its functional and non-functional guarantees.

## Undefined Behavior and Language Guarantees

### 1. General Principles

Gaïa aims to provide defined and predictable behavior whenever reasonably possible.

The language prioritizes defined behavior, except when providing such guarantees would:

- Introduce significant runtime overhead.
- Restrict programming flexibility or prevent legitimate low-level operations.
- Conflict with guarantees or requirements imposed by third-party systems or native interfaces.

Gaïa does not use unspecified behavior as a language-level category. Whenever multiple behaviors are possible, the specification must either define the behavior or explicitly classify it as implementation-defined or undefined.

#### 1.1 Defined Behavior

Defined behavior is behavior for which this specification guarantees the observable result or permitted effects.

An implementation must preserve these guarantees regardless of its optimization strategies or internal representation.

#### 1.2 Implementation-Defined Behavior

Implementation-defined behavior allows an implementation to select between multiple behaviors explicitly permitted by this specification.

For every implementation-defined behavior:

- This specification must document the permitted choices and degrees of freedom.
- Each implementation must explicitly document the choice it makes in its implementation documentation.

An implementation must not introduce additional choices beyond those permitted by the specification.

#### 1.3 Undefined Behavior

Undefined behavior (UB) occurs when a program performs an operation whose required preconditions are not satisfied and for which the language provides no guarantees.

When undefined behavior occurs, the implementation is not required to preserve any particular observable behavior.

Undefined behavior is reserved for cases where providing meaningful guarantees would impose unreasonable costs, restrict necessary programming flexibility, or conflict with lower-level platform guarantees.

Examples include invalid memory accesses, accesses through incompatible pointer types, and unsynchronized concurrent memory accesses.

### 2. Arithmetic Operations

Arithmetic operations are designed to behave as closely as possible to the corresponding native machine instructions of the target architecture.

Their guarantees follow those of the corresponding native instructions, as documented by the target platform.

This specification does not reproduce architecture-specific instruction guarantees. Implementations and developers must refer to the relevant platform documentation when those guarantees are needed.

#### 2.1 Integer Arithmetic

Integer arithmetic operators follow the behavior and guarantees of their corresponding native machine instructions.

For example, integer addition follows the guarantees of the corresponding native addition instruction, such as the `ADD` instruction on x86 architectures.

The language does not introduce additional overflow checks or impose arithmetic behavior that would differ from the corresponding native instruction.

Operations requiring more specific behavior must be provided through dedicated standard library functions.

#### 2.2 Integer Division

Integer division follows the behavior and guarantees of the corresponding native division instruction.

This includes exceptional cases such as division by zero and signed division overflow.

The language does not introduce additional runtime checks for these cases.

Alternative division operations with explicitly defined behavior may be provided by the standard library.

#### 2.3 Shift Operations

Shift operators are available only for unsigned integer types.

Their behavior follows the corresponding native machine instructions and their documented guarantees.

Shift operations on signed integer types are not permitted.

Alternative shift operations with explicitly defined semantics may be provided by the standard library.

#### 2.4 Floating-Point Arithmetic

Floating-point operators follow the behavior and guarantees of the corresponding native floating-point instructions.

This includes:

- Rounding behavior.
- Infinity and NaN propagation.
- Floating-point exceptions.
- Other observable properties defined by the corresponding native instructions.

The language does not impose additional checks or substitute different arithmetic semantics.

Operations requiring more specific numerical guarantees must be provided through dedicated standard library functions.

#### 2.5 Numeric Conversions

Implicit integer-to-floating-point conversions are permitted only when they preserve the exact mathematical value.

Floating-point-to-integer conversions require dedicated standard library functions that explicitly define their rounding and exceptional-case behavior.

Other numeric conversion restrictions and guarantees are defined by the numeric conversion rules of this specification.

### 3. Initialization and Object Lifetime

Gaïa does not permit declarations that leave variables uninitialized.

The compiler must guarantee that an object is initialized before it can be read, according to the initialization rules defined by the language.

Object construction, destruction, and lifetime guarantees are defined by the corresponding constructor, destructor, and exception rules.

This section does not redefine those mechanisms. Their existing guarantees apply equally when determining whether an object may be accessed.

Accessing an object outside its valid lifetime is undefined behavior unless explicitly permitted by the applicable lifetime rules.

### 4. Memory Representation and Alignment

#### 4.1 Primitive Types

Primitive types have a precisely defined memory representation.

The representation of pointer and reference types corresponds to the machine pointer representation of the target architecture.

The language does not guarantee that pointers or references can contain additional metadata, such as bounds or provenance information.

The `Size` type must be capable of representing the size of the largest possible addressable memory region on the target architecture.

The `Byte` type represents the smallest addressable unit of memory on the target architecture.

#### 4.2 Composite Types

The memory layout of composite types preserves the order and representation requirements specified by the programmer.

The compiler must not arbitrarily reorder fields or otherwise alter the specified layout.

Padding bytes may be inserted when required to satisfy the alignment requirements of the target architecture.

Padding may occur between fields or at the end of a type.

Consequently, the final size and alignment of a composite type may depend on the target architecture, but must not vary arbitrarily between implementations targeting the same architecture and layout requirements.

#### 4.3 Union Layout

All members of a union begin at the same memory address.

The alignment of a union must satisfy the strictest alignment requirement of all its members.

Its size must be sufficient to contain its largest member, including any padding required by that member's layout.

Additional trailing padding may be inserted to satisfy the union's alignment requirements.

#### 4.4 Array Layout

Array elements are stored contiguously.

No additional padding is inserted between consecutive elements. The size of an element type already accounts for any trailing padding required to satisfy its alignment.

The address of each element is determined by the size of the element type and its index.

The total size of an array is therefore equal to its element count multiplied by the size of its element type.

#### 4.5 Alignment Requirements

All memory accesses must satisfy the alignment requirements of the accessed type.

Accessing an object through an insufficiently aligned address results in undefined behavior, including on architectures that natively support unaligned memory accesses.

Operations requiring unaligned memory access must use dedicated standard library functions.

### 5. Pointer Operations and Memory Access

#### 5.1 Pointer Arithmetic

Pointer arithmetic is restricted to array pointer types.

Pointer arithmetic and pointer conversions must not be combined to bypass the restrictions imposed by either operation.

Conversions between pointers and integer types are not provided as native language conversions. Such operations must use dedicated standard library functions.

The behavior of pointer arithmetic must respect the native pointer and memory access rules of the target architecture.

Invalid memory accesses result in undefined behavior.

#### 5.2 Bounds-Checked Sequences

Fixed-size arrays (`[N]T`) and slices (`[]T`) contain sufficient size information to perform bounds checking.

All operations on these types that depend on sequence bounds must verify that the requested operation remains within the valid range.

This includes, but is not limited to:

- Element access.
- Range access and slicing.
- Other operations that select or access a portion of the sequence.

When an operation exceeds the valid bounds, it must report a runtime exception.

Each bounds-checked operation has a corresponding unchecked alternative.

Unchecked operations omit bounds validation. Using them outside the valid range follows the native memory access rules of the target architecture and may result in undefined behavior.

#### 5.3 Array Pointers

Array pointers (`[&]T` and `[*]T`) do not contain the size of the sequence they reference.

Consequently, operations on array pointers do not perform bounds checking.

The validity of such operations is the responsibility of the programmer. Invalid memory accesses result in undefined behavior.

#### 5.4 Pointer Conversions

Conversions between pointers to unrelated types are not permitted.

Pointer conversions between different object types are allowed only when the types are related through class inheritance and the applicable pointer conversion rules permit the operation.

Conversions based solely on a shared or compatible memory representation must use dedicated standard library functions.

The existing inheritance conversion rules, including pointer adjustments and runtime checks for downcasts, remain applicable.

#### 5.5 Pointer Aliasing

Gaïa follows the strict aliasing principles of C++.

An object may only be accessed through pointer or reference types permitted by the language's type accessibility rules.

Accessing an object through an incompatible type results in undefined behavior.

The `Byte` type is an exception to these restrictions.

A `Byte` pointer or reference may be used to read or modify the memory representation of any object, without violating the aliasing rules.

The code unit types `CodeUnit8`, `CodeUnit16`, and `CodeUnit32` do not benefit from this exception.

### 6. Concurrent Memory Access

#### 6.1 Data Races

Data races result in undefined behavior.

Concurrent access to shared memory must therefore be properly synchronized whenever at least one access modifies the accessed memory.

#### 6.2 Default Execution Model

By default, Gaïa programs are optimized under the assumption of synchronous execution.

The compiler may therefore perform optimizations that rely on the absence of unsynchronized concurrent memory accesses.

#### 6.3 Synchronization and Atomic Operations

The standard library provides the mechanisms required to establish synchronization guarantees and perform atomic operations.

The initial language specification does not provide dedicated built-in atomic operations or synchronization primitives.

Programs requiring asynchronous or concurrent execution must use the corresponding standard library facilities.

#### 6.4 Future Compiler Annotations

Gaïa may introduce additional annotations that communicate specific memory or execution guarantees to the compiler.

Such annotations may include mechanisms comparable to `@volatile`.

Their semantics and optimization constraints will be defined when these mechanisms are introduced.

## Project Configuration

Gaïa projects are configured through a `gaia.toml` file located at the project root.

This file defines project-wide settings, build configurations, targets, and their dependencies. It is also used to configure the native compilation environment and other project-specific options.

The configuration system follows a convention-over-configuration approach: common project layouts and settings are inferred automatically, while explicit configuration allows projects to override these conventions when necessary.

### 1. Project Configuration

The `[project]` section defines settings shared by all targets and configurations.

```toml
[project]
```

#### 1.1 Target Platform

The target platform, architecture, and toolchain are inferred from the current compilation environment by default.

A project may explicitly override the automatically determined target environment. This configuration applies globally to the project, ensuring that all its targets are built for a coherent platform.

#### 1.2 Build and Installation Directories

The project defines two directory prefixes:

- `build-prefix` specifies where generated build artifacts are stored. Its default value is `build`.
- `install-prefix` specifies where installed artifacts are placed. Its default value is `install`.

Both properties accept relative and absolute paths.

Relative paths are resolved relative to the directory containing `gaia.toml`. Absolute paths are used as specified.

These properties can be overridden by individual build configurations and by command-line options.

### 2. Build Configurations

Build configurations define sets of compilation, linking, and dependency-resolution settings.

The following configurations are predefined:

- `debug`
- `release`

Additional configurations can be declared through `[configs.<name>]` sections.

The active configuration is selected through the `--config` command-line option. When no configuration is explicitly selected, `debug` is used.

#### 2.1 Configuration Inheritance

A configuration may inherit from one other configuration using the `inherits` property.

```toml
[configs.my-debug]
inherits = "debug"
```

Inheritance is transitive, allowing configuration chains.

A configuration may override any inherited property. Properties not explicitly overridden retain their inherited values.

Unknown parent configurations and inheritance cycles are configuration errors.

The `[project]` section defines settings common to all configurations. Configuration-specific values override the corresponding project-level values.

#### 2.2 Configuration Scope

Configurations control structured compiler and linker options, dependency resolution, and the native compilation environment.

They do not provide general-purpose user-defined variables or arbitrary custom build commands.

Compiler and linker settings are expressed through structured properties rather than unrestricted raw command-line flags.

#### 2.3 Compiler Options

The following compiler options are configurable.

##### `optimization_level`

Specifies the optimization strategy used by the compiler.

The standard values are:

- `none`
- `less`
- `default`
- `aggressive`
- `size`
- `size_aggressive`

The implementation maps these abstract levels to its underlying compiler and optimization strategy.

The `size` and `size_aggressive` levels prioritize reducing generated code size rather than merely disabling selected optimizations.

Implementations may provide additional optimization levels.

Defaults:

| Configuration | Default |
|---|---|
| `debug` | `none` |
| `release` | `default` |

##### `debug_info`

A Boolean property controlling whether debugging information is generated.

Debugging information may include source locations, variable information, and type information.

Defaults:

| Configuration | Default |
|---|---|
| `debug` | `true` |
| `release` | `false` |

The format of the generated debugging information is implementation-defined.

##### `link_time_optimization`

A Boolean property controlling link-time optimization.

When enabled, the implementation attempts to optimize the final program across compilation units and dependencies wherever the available intermediate representations permit it.

Precompiled native binaries generally cannot participate in Gaïa link-time optimization.

Defaults:

| Configuration | Default |
|---|---|
| `debug` | `false` |
| `release` | `true` |

##### `assertions`

A Boolean property controlling the compilation of assertion checks.

Its value is exposed to compile-time macros so that assertion macros can generate or omit checks according to the active compilation configuration.

The value is fixed when each module is compiled. Changing this property in a consuming project does not retroactively alter assertions in already compiled dependencies.

Defaults:

| Configuration | Default |
|---|---|
| `debug` | `true` |
| `release` | `false` |

##### `strip_symbols`

A Boolean property controlling whether debugging and symbol information is removed from installed artifacts.

This operation applies during installation and does not require the corresponding information to be omitted from compilation artifacts.

This allows, where supported by the platform, installing stripped binaries while retaining separate debugging information.

Defaults:

| Configuration | Default |
|---|---|
| `debug` | `false` |
| `release` | `true` |

Language-defined checks, including overflow and runtime safety checks, are not controlled by additional generic configuration switches. Their behavior is determined by the corresponding language mechanisms.

#### 2.4 Warning Configuration

Warnings can be configured at the project level and overridden by individual modules.

All warnings are enabled by default at the `warning` level.

Each warning can be assigned one of the following levels:

- `error`
- `warning`
- `ignore`

Warning selectors support:

- Exact warning identifiers.
- Hierarchical prefixes using a trailing wildcard, such as `numeric-*`.
- The global wildcard `*`.

Rules are evaluated in declaration order, with the last matching rule taking precedence.

More specific configuration levels override inherited rules. Module-specific settings therefore take precedence over project-wide settings.

These settings affect warnings only. Errors cannot be downgraded or ignored through project configuration, and notes and remarks cannot be promoted.

Source-level warning annotations retain their independently defined semantics and may locally override the effective warning configuration.

The exact TOML representation of warning rules is specified alongside the warning configuration syntax.

#### 2.5 Native Compilation Environment

Gaïa uses Clang to compile native C and C++ code.

By default, Gaïa attempts to reproduce its own compilation environment when invoking Clang. This includes the target platform, architecture, toolchain, and other relevant compilation defaults.

The project may provide additional parameters or override automatically determined values through `clang-tweaks`.

These settings are passed to Clang rather than interpreted through a separate Gaïa-specific native configuration system.

Configurable parameters include:

- Header and module search paths.
- Compiler flags and other compilation options.
- Preprocessor macro definitions and undefinitions.
- C and C++ language standards.
- Platform- and toolchain-specific options.

Native compilation settings can be defined globally in the project configuration and overridden by individual build configurations.

The exact TOML structure used to express `clang-tweaks` is specified separately.

### 3. Targets

A target is a buildable unit identified by a target name.

Targets are the units selected by build, configuration, installation, and cleaning operations of the `gaia` command.

The target name is independent of the logical module name declared in Gaïa source code.

#### 3.1 Target Discovery

By convention, targets are located under the project's `src/` directory.

A conventional target named `my-target` has the following entry-point path:

```text
src/my-target/main.gaia
```

Targets following this convention are discovered automatically and do not require explicit entries in `gaia.toml`.

A target can also be explicitly declared through a `[targets.<name>]` section. Such a declaration allows additional configuration and can be used to declare targets outside the conventional source directory.

The target name defaults to the name of its directory when discovered through the conventional layout.

#### 3.2 Target Entry Point

Each target has one entry-point source file, which defaults to `main.gaia`.

The entry-point file determines the nature of the target.

A library target declares exactly one module:

```gaia
module MyLibrary {
    // ...
}
```

An executable target declares exactly one `main` function:

```gaia
fn main() {
    // ...
}
```

The entry point must contain either one module declaration or one `main` function, but not both.

A missing entry point declaration, multiple module declarations, or multiple `main` declarations is an error.

Other source files belonging to the target are handled through Gaïa's standard fragment and import mechanisms. The compiler does not need to scan source directories to discover those files.

#### 3.3 Target Properties

A target can be configured through `[targets.<name>]`.

The following properties are defined:

##### `path`

Overrides the complete path to the target's entry-point source file.

The path is relative to the directory containing `gaia.toml`, unless it is absolute.

For example:

```toml
[targets.my-funky-module]
path = "extra-src/funky-module/starts-here.gaia"
```

The target name and its source entry point are therefore independent.

##### `dependencies`

Declares the direct Gaïa module dependencies required by the target.

Dependencies are represented as an array of strings or inline tables.

A simple dependency is expressed as a string:

```toml
[targets.my-app]
dependencies = [
    "foo:1.5.2",
    "bar:^2.0.0"
]
```

An inline table is used when additional dependency settings are required:

```toml
[targets.my-app]
dependencies = [
    "foo:1.5.2",
    { name = "bar", version = "^2.0.0", link = "dynamic" }
]
```

Only direct dependencies need to be declared. Transitive dependencies are reconstructed from the dependency metadata embedded in generated modules.

Each dependency may specify a version constraint using the following syntax:

| Constraint | Meaning |
|---|---|
| `:1.2.3` | Exact version |
| `:^1.0.0` | Any compatible version within the same major version |
| `:~1.2.0` | Any compatible version within the same minor version |
| `:latest` | Latest available version |

##### Dependency Linking Mode

The optional `link` property specifies the requested linking mode for a dependency.

Supported values are:

- `follow`
- `static`
- `dynamic`

The default is `follow`.

`follow` uses the linking preference declared by the dependency itself.

`static` and `dynamic` explicitly request the corresponding linking mode. Such a request is valid only if the dependency supports that mode. Otherwise, configuration or linking fails.

A module declares its preferred linking mode and the modes it supports. Its preference is a recommendation, while its supported modes define compatibility constraints.

The default linking preference is `static`.

The Gaïa runtime and standard library also use static linking by default, unless a compatible explicit request specifies otherwise.

The linking mode is independent of the dependency's other dependency flags.

##### Native Libraries

Native library dependencies are declared separately using the `native-libraries` property.

```toml
[targets.my-app]
native-libraries = ["ssl", "crypto"]
```

Native imports do not necessarily reveal which native libraries provide the imported definitions. Native library dependencies must therefore be declared explicitly.

The property contains logical library names. The implementation adapts these names to the conventions of the target platform and toolchain, including library prefixes and file extensions.

Native library versions and dependency resolution are handled by the native build environment and linker rather than by Gaïa's dependency manager.

Native library search paths and other native linking parameters are configured through `clang-tweaks`.

The platform's native standard library is linked automatically according to the selected toolchain.

#### 3.4 Dependency Metadata

Dependency flags are determined by the compiler according to actual module usage. They are not manually configurable in `gaia.toml`.

The compiler records the following flags in generated module metadata:

- `buildtime`
- `runtime`
- `interface`

These flags are independent and may apply simultaneously to the same dependency.

The metadata records the dependencies of each generated module, allowing the dependency graph to be reconstructed recursively.

A dependency marked `interface` is propagated transitively: its own interface dependencies are also exposed through the interface dependency graph.

Dependencies marked only `buildtime` and/or `runtime` are not propagated through this mechanism.

This propagation concerns dependency graph resolution and is independent of source-level `export import`, which controls declaration visibility.

Each module is compiled in its own dependency context. Interface dependencies are resolved using the supplier module's compilation context and its generated interface artifacts; they are not rebuilt in the consuming module's context.

Logical module names must be unique within a dependency graph. Different versions of a logical module can coexist when they remain isolated in separate dependency contexts.

If multiple versions of the same logical module become exposed in a single interface dependency graph, the resulting ambiguity is a configuration error.

A module may intentionally use a different logical module name to allow multiple versions to be exposed in the same graph.

### 4. Dependency Lock File

The project uses a `gaia.lock` file to record resolved dependency versions and the information required to retrieve them.

The lock file is generated automatically during the first dependency resolution.

It is the reference used to retrieve dependencies in subsequent operations.

When a dependency is added, removed, or its version constraint no longer matches the locked version, the lock file is updated accordingly.

If the locked version still satisfies the declared constraint, it is retained even when a newer version is available.

Committing `gaia.lock` to version control is recommended to ensure reproducible dependency resolution across environments. However, doing so is a project convention rather than a requirement.

Multiple versions of the same logical module may coexist in one project when their dependency contexts remain isolated.

The implementation may share cached dependencies and compilation artifacts between projects when their complete inputs are identical. Cache identity must account for all relevant inputs, including module version, compiler version, target platform, compilation options, and effective dependencies.

### 5. Command-Line Interface

The `gaia` command acts as the project's build driver and dependency manager. It handles dependency retrieval, target configuration, compilation, linking, installation, and build artifact maintenance.

When invoked without arguments, `gaia` operates on the project in the current directory and builds the entire project.

A project path can be specified explicitly:

```sh
gaia ./project
```

When a project path is specified, all relative paths in its configuration are resolved relative to that project's root directory.

#### 5.1 Operations

Operations are specified through command-line options. Each operation represents an objective rather than an isolated build step.

The command automatically performs all prerequisite operations required to achieve the requested objective, including the corresponding operations on dependencies.

The following operations are defined:

- `--fetch`: resolves and retrieves dependencies without configuring or compiling targets.
- `--configure`: ensures that the selected targets and their dependencies are configured. This may require retrieving dependencies first.
- `--build`: ensures that the selected targets and their dependencies are built, including dependency resolution, retrieval, configuration, compilation, and linking.
- `--install`: ensures that the selected targets and their dependencies are built as necessary, then installs them.
- `--clean`: removes generated artifacts associated with the selected targets.

An operation can be followed by one or more target names. If no target is specified for an operation, it applies to the entire project.

Multiple operations can be combined in a single invocation. Each operation can independently specify its targets.

For example:

```sh
gaia --configure libX
gaia --build toolX
gaia --build
gaia --build libX libY
gaia --fetch libX --build libY
gaia ./project --build myTool
gaia --clean
gaia --clean libX libY
gaia --clean --build toolX
```

When the same target is selected by multiple operations, the command may combine redundant objectives. For example, fetching and building the same target only requires the build operation, since building already includes dependency retrieval.

#### 5.2 Build Configurations

The active build configuration is selected using `--config <name>`.

When omitted, the `debug` configuration is selected.

For example:

```sh
gaia --config release --build
```

#### 5.3 Build and Installation Directories

The command-line options `--build-prefix` and `--install-prefix` override the corresponding directory prefixes defined in the project configuration.

Both options accept relative or absolute paths. Relative paths are resolved relative to the project root.

Command-line values take precedence over values defined in the active configuration or the project-wide configuration.

For example:

```sh
gaia --build --build-prefix /tmp/gaia-build
gaia --install --install-prefix /opt/my-project
```

These overrides apply only to the current invocation and do not modify the project configuration.

#### 5.4 Incremental Builds and Caching

The build system performs incremental operations by default.

It avoids unnecessary work whenever the relevant inputs and outputs remain unchanged. In particular, it avoids:

- Retrieving dependencies that are already available at the required version.
- Reconfiguring targets whose effective configuration has not changed.
- Recompiling unchanged source fragments.
- Relinking or regenerating binaries when their inputs have not changed.

Compilation and dependency caches may be shared between projects when the corresponding artifacts are interchangeable.

Cache identity must account for all relevant inputs, including module versions, compiler versions, target platform, compilation options, and effective dependencies.

#### 5.5 Cleaning

The `--clean` operation removes generated project artifacts associated with the selected targets.

It can be combined with other operations, allowing a target to be cleaned and rebuilt in the same invocation.

Cleaning project artifacts does not imply removing shared dependency or compilation caches. Cache maintenance is a separate operation.

#### 5.6 Additional Options

The command-line interface may provide additional options for build customization and maintenance, including:

- Forcing configuration, compilation, or linking even when the build system considers the corresponding outputs up to date.
- Updating locked dependency versions.
- Checking dependency and cache integrity.
- Inspecting planned operations without executing them.
- Displaying detailed build information.
- Selecting a target platform, architecture, or toolchain when supported.

The exact names and semantics of these additional options are specified separately.
