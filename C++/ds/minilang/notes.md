# MiniLang Compiler Project

## Overview
MiniLang is a tiny language supporting:
- print statements
- integer variables
- addition of integers
- standalone executable compilation

This project implements:
- Lexer → tokenizes source
- Parser → builds AST
- Bytecode generator → converts AST to instructions
- CodeGen → converts bytecode into C++ source code
- CLI (minicomp) → generates executable from .minilang source

---

## File hierarchy

src/
    Lexer.h/cpp       # tokenizer
    AST.h             # expression/statement nodes
    Parser.h/cpp      # parser
    Bytecode.h/cpp    # bytecode generator
    CodeGen.h/cpp     # generate C++ code from bytecode
    main.cpp          # minicomp CLI entry point

examples/
    hello.minilang    # sample program

build/               # compiled executables

notes.md             # this file

---

## How to run

1. Compile the compiler itself:
```
g++ src/*.cpp -o minicomp
```

2. Compile a MiniLang program:
```
./minicomp examples/hello.minilang
```
- This generates executable `hello` in current directory.

3. Run the generated program:
```
./hello
```
```
Hello, MiniLang!
15
```
4. Add more programs in `examples/` and compile similarly.

---

## Notes

- The compiler internally generates C++ code from bytecode and compiles with g++.
- The VM instructions are embedded in the generated C++ file.
- Supports integers, strings, print, let, and addition.
- Can be extended for loops, if statements, and functions.

✅ Summary
- minicomp hello.minilang → generates executable hello
- User never sees C++ code (transparent)
- Standalone executable runs like a real compiled language
- Fully modular: Lexer → Parser → Bytecode → CodeGen → CLI