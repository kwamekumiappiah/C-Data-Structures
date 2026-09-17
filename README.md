# 🔗 Heterogeneous Linked List in C

> A type-safe, generic, memory-managed linked list built from scratch in C — no `void*` spaghetti, no leaks, no undefined behavior left unexamined.

![C](https://img.shields.io/badge/language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Status](https://img.shields.io/badge/status-active%20learning%20project-yellow?style=for-the-badge)
![Memory Safety](https://img.shields.io/badge/tested%20with-ASan%20%7C%20Valgrind-critical?style=for-the-badge)
![License](https://img.shields.io/badge/license-MIT-blue?style=for-the-badge)

---

## 📖 Table of Contents

- [Why This Project Exists](#-why-this-project-exists)
- [What It Does](#-what-it-does)
- [Project Structure](#-project-structure)
- [Getting Started](#-getting-started)
- [Design Deep Dive](#-design-deep-dive)
- [Bugs I Found (and Fixed)](#-bugs-i-found-and-fixed)
- [What I Learned](#-what-i-learned)
- [Testing](#-testing)
- [Roadmap](#-roadmap)
- [Where This Is Heading](#-where-this-is-heading)
- [Contact](#-contact)

---

## 🎯 Why This Project Exists

I started learning C **63 days ago**. This repository is not a tutorial project — it's the first thing I built to prove to myself (and eventually to employers) that I actually understand what's happening underneath the language, not just that I can copy syntax.

My long-term goal is **low-level systems work**: binary exploitation, reverse engineering, and digital forensics. All three fields demand the same foundation — a precise mental model of memory, pointers, and how data is actually laid out and manipulated at runtime. You can't exploit a vulnerability you don't understand, and you can't understand it without first being able to *build* correct (and sometimes intentionally broken) C.

So instead of jumping straight into CTFs or `pwntools`, I picked a project that forces you to touch every core C concept at once:

- Manual memory management (`malloc`/`free`, ownership, lifetimes)
- Pointers and pointer-to-pointer indirection
- `struct`s and `union`s (and the type-punning risks that come with them)
- Opaque types and API design / encapsulation
- Defensive programming (NULL checks, bounds checks)
- Writing and reading your own test suite

This README documents not just *what* the code does, but *what I learned building it*, including the bugs I introduced and later found — because in low-level programming, finding your own bugs **is** the skill.

---

## ⚙️ What It Does

A **generic (heterogeneous) singly linked list** — meaning a single list instance can store nodes of *different C types* simultaneously (an `int`, right next to a `double`, right next to a `char`), safely, using a **tagged union**.

```c
linkedList *list = create_linked_list();

int    age    = 25;
double gpa    = 3.8;
char   grade  = 'A';

add_node(list, TYPE_INT,    &age);
add_node(list, TYPE_DOUBLE, &gpa);
add_node(list, TYPE_CHAR,   &grade);

print_linked_list(list);   // 25 -> 3.800000 -> A -> NULL

free_linked_list(list);
```

### Core capabilities

| Category | Functions |
|---|---|
| 🏗️ **Lifecycle** | `create_linked_list`, `free_linked_list` |
| ➕ **Insertion** | `add_node`, `prepend_node`, `insert_value` |
| ➖ **Deletion** | `delete_node` (by index), `delete_node_value` (by value) |
| 🔍 **Search** | `search_by_index`, `search_by_value`, `contains_value` |
| 🧠 **Utility** | `is_empty`, `get_list_length`, `clone_list`, `reverse_list` |
| 🖨️ **Display** | `print_linked_list` |

Supported types: `char`, `unsigned char`, `short`, `unsigned short`, `int`, `unsigned int`, `long`, `unsigned long`, `long long`, `unsigned long long`, `float`, `double`, `long double`, and `void*`.

---

## 📂 Project Structure

```
.
├── build/
│   ├── program.exe
│   └── test_suite.exe
├── include/
│   └── linked_list.h       # Public API + type definitions
├── src/
│   ├── linked_list.c       # Implementation
│   └── main.c              # Demo / entry point
└── tests/
    └── test_linked_list.c  # Custom unit test suite (no external framework)
```

The header exposes an **opaque struct** — client code never sees the internals of `linkedList` or `Node`, only pointers to them. This isn't cosmetic; it's the same principle used to protect internal state in real-world C libraries (and, on the flip side, exactly the kind of boundary an RE engineer has to reconstruct from a stripped binary when the source isn't available).

---

## 🚀 Getting Started

### Requirements
- A C compiler (GCC / Clang / MSVC)
- (Optional, recommended) `valgrind` or `clang`'s AddressSanitizer for memory checking

### Build & Run

```bash
git clone https://github.com/<your-username>/<repo-name>.git
cd <repo-name>

gcc -Wall -Wextra -g -Iinclude src/linked_list.c src/main.c -o build/program
./build/program
```

### Run the Test Suite

```bash
gcc -Wall -Wextra -g -Iinclude src/linked_list.c tests/test_linked_list.c -o build/test_suite
./build/test_suite
```

### Run Under AddressSanitizer (recommended — this is how I catch memory bugs)

```bash
gcc -fsanitize=address -g -Iinclude src/linked_list.c tests/test_linked_list.c -o build/test_suite_asan
./build/test_suite_asan
```

---

## 🧩 Design Deep Dive

### 1. The Tagged Union — how "one list, many types" actually works

```c
typedef struct Node {
    DataType type;          // discriminator — tells us which union field is "live"
    union {
        char char_val;
        int  int_val;
        double double_val;
        // ... etc
        void *void_ptr_val;
    } value;
    struct Node *next;
} Node;
```

A `union` in C means all its members **share the same memory** — writing to one field overwrites the others. On its own, a union has no memory of what was last stored in it. The `type` field solves that: it's the discriminator that tells every other function in the library *which* union member is currently valid to read. This is the classic C pattern for building generic containers when you don't have templates or generics — you fake polymorphism with a type tag plus a `switch`.

**Why this matters for RE/security work:** this is precisely the pattern malware and real-world parsers use for "variant" data types (think: a network packet where a `type` byte tells the parser how to interpret the bytes that follow, or a Windows `VARIANT` struct). Understanding tagged unions from the *builder's* side makes it dramatically easier to reverse-engineer them from the *disassembler's* side later.

### 2. Opaque Struct Pattern — real encapsulation in C

```c
// linked_list.h — client only ever sees a forward declaration
typedef struct linkedList linkedList;

// linked_list.c — full definition hidden from the client
typedef struct linkedList {
    size_t length;
    Node *head;
} linkedList;
```

Client code can only hold a `linkedList *` — a pointer to something it can't inspect, can't `sizeof()`, and can't accidentally corrupt by reaching into its fields directly. All access goes through the public API. This is C's version of a "private" class member, and it's how most production C libraries (OpenSSL, SQLite, zlib) hide implementation details from consumers.

### 3. Type-Safe Retrieval via `ListElement`

```c
typedef struct {
    DataType type;
    void *data;
} ListElement;
```

Instead of returning a raw `void*` and hoping the caller remembers what they stored, every search function returns a `(type, data)` pair. The caller checks `type` before casting `data`, e.g.:

```c
ListElement e = search_by_index(list, 0);
if (e.type == TYPE_INT) {
    printf("%d\n", *(int *)e.data);
}
```

This pushes the "know your types" discipline into the API contract instead of leaving it as an unstated assumption — a small design choice, but one that reflects how much CTF/exploit-dev work is really about *finding where an assumption like this was left unstated* in someone else's code.

---

## 🐛 Bugs I Found (and Fixed)

I'm documenting these deliberately, unedited. In low-level programming, the bugs you catch — and how you caught them — matter more than pretending the first draft was perfect.

### ✅ Fixed: Uninitialized `next` pointer on first insert

**The bug:** `create_node()` used `malloc`, not `calloc`, so every field started as garbage memory — including `next`. `add_node()` explicitly zeroed `next` after creating a node, but `insert_value()`'s "insert into an empty list" branch didn't. Calling `prepend_node()` as the *very first* operation on a brand-new list produced a head node with a garbage `next` pointer — a ticking time bomb that would crash (or worse, silently corrupt memory) on the next traversal.

**Why my own tests didn't catch it:** every test that exercised `prepend_node` did so on a list that already had a node in it, which coincidentally already had a valid `next`. Classic case of a test suite giving false confidence by not covering the *specific* state transition where the bug lived.

**The fix:** moved `ptr->next = NULL;` into `create_node()` itself, so every node is fully initialized at the single point of construction — no caller can forget it again.

```c
static Node *create_node(DataType type, void *data) {
    Node *ptr = malloc(sizeof(Node));
    if (!ptr) return NULL;
    switch (type) { /* ... */ }
    ptr->next = NULL;   // ✅ now guaranteed, regardless of caller
    return ptr;
}
```

**Lesson:** enforce struct invariants in the constructor, not in every call site. One place to get right beats three.

### 🔧 In Progress: `TYPE_VOID_POINTER` calling-convention mismatch

**The bug:** every other type follows the same convention — pass the *address of* the value (`&my_int`), and `create_node` dereferences it (`*(int *)data`). But the `TYPE_VOID_POINTER` case breaks the pattern:

```c
case TYPE_VOID_POINTER:
    ptr->value.void_ptr_val = data;   // stores data directly, doesn't dereference
```

Meanwhile, `compare_node_value()` assumes the *opposite* convention for the same type (`*(void **)search_data`), and `clone_list()` inherits the confusion — cloning a void-pointer node ends up storing a pointer into the *original* node's internal union field instead of copying the pointer value, creating a subtle aliasing bug between "independent" clones.

**Status:** identified, not yet fixed — intentionally left visible in the repo as an open issue rather than quietly patched, because catching type-convention drift across a codebase is exactly the muscle I'm building.

### 🔧 Known Landmine: unsigned underflow in `get_node_before_target`

```c
while (tracker < index - 1) { ... }
```

`index` is `size_t` (unsigned). If this helper is ever called with `index == 0`, `index - 1` wraps around to the maximum possible `size_t` value instead of going negative, causing an out-of-bounds walk off the end of the list. No current caller triggers it (they all guard `index == 0` first), but it's exactly the kind of latent bug that becomes exploitable the moment someone extends the code without knowing the implicit precondition.

> Track open issues like these on the [Issues tab](../../issues) of this repo as I work through them.

---

## 🧠 What I Learned

A running log of the concepts this project forced me to actually understand, not just recognize:

- **Manual memory lifetime management** — every `malloc` needs an owner and an exit plan; `free_linked_list` has to walk and free every node *before* freeing the container, in the right order.
- **Pointers vs. pointers-to-pointers** — modifying `linked_list->head` from inside a helper function requires passing the *list*, not a copy of the head pointer.
- **Struct/union memory layout** — a `union` is not "extra type safety," it's raw shared memory with a discriminator bolted on by convention, not by the compiler.
- **API design and encapsulation** — hiding implementation details behind a forward-declared struct, and why that boundary matters both for safety and for maintainability.
- **Defensive programming as a habit** — NULL checks and bounds checks at the top of every function, not as an afterthought.
- **The gap between "compiles" and "correct"** — every bug above compiled cleanly and ran fine in the common case. Finding them required either adversarial test design or tools like ASan, not just reading the code again.
- **Why testing your own assumptions matters more than testing the happy path** — my test suite passed 100% while still shipping a memory bug, because I tested *behaviors* I expected to work, not the specific state transition where they didn't.

---

## 🧪 Testing

The `tests/` directory contains a self-contained unit test suite (no external framework — just a custom `TEST_ASSERT` macro) covering:

1. Lifecycle, empty-state checks, and length tracking
2. All three insertion modes (`add`, `prepend`, `insert_value`)
3. Search by index and by value, including not-found cases
4. Deletion by index and by value
5. Deep cloning and independent state verification
6. In-place list reversal

```
🟢 [PASS] List created successfully
🟢 [PASS] New list is empty
🟢 [PASS] New list length is 0
...
🎉 ALL TESTS COMPLETED
```

Going forward, I'm adding tests specifically designed to *break* the code (empty-list edge cases, boundary indices, repeated frees) rather than just confirm it works — see [Roadmap](#-roadmap).

---

## 🗺️ Roadmap

- [ ] Fix `TYPE_VOID_POINTER` calling-convention mismatch across `create_node`, `compare_node_value`, and `clone_list`
- [ ] Guard `get_node_before_target` against the `index == 0` underflow case
- [ ] Add a `Makefile` for one-command builds
- [ ] Add regression tests specifically targeting the bugs documented above
- [ ] Run and document a full Valgrind pass (`--leak-check=full --show-leak-kinds=all`)
- [ ] Write a small fuzz harness (libFuzzer or AFL++) targeting `insert_value` / `delete_node` with randomized indices
- [ ] Convert to a doubly linked list as a follow-up project
- [ ] Explore an intentionally *vulnerable* branch (e.g., a version with a deliberate use-after-free) to practice finding it with GDB + ASan, as a bridge into exploit-dev fundamentals

---

## 🔭 Where This Is Heading

This project is step one of a deliberate path:

```
C fundamentals (this repo)
        │
        ▼
Memory-safety tooling (ASan, Valgrind, GDB)
        │
        ▼
Intentionally vulnerable C (buffer overflows, UAF, format strings)
        │
        ▼
Binary exploitation fundamentals (stack/heap exploitation, ROP)
        │
        ▼
Reverse engineering & forensic analysis
```

Everything in this README exists because those later stages are unreachable without a real, hands-on model of how memory, pointers, and types behave — not the textbook version, the version where you've personally shipped an uninitialized pointer and had to go find it. This repo is where that started.

---

## 📬 Contact

I'm actively building toward low-level security work and always happy to talk C, memory safety, or how this project could be improved.

- GitHub: [@kwamekumiappiah](https://github.com/kwamekumiappiah)
- LinkedIn: https://www.linkedin.com/in/kwameappiah-kumi-appiah/
- Email: kwameappiahkumi@gmail.com

---

<p align="center">
  <i>⭐ If you're an employer or fellow learner and this documentation style was useful, a star helps me know it's worth keeping up.</i>
</p>
