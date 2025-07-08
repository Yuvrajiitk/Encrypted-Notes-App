# 🔐 Encrypted Notes App (C++)

This is a simple terminal-based note-taking application I built using C++. It allows users to store personal notes securely in an encrypted file. Notes are protected with a master password and encrypted using XOR logic before saving.

The goal behind this project was to gain hands-on experience with file handling in C++, implement basic encryption, and design a usable CLI interface for real-world use cases.

---

## ✨ Features

✅ Password-protected access  
📝 Add, view, and delete notes through a clean CLI  
🔒 Notes are encrypted using XOR and saved in `notes.db`  
📦 Uses standard C++ STL for strings, vectors, and file I/O  
💾 All notes persist across sessions

---

## ⚙️ How to Run

1. 🛠 Make sure a C++ compiler (like `g++`) is installed  
2. 📁 Clone this repo or download the code  
3. 🚀 Compile and run the program:

```bash
g++ notes_app.cpp -o notes_app
./notes_app


📁 EncryptedNotesApp/
├── notes_app.cpp       // Main C++ source code
├── .gitignore          // Ignore compiled files & database
├── notes.db            // Encrypted notes file (auto-created)
├── README.md           // You're reading this!
