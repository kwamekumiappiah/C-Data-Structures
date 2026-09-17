# 🔗 Heterogeneous Linked List in C

> A dynamically allocated, heterogeneous singly linked list implemented in **C from scratch**.

![Language](https://img.shields.io/badge/language-C-A8B9CC?logo=c\&logoColor=white)
![Compiler](https://img.shields.io/badge/compiler-GCC-4EAA25?logo=gnu\&logoColor=white)
![Git](https://img.shields.io/badge/version%20control-Git-F05032?logo=git\&logoColor=white)
![Status](https://img.shields.io/badge/status-learning%20project-blue)

---

## 🧠 About The Project

This project is my **first substantial C project**, developed as part of my ongoing journey into **systems programming and low-level computing**.

The goal wasn't simply to learn how a linked list works.

Instead, I wanted to take individual C concepts I had been studying and force myself to combine them into a working, reusable project involving:

**pointers + memory + data structures + APIs + testing + project organization**

The repository was intentionally structured like a small standalone C project rather than placing everything into a single source file.

That means the project also became an exercise in:

* 🧱 C structures and enumerations
* 🧩 unions and tagged data
* 👉 pointers and pointer manipulation
* 💾 dynamic memory allocation
* 🧹 manual memory management
* 🔗 linked-list data structures
* 🛡️ defensive programming and boundary checking
* 📦 header/source separation
* 🔒 opaque data types
* 🔧 API design
* ⚠️ error handling through return values
* 🗂️ modular project organization
* 🧪 writing a separate test suite
* 🌱 Git and GitHub-based development

This project is also part of a much longer learning path toward:

**systems programming → reverse engineering → binary analysis → exploitation → vulnerability research → digital forensics**

---

# 🚀 Features

This implementation supports multiple C data types through a `DataType` discriminator combined with a union-based value representation.

### Supported Types

| Type                 | Supported |
| -------------------- | :-------: |
| `char`               |     ✅     |
| `unsigned char`      |     ✅     |
| `short`              |     ✅     |
| `unsigned short`     |     ✅     |
| `int`                |     ✅     |
| `unsigned int`       |     ✅     |
| `long`               |     ✅     |
| `unsigned long`      |     ✅     |
| `long long`          |     ✅     |
| `unsigned long long` |     ✅     |
| `float`              |     ✅     |
| `double`             |     ✅     |
| `long double`        |     ✅     |
| `void *`             |     ✅     |

Each node stores information about **which type is currently active**, alongside the corresponding value.

---

# 🧬 How The Data Structure Works

At a high level, the project uses a singly linked structure where each node contains:

```text
┌─────────────────────┐
│      DataType       │
├─────────────────────┤
│       union         │
│   ┌─────────────┐   │
│   │ char        │   │
│   │ int         │   │
│   │ float       │   │
│   │ double      │   │
│   │ void *      │   │
│   │ ...         │   │
│   └─────────────┘   │
├─────────────────────┤
│        next         │ ────────────────┐
└─────────────────────┘                 │
                                        ▼
                              ┌─────────────────────┐
                              │      DataType       │
                              ├─────────────────────┤
                              │       union         │
                              ├─────────────────────┤
                              │        next         │
                              └─────────────────────┘
```

The list itself maintains:

```text
┌──────────────────────┐
│        length        │
├──────────────────────┤
│         head         │ ───────────────► first node
└──────────────────────┘
```

The result is a dynamically allocated, heterogeneous singly linked list.

---

# 🛠️ API

## 📋 List Lifecycle

```c
linkedList *create_linked_list(void);
int free_linked_list(linkedList *linked_list);
```

Creates and destroys the linked-list container and its dynamically allocated nodes.

---

## ➕ Adding Elements

```c
int add_node(
    linkedList *linked_list,
    DataType type,
    void *data
);

int insert_value(
    linkedList *linked_list,
    size_t index,
    DataType type,
    void *data
);

int prepend_node(
    linkedList *linked_list,
    DataType type,
    void *data
);
```

Elements can be:

* appended to the end
* inserted at a specific index
* prepended to the beginning

---

## ➖ Removing Elements

```c
int delete_node(
    linkedList *linked_list,
    size_t index
);

int delete_node_value(
    linkedList *linked_list,
    DataType type,
    void *data
);
```

Nodes can be removed either by:

* 📍 index
* 🔍 matching both type and value

---

## 🔎 Searching

```c
ListElement search_by_index(
    linkedList *linked_list,
    size_t index
);

ListElement search_by_value(
    linkedList *linked_list,
    DataType type,
    void *data
);
```

Search operations return both:

* the stored `DataType`
* a pointer to the corresponding value

This allows the caller to determine how the returned data should be interpreted.

---

## 🧰 Utility Operations

```c
int is_empty(
    const linkedList *linked_list
);

size_t get_list_length(
    const linkedList *linked_list
);

linkedList *clone_list(
    linkedList *linked_list
);

int reverse_list(
    linkedList *linked_list
);
```

The implementation also provides:

* ✅ empty-list checks
* 📏 length retrieval
* 🧬 list cloning
* 🔄 in-place list reversal

---

## 🖨️ Display

```c
void print_linked_list(
    linkedList *linked_list
);
```

The list can be traversed and printed using type-appropriate formatting.

---

# 🔬 Technical Concepts Demonstrated

## 1. 🧱 Structures

The project uses structures to represent both individual nodes and the list container.

A node conceptually contains:

```text
type
value
next
```

while the list container maintains:

```text
length
head
```

This provided practical experience designing relationships between dynamically allocated structures.

---

## 2. 🔢 Enumerations

`DataType` acts as a discriminator describing which value is currently active inside the node's union.

```c
typedef enum {
    TYPE_INVALID = -1,
    TYPE_CHAR,
    TYPE_UNSIGNED_CHAR,
    TYPE_SHORT,
    TYPE_UNSIGNED_SHORT,
    TYPE_INT,
    TYPE_UNSIGNED_INT,
    TYPE_LONG,
    TYPE_UNSIGNED_LONG,
    TYPE_LONG_LONG,
    TYPE_UNSIGNED_LONG_LONG,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_LONG_DOUBLE,
    TYPE_VOID_POINTER
} DataType;
```

This was an important exercise in representing type information explicitly at runtime.

---

## 3. 🧩 Unions

The node uses a union so that different C data types can share the same storage area.

Conceptually:

```text
          ┌───────────────────┐
          │     DataType      │
          ├───────────────────┤
          │                   │
          │       union       │
          │                   │
          ├───────────────────┤
          │       next        │
          └───────────────────┘
```

This provided practical experience with one of C's lower-level mechanisms for representing different types within the same object.

The combination of:

```text
DataType + union
```

creates a simple form of **tagged data**.

---

## 4. 👉 Pointers

Pointers are central to essentially the entire project.

They are used for:

* dynamically allocated nodes
* linked-list traversal
* modifying links between nodes
* returning stored values
* handling `void *`
* manipulating the list head
* cloning the list
* reversing the structure

For example, `reverse_list()` performs an **in-place reversal** by maintaining three pointers:

```text
prev
current
next
```

Conceptually:

```text
Before:

HEAD
 │
 ▼
[A] ──► [B] ──► [C] ──► NULL


After:

HEAD
 │
 ▼
[C] ──► [B] ──► [A] ──► NULL
```

---

## 5. 💾 Dynamic Memory

Nodes and the list container are dynamically allocated with `malloc()` and released using `free()`.

The implementation explicitly walks through the list when destroying it instead of relying on automatic memory management.

That means the project required reasoning about:

```text
allocation
    ↓
initialization
    ↓
ownership
    ↓
object lifetime
    ↓
deallocation
```

It also required thinking about problems such as:

* memory leaks
* invalid memory access
* dangling pointers
* incorrect ownership
* object lifetime

---

## 6. 🔒 Opaque Data Types

The public header exposes:

```c
typedef struct linkedList linkedList;
```

while the actual structure definition remains inside the implementation.

This creates a separation between:

```text
PUBLIC INTERFACE
       │
       ▼
┌──────────────────┐
│ linked_list.h    │
└────────┬─────────┘
         │
         ▼
PRIVATE IMPLEMENTATION
┌──────────────────┐
│ linked_list.c    │
└──────────────────┘
```

The goal was to practice designing a small C library without exposing every implementation detail to the caller.

---

## 7. 📦 Header / Source Separation

The public interface and implementation are separated:

```text
include/
└── linked_list.h

src/
└── linked_list.c
```

The header contains:

* public types
* function declarations
* API definitions

The source file contains:

* implementation details
* internal structures
* function implementations

This was intentional practice in **modular C development**.

---

# 🗂️ Repository Structure

```text
.
├── build/
│   ├── program.exe
│   └── test_suite.exe
│
├── include/
│   └── linked_list.h
│
├── src/
│   ├── linked_list.c
│   └── main.c
│
└── tests/
    └── test_linked_list.c
```

### Directory Overview

| Directory  | Purpose                                  |
| ---------- | ---------------------------------------- |
| `include/` | Public header files and API declarations |
| `src/`     | Application and library source code      |
| `tests/`   | Test suite                               |
| `build/`   | Compiled executables                     |

The separation is intended to keep implementation, public interfaces, tests, and build artifacts organized independently.

---

# 🧪 Testing

A separate test program is included in:

```text
tests/test_linked_list.c
```

Testing was treated as a separate part of the project rather than embedding all verification directly into the main program.

The test suite is intended to exercise the public linked-list operations and provide a way to verify behavior independently from the implementation.

The broader goal is to make testing part of the development workflow rather than something added only after the implementation is finished.

---

# 🧠 Design Decisions

## Why a Heterogeneous List?

A conventional linked list could store a single type such as:

```c
int
```

This project intentionally goes further by using:

```text
type discriminator
        +
      union
```

to experiment with representing multiple C types inside the same data structure.

The additional complexity was deliberate.

It created an opportunity to work with:

* unions
* enumerations
* `void *`
* runtime type information
* type-dependent operations

The project isn't trying to claim that this is necessarily the simplest or most idiomatic generic container design.

The complexity exists because it makes the underlying C mechanics much more visible.

---

# ⚠️ Error Handling

The public functions generally use return values to communicate success or failure.

The current convention is primarily:

```text
0 → success
1 → failure
```

Search functions instead return a `ListElement` structure containing:

```text
data pointer
DataType
```

`TYPE_INVALID` is used as a sentinel for unsuccessful searches.

This project has helped reinforce an important part of C API design:

> In C, failure states, ownership, invalid input, and object lifetime often have to be made explicit by the programmer.

---

# 💡 What I Learned

This project represented an important transition from writing isolated C exercises to designing a small program as a complete software project.

## 💾 C is fundamentally about memory

Working with a linked list made pointers and memory far more concrete than they were when learning C syntax in isolation.

I had to reason about:

* what each pointer represents
* where objects live in memory
* how nodes reference one another
* what happens when an object is freed

---

## 🧱 Abstraction Still Matters in C

C is often described as a low-level language, but writing maintainable C still requires good organization.

Separating the interface from the implementation helped me understand why concepts such as:

* headers
* opaque structures
* APIs
* encapsulation

exist even in a language as low-level as C.

---

## 🧩 Generic Programming in C Has Trade-offs

Using:

```text
void *
+
union
+
explicit type discriminator
```

provides flexibility.

But that flexibility also means the programmer becomes responsible for maintaining type correctness.

This project made those trade-offs much more obvious.

---

## 🔗 Data Structures Are About More Than Syntax

Implementing:

* insertion
* deletion
* searching
* traversal
* reversal
* cloning

required understanding how the underlying memory structure changes.

I couldn't simply rely on a built-in container.

I had to reason about the actual relationships between objects in memory.

---

## 🧪 Testing Matters

Writing a separate test program changed how I approached the implementation.

Instead of asking:

> "Does this work?"

I started thinking about:

> "What happens at the boundaries?"

That means considering:

* empty lists
* invalid indexes
* invalid values
* deletion cases
* insertion edge cases
* failure paths

rather than only testing the happy path.

---

## 🌱 Git Is Part of Development

This project was also used to begin learning how to work with:

* Git
* commits
* repository structure
* GitHub
* source control
* public project documentation

The goal wasn't just to learn how to write code.

It was to start learning how to **build, organize, document, test, and present** a software project.

---

# 🚧 Current Limitations

This is an early project and intentionally reflects my current stage of learning C.

Areas I plan to improve include:

* stronger input validation
* more consistent error reporting
* more comprehensive automated tests
* deeper handling of ownership semantics
* clearer semantics for `void *` values
* additional memory-safety testing
* more aggressive compiler warnings
* sanitizer usage
* build-system improvements
* improved documentation
* additional data structures

These limitations are part of the learning process rather than something I want to hide.

The repository is meant to show progression over time.

---

# 🗺️ Development Roadmap

The next steps are focused on improving my understanding rather than simply adding more features.

## 🔹 Near Term

* [ ] Improve the test suite
* [ ] Test edge cases and invalid inputs
* [ ] Use compiler warnings more aggressively
* [ ] Learn and use AddressSanitizer
* [ ] Learn and use UndefinedBehaviorSanitizer
* [ ] Review memory ownership and object lifetime
* [ ] Refactor parts of the API after gaining more C experience

---

## 🔹 Data Structures

After becoming more comfortable with this implementation, I plan to build additional data structures from scratch:

```text
Dynamic Arrays
      ↓
   Stacks
      ↓
   Queues
      ↓
 Hash Tables
      ↓
    Trees
      ↓
    Heaps
```

The point is not just to collect implementations.

It's to understand how these structures work internally and what trade-offs they introduce.

---

# 🧭 Long-Term Learning Direction

This project is one step in a much broader path toward understanding computers at a lower level.

```text
             ┌──────────┐
             │    C     │
             └────┬─────┘
                  │
                  ▼
      ┌──────────────────────┐
      │ Memory & Architecture│
      └──────────┬───────────┘
                 │
                 ▼
      ┌──────────────────────┐
      │ Operating Systems    │
      └──────────┬───────────┘
                 │
                 ▼
          ┌────────────┐
          │  Assembly  │
          └─────┬──────┘
                │
                ▼
          ┌────────────┐
          │ Debugging  │
          └─────┬──────┘
                │
                ▼
        ┌─────────────────┐
        │ Binary Formats  │
        └────────┬────────┘
                 │
                 ▼
       ┌────────────────────┐
       │ Reverse Engineering│
       └─────────┬──────────┘
                 │
                 ▼
         ┌────────────────┐
         │ Binary Analysis│
         └───────┬────────┘
                 │
                 ▼
       ┌─────────────────────┐
       │ Exploitation / VR   │
       └──────────┬──────────┘
                  │
                  ▼
       ┌─────────────────────┐
       │ Digital Forensics   │
       │ & Low-Level Security│
       └─────────────────────┘
```

I am deliberately building these foundations incrementally rather than jumping directly into exploitation techniques without understanding the systems underneath them.

---

# 🧩 Why This Project Exists

This repository is **not intended to present itself as a production-ready generic container library**.

It is a:

> 🎓 **Learning project and a record of progression.**

The purpose was to take concepts I had been studying in C and force myself to use them together in a project requiring me to reason about:

```text
┌───────────────┐
│ Data Structures│
└───────┬───────┘
        │
        ▼
┌───────────────┐
│    Pointers   │
└───────┬───────┘
        │
        ▼
┌───────────────┐
│    Memory     │
└───────┬───────┘
        │
        ▼
┌───────────────┐
│      APIs     │
└───────┬───────┘
        │
        ▼
┌───────────────┐
│    Testing    │
└───────┬───────┘
        │
        ▼
┌───────────────┐
│ Organization  │
└───────────────┘
```

It also represents my first attempt to treat a personal programming project more like a professional software repository.

That includes:

* source/header separation
* testing
* documentation
* Git version control
* structured directory layout
* a reusable public API

As I continue learning C and low-level computing, I expect future repositories to become progressively more sophisticated.

---

# 🔨 Build

A C compiler such as **GCC** can be used to compile the project.

## Compile the main program

```bash
gcc -Wall -Wextra -Wpedantic \
    -Iinclude \
    src/linked_list.c src/main.c \
    -o build/program
```

## Compile the test suite

```bash
gcc -Wall -Wextra -Wpedantic \
    -Iinclude \
    src/linked_list.c tests/test_linked_list.c \
    -o build/test_suite
```

## Run

```bash
./build/program
```

```bash
./build/test_suite
```

> 💡 Build commands may vary depending on the compiler and operating system.

---

# 🧰 Technologies

| Technology | Purpose                                      |
| ---------- | -------------------------------------------- |
| 🇨         | Core implementation                          |
| 🟢 GCC     | Compilation                                  |
| 🌱 Git     | Version control                              |
| 🐙 GitHub  | Repository hosting and project documentation |

---

# 📌 Project Status

### 🟡 Learning Project — Actively Improving

This is the **first substantial C project** in my low-level programming journey.

The implementation will evolve as my understanding of:

```text
C
├── memory management
├── pointers
├── data structures
├── API design
├── testing
└── systems programming
```

continues to improve.

The goal isn't to pretend the project is finished.

The goal is to be able to look back at it later and clearly see how far I've come.

---

# 👤 Author

This project was built as part of my ongoing self-directed study of **C and low-level computing**.

The long-term objective is to develop a strong understanding of how software interacts with:

```text
Memory
   ↓
Processors
   ↓
Operating Systems
   ↓
Binary Data
   ↓
Low-Level Software
```

and eventually apply that knowledge to areas such as:

* 🔬 reverse engineering
* 🔍 binary analysis
* 🐛 vulnerability research
* 🛡️ low-level security
* 💾 digital forensics

---

<div align="center">

### ⚙️ Built to understand what's happening underneath the code.

**C → Memory → Systems → Binaries → Deeper Understanding**

</div>
