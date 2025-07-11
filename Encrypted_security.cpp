// Encrypted Notes App in C++
// Author: Yuvraj
// Description: A terminal-based secure note-taking app using XOR encryption and file I/O.
// Features: Add/View/Delete notes, Password-protected access, Encrypted storage

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const string DATA_FILE = "notes.db";
const string MASTER_PASSWORD = "1234"; // This can be customized
const char XOR_KEY = 'K'; // XOR key used for basic encryption

// Structure to represent a note
struct Note {
    string title;
    string content;
};

// Function to encrypt or decrypt text using XOR logic
string xorEncryptDecrypt(const string& input) {
    string output = input;
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ XOR_KEY;
    }
    return output;
}

// Save a note to the encrypted file
void saveNote(const Note& note) {
    ofstream fout(DATA_FILE, ios::app);
    if (!fout) {
        cout << "Error: Could not open file to write notes.\n";
        return;
    }
    fout << xorEncryptDecrypt(note.title) << endl;
    fout << xorEncryptDecrypt(note.content) << endl;
    fout.close();
    cout << "\n✅ Note saved successfully.\n";
}

// Load all notes from the encrypted file
vector<Note> loadNotes() {
    vector<Note> notes;
    ifstream fin(DATA_FILE);
    if (!fin) return notes;
    string title, content;
    while (getline(fin, title) && getline(fin, content)) {
        notes.push_back({ xorEncryptDecrypt(title), xorEncryptDecrypt(content) });
    }
    fin.close();
    return notes;
}

// List all note titles
void listNotes(const vector<Note>& notes) {
    if (notes.empty()) {
        cout << "\nNo notes available.\n";
        return;
    }
    cout << "\nSaved Notes:\n";
    for (size_t i = 0; i < notes.size(); ++i) {
        cout << i + 1 << ". " << notes[i].title << endl;
    }
}

// View content of a selected note
void viewNote(const vector<Note>& notes) {
    listNotes(notes);
    if (notes.empty()) return;
    cout << "\nEnter the note number to view: ";
    int index;
    cin >> index;
    if (index < 1 || index > static_cast<int>(notes.size())) {
        cout << "Invalid selection.\n";
        return;
    }
    cout << "\n🔓 " << notes[index - 1].title << "\n";
    cout << "--------------------------------------\n";
    cout << notes[index - 1].content << endl;
    cout << "--------------------------------------\n";
}

// Delete a selected note and update the file
void deleteNote(vector<Note>& notes) {
    listNotes(notes);
    if (notes.empty()) return;
    cout << "\nEnter the note number to delete: ";
    int index;
    cin >> index;
    if (index < 1 || index > static_cast<int>(notes.size())) {
        cout << "Invalid selection.\n";
        return;
    }
    string deletedTitle = notes[index - 1].title;
    notes.erase(notes.begin() + (index - 1));

    ofstream fout(DATA_FILE);
    for (const auto& note : notes) {
        fout << xorEncryptDecrypt(note.title) << endl;
        fout << xorEncryptDecrypt(note.content) << endl;
    }
    fout.close();
    cout << "\n🗑️  Deleted note: \"" << deletedTitle << "\"\n";
}

// Display main menu
void showMenu() {
    cout << "\n1. Add a New Note\n2. View Notes\n3. Delete a Note\n4. Exit\n";
    cout << "\nChoose an option (1-4): ";
}

int main() {
    cout << "==============================\n";
    cout << "  Welcome to Secure Notes 🔐\n";
    cout << "==============================\n\n";

    string password;
    cout << "Enter master password: ";
    cin >> password;

    if (password != MASTER_PASSWORD) {
        cout << "\n❌ Access Denied.\n";
        return 0;
    }

    cout << "\n✅ Access Granted.\n";

    while (true) {
        vector<Note> notes = loadNotes(); // reload notes every cycle
        showMenu();
        int choice;
        cin >> choice;
        cin.ignore(); // clear newline

        if (choice == 1) {
            Note note;
            cout << "\nEnter note title: ";
            getline(cin, note.title);
            cout << "Enter note content:\n";
            getline(cin, note.content);
            saveNote(note);
        }
        else if (choice == 2) {
            viewNote(notes);
        }
        else if (choice == 3) {
            deleteNote(notes);
        }
        else if (choice == 4) {
            cout << "\n🔐 Logging out. Goodbye!\n";
            break;
        }
        else {
            cout << "\nInvalid choice. Try again.\n";
        }
    }

    return 0;
}
