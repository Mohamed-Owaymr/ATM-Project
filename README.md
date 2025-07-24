# 🏧 ATM System in C++
> A Functional Programming Practice Project

---

## 🎯 About The Project

This project is a **console-based ATM system** written in C++, developed as part of my learning and practice in **Functional Programming (FP)** using C++.

The goal is to simulate a basic banking system with clean, modular, and reusable functions — avoiding the use of classes wherever possible — to embrace the **functional programming paradigm**.

---

## 🎓 Why This Project?

✅ **Practicing Functional Thinking**  
✅ **Strengthening Logic Building and Modularity**  
✅ **Handling Real-World Tasks in C++ Without Classes**  
✅ **Simulating a System Using File Storage Instead of Databases**

> 🧠 This project is meant as an educational tool and a stepping stone toward mastering functional programming concepts in C++.

---

## ✨ Key Features

- 🔐 Login system (Account Number + PIN)
- 💸 Quick Withdraw (20, 50, 100, etc.)
- 💰 Normal Withdraw (custom amount)
- 🏦 Deposit feature
- 📊 Balance check
- ✏️ Update user info (PIN, Name, Address, Phone)
- 🔄 Send money to a friend in the same bank
- 📃 View transaction and pay history
- 🔓 Logout securely

---

## 🧱 Functional Approach

- Core logic is built around **pure functions** with clear inputs and outputs.
- **Minimal use of classes**, most features are handled through modular functions.
- All data is stored and managed via **flat text files** instead of using any database system.
- Emphasis on:
  - Function reusability
  - Separation of concerns
  - Side-effect management (e.g. file I/O isolated)

---

## 🛠️ Technologies Used

- C++ (ISO Standard)
- File I/O (Text files)
- STL (`vector`, `string`, `fstream`, etc.)

---

## 📂 Project Structure
ATM-Project/
- main.cpp # Main controller logic
- utility.cpp # Functional modules for transactions, I/O
- utility.h # Function declarations and shared types
- Clients.txt # Sample data storage file
- README.md # Project description
- .gitignore # Ignored files and build outputs

---

## 🚀 How to run
1. Clone the repository  
2. Compile the code using a C++ compiler  
3. Run the executable  
