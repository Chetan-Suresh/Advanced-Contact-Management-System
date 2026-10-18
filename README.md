# Advanced Contact Management System

A C-based contact management application featuring multi-layer input validation, duplicate detection, contact search, editing, deletion, sorting, and file-based data persistence.

## Overview

The Advanced Contact Management System is a menu-driven command-line application developed in C. It allows users to manage contact information through a structured address book while applying validation rules to help maintain data consistency.

## Features

- **Create Contacts:** Add contacts with name, phone number, and email address.
- **Search Contacts:** Find existing contacts using supported search criteria.
- **Edit Contacts:** Update contact information with validation.
- **Delete Contacts:** Remove contacts from the address book.
- **List and Sort:** Display contacts sorted by name, phone number, or email.
- **Input Validation:** Validate names, phone numbers, and email addresses.
- **Duplicate Detection:** Check for duplicate phone numbers and email addresses.
- **File Handling:** Store and retrieve contact information using a text file.

## Technologies Used

- **Language:** C
- **Concepts:** Structures, functions, pointers, arrays, string handling, and input validation
- **File Handling:** Standard C file I/O (`fopen`, `fscanf`, `fprintf`, `fclose`)
- **Compiler:** GCC

## Project Structure

```text
Advanced-Contact-Management-System/
├── main.c       # Main menu and program entry point
├── contact.c    # Contact management and validation logic
├── contact.h    # Contact structures and function declarations
├── file.c       # File storage and retrieval operations
├── file.h       # File handling function declarations
├── contacts.txt # Contact data storage
├── .gitignore
├── LICENSE
└── README.md
```

## Getting Started

### Prerequisites

Install a C compiler such as GCC.

### Compile the Project

Open a terminal in the project directory and run:

```bash
gcc main.c contact.c file.c -o address_book
```

### Run the Application

On Linux or macOS:

```bash
./address_book
```

On Windows with GCC:

```bash
gcc main.c contact.c file.c -o address_book.exe
address_book.exe
```

Keep `contacts.txt` in the same directory as the executable because the application uses it to load and save contact data.

## Learning Objectives

This project demonstrates practical applications of:

- Modular programming in C
- Structures and arrays
- String manipulation and validation
- CRUD operations (Create, Read, Update, Delete)
- File handling and data persistence
- Sorting and searching techniques

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
