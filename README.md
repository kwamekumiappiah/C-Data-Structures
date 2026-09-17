# 🛠️ Heterogeneous Linked List Library in C

A lightweight, type-safe, heterogeneous singly linked list library written in C. Designed with explicit memory management, pointer manipulation, and dynamic typing via C unions.

---

## 🎯 Motivation & Goals

This project serves as my foundational deep-dive into C programming and manual memory management. Built as a step toward my long-term trajectory in **low-level engineering, reverse engineering, and binary security analysis**, this repository focuses on:
* Manual dynamic memory allocation (`malloc`, `free`) and pointer arithmetic.
* Modern C project organization and build workflows.
* Automated modular unit testing and explicit data layout design.

---

## 🧱 Architecture & Project Structure

Organized according to standard C software design practices:

```text
.
├── include/
│   └── linked_list.h     # Public API, data types, and struct definitions
├── src/
│   ├── linked_list.c    # Core library implementation
│   └── main.c           # Example application / demonstration
├── tests/
│   └── test_linked_list.c # Comprehensive unit testing suite
└── build/               # Output directory for compiled binaries
