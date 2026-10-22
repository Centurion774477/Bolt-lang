![Bolt Logo](assets/logo.png)

# Bolt Language

Bolt is a fast and simple language.

---

## Building with Python

1. Set up an `.env` file

```env
CPP_COMPILER="your-cpp-compiler"
C_COMPILER="c_compiler"
```

2. Run Python to compile

> There is no backend to compile yet

```bash
python build/build.py frontend
python build/build.py vm
```

Note: if your machine is running macOS or GNU/Linux then you may be using `python3` instead.
If you're unsure, you can check with `which python` or `which python3`

## Expected Syntax

> Syntax may vary and is subject to change as Bolt is in an early stage of development

```
// function definition
fn add(a: i32, b: i32) -> i32 {
    ret a+b;
}

// variable definition
var n1: int = 123; // int is an alias for i32
var n2: int = 494;

// function call
print(add(n1, n2));

```
Note that print is just a placeholder name; it is subject to change.
