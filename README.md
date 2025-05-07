# 🗃️ Simple Database Management System (C Language)

A lightweight, console-based Database Management System (DBMS) developed in C, designed for educational purposes. This project showcases how to manage structured data using file handling, basic CRUD operations, and procedural programming principles in C.

---

## 📌 Key Features

- 🔐 **Insert Records** – Add new structured data entries to the system.
- 📄 **Display Records** – View all records in a clean tabulated format.
- ❌ **Delete Records** – Remove records using a unique identifier.
- 💾 **File-Based Storage** – Persists data in a flat `.txt` file.
- 📚 **Simple CLI Interface** – Interactive terminal-based user experience.

---

## 🛠️ Tech Stack

| Tech       | Description                      |
|------------|----------------------------------|
| **C**      | Core programming language        |
| **GCC**    | Compiler for building the project|
| **File I/O** | Persistent data storage via `fopen`, `fprintf`, etc. |

---

## 🚀 Getting Started

### Prerequisites

- A C compiler (e.g. `gcc`, `clang`)
- Any OS with a terminal (Linux, macOS, Windows WSL or Git Bash)

### Build Instructions

```bash
gcc main.c -o simple-dbms
Run
bash
Copy
Edit
./simple-dbms
Follow the on-screen instructions to interact with the system.

📁 Project Structure
plaintext
Copy
Edit
Simple-Database-Management-System/
├── main.c             # Main source code (all logic)
├── database.txt       # Plain text file used to store records
└── README.md          # Project documentation
🧠 Concepts Demonstrated
File manipulation using C standard I/O

Procedural program flow and menu-driven interfaces

Data validation and basic error handling

Separation of concerns (future refactor)
