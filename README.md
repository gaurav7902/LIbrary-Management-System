# Library Management System (C++)

## 📌 Overview
A console-based Library Management System built using C++ and Object-Oriented Programming principles.  
The system allows users to manage books, issue/return them, and persist data across executions.

## 🚀 Features
- Add new books with unique IDs
- Display all available books
- Issue and return books
- Search books by title or author
- Persistent storage using file handling

## 🛠️ Technologies Used
- C++
- OOP (Encapsulation, Abstraction)
- File Handling (Text Serialization)
- STL (vector, string)

## 📂 Data Storage
Books are stored in a text file (`books.txt`) using a safe serialization format:
id|isIssued|title|author

## ▶️ How to Run
```bash
g++ library.cpp -o library
./library
```
## 📌 Future Enhancements
- User login system
- Due date & fine calculation
- Admin/User role separation
