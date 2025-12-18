#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;

    Book() : id(0), isIssued(false) {}

    Book(int id, const string &title, const string &author)
        : id(id), title(title), author(author), isIssued(false) {}

    // Serialize book to text
    string serialize() const {
        return to_string(id) + "|" +
               to_string(isIssued) + "|" +
               title + "|" +
               author;
    }

    // Deserialize book from text
    static Book deserialize(const string &line) {
        Book b;
        size_t pos = 0, next;
        vector<string> parts;

        while ((next = line.find('|', pos)) != string::npos) {
            parts.push_back(line.substr(pos, next - pos));
            pos = next + 1;
        }
        parts.push_back(line.substr(pos));

        b.id = stoi(parts[0]);
        b.isIssued = stoi(parts[1]);
        b.title = parts[2];
        b.author = parts[3];

        return b;
    }

    void display() const {
        cout << "ID: " << id
             << ", Title: " << title
             << ", Author: " << author
             << ", Issued: " << (isIssued ? "Yes" : "No") << "\n";
    }
};

class Library {
private:
    vector<Book> books;
    const string filename = "books.txt";

    void loadFromFile() {
        ifstream file(filename);
        if (!file) return;

        string line;
        while (getline(file, line)) {
            books.push_back(Book::deserialize(line));
        }
        file.close();
    }

    void saveToFile() {
        ofstream file(filename, ios::trunc);
        for (const auto &b : books) {
            file << b.serialize() << "\n";
        }
        file.close();
    }

    Book* findBookById(int id) {
        for (auto &b : books) {
            if (b.id == id)
                return &b;
        }
        return nullptr;
    }

public:
    Library() {
        loadFromFile();
    }

    void addBook() {
        int id;
        string title, author;

        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();

        if (findBookById(id)) {
            cout << "Book ID already exists!\n";
            return;
        }

        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);

        books.emplace_back(id, title, author);
        saveToFile();
        cout << "Book added successfully!\n";
    }

    void displayBooks() const {
        if (books.empty()) {
            cout << "No books available.\n";
            return;
        }
        for (const auto &b : books)
            b.display();
    }

    void issueBook() {
        int id;
        cout << "Enter Book ID to issue: ";
        cin >> id;

        Book* b = findBookById(id);
        if (!b) {
            cout << "Book not found.\n";
            return;
        }
        if (b->isIssued) {
            cout << "Book already issued.\n";
            return;
        }

        b->isIssued = true;
        saveToFile();
        cout << "Book issued successfully!\n";
    }

    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;

        Book* b = findBookById(id);
        if (!b) {
            cout << "Book not found.\n";
            return;
        }
        if (!b->isIssued) {
            cout << "Book is not issued.\n";
            return;
        }

        b->isIssued = false;
        saveToFile();
        cout << "Book returned successfully!\n";
    }

    void searchBook() const {
        string key;
        cin.ignore();
        cout << "Enter keyword (title/author): ";
        getline(cin, key);

        bool found = false;
        for (const auto &b : books) {
            if (b.title.find(key) != string::npos ||
                b.author.find(key) != string::npos) {
                b.display();
                found = true;
            }
        }
        if (!found)
            cout << "No matching books found.\n";
    }
};

int main() {
    Library lib;
    int choice;

    while (true) {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n2. Display Books\n3. Issue Book\n";
        cout << "4. Return Book\n5. Search Book\n6. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;
        switch (choice) {
        case 1: lib.addBook(); break;
        case 2: lib.displayBooks(); break;
        case 3: lib.issueBook(); break;
        case 4: lib.returnBook(); break;
        case 5: lib.searchBook(); break;
        case 6: return 0;
        default: cout << "Invalid choice!\n";
        }
    }
}
