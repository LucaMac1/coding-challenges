# 📐 Coding Challenges

## 🧮 TASK 1 – THE CALCULATOR (C++)

Your team is developing a calculator program that takes algebraic expressions as input and computes the result.  

For example:

### ✅ Examples

```txt
Input: 2 * (3 + 4)
Output: 14

Input: 13.75 + 22 * 15
Output: 343.75
```

---

## 📌 Phase 1 Requirements

The program shall support:

1. The operators **plus (`+`)** and **multiplication (`*`)**
2. Integer and floating-point constants
3. **Operator precedence**: multiplication has higher precedence than addition
4. **Parentheses** to group expressions

> 🚫 **Note**: Parsing the text input is *not* required in the minimum solution. Assume another module handles parsing.

---

## 🧠 Task

You are tasked with designing:

- A **data structure** to represent an algebraic expression  
- An **evaluate function** to calculate the result  

### 💡 Hints

- The structure should support **arbitrarily long** expressions  
- **Memory safety** is important — avoid memory leaks

---

## ✅ Minimum Solution – AST-Based Evaluation

This project implements a basic **algebraic expression calculator** in C++ using an **Abstract Syntax Tree (AST)**.  

It evaluates mathematical expressions based on standard precedence rules and grouping via parentheses.

---

### ✨ Features

- ✅ Supports **addition (`+`)** and **multiplication (`*`)**
- ✅ Correct **operator precedence**
- ✅ Handles **parentheses**
- ✅ Works with **integers** and **floating-point** numbers
- ✅ Memory-safe using `std::unique_ptr`
- ✅ Clean, extensible design

---

### 🧱 Design – Abstract Syntax Tree (AST)

The calculator uses an **AST**, where:

- Leaf nodes = numeric constants (`Constant`)
- Internal nodes = binary operations like `Add`, `Multiply`

#### 📊 Example AST for `2 * (3 + 4)`:

```
     *
    / \
   2   +
      / \
     3   4
```

### 🧩 Class Hierarchy

- `Expression`: Abstract base class with virtual `evaluate()`  
- `Constant`: Leaf node holding a numeric value  
- `Add`, `Multiply`: Binary operator nodes with left/right subtrees  

Each node evaluates itself **recursively**.

---

### 🧪 How to Build & Run

```bash
g++ -std=c++17 calculator.cpp -o calculator
./calculator
```

#### 🖥️ Expected Output:

```
2 * (3 + 4) = 14
13.75 + 22 * 15 = 343.75
```

---

## 🛠️ Bonus Solution – With Parser (Optional)

In addition to the AST-based solution, this project also includes an **extended version** that implements a **parser** for algebraic expressions.

### 🎁 Extra Features

- 🧮 Parses string input like `"2 * (3 + 4)"` into an AST
- ➕ Adds support for **subtraction (`-`)** and **division (`/`)**
- 🔄 Optional `optimize()` function to simplify constant subtrees
- 🔍 `getType()` to infer result type (int or float)

---

### 🔧 Optional Extensions

If time permits, consider adding:

- [ ] Unary operators (`-a`)
- [ ] An `optimize()` function to fold constant subtrees
- [ ] A `getType()` function to infer result type (int or float)
- [ ] Support for additional operators (e.g. `-`, `/`)
- [ ] A full expression parser for user input

---

### 🧼 Notes

- Parsing is separated for modularity.
- `std::unique_ptr` is used throughout to ensure **automatic memory cleanup**.
- The AST-based approach allows for **easy extension**, **transformation**, and **code clarity**.

---

## 📁 Project Structure

```txt
.
├── calculator.cpp         # Main calculator implementation using AST
├── parser_calculator.cpp  # Extended version with expression parser (optional)
└── README.md              # This file
```

---

## 👨‍💻 Author

This calculator challenge was implemented as part of a coding exercise to demonstrate clean C++ design, memory safety, and recursive data structures.

---