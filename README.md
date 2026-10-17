# Bolt Language

A language made to be fast and simple.

---

## Building with Python

1. Set up an `.env` file

```env
CPP_COMPILER="your-cpp-compiler"
```

2. Run Python to compile the frontend

> There is no backend yet, so you can't compile backend

```bash
python build/build.py frontend
```

## Expected Syxtax

> Syntax may vary, as Bolt is in very development stage

```
fn add(a: i32, b: i32) -> i32 {
    ret a+b;
}

var n1: int = 123; // int is an alias for i32
var n2: int = 494;

print(add(n1, n2)); // This print method is a placeholder for future print methods

```