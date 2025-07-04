#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class Book
{
public:
    int id;
    string title;
    string author;
    bool isIssued;

    Book() {}
    Book(int i, string t, string a)
    {
        id = i;
        title = t;
        author = a;
        isIssued = false;
    }

    void display()
    {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author << ", Issued: " << (isIssued ? "Yes" : "No") << endl;
    }
};

class Library
{
    vector<Book> books;

    void saveToFile()
    {
        ofstream file("books.dat", ios::binary | ios::out);
        for (auto &book : books)
            file.write((char *)&book, sizeof(Book));
        file.close();
    }

    void loadFromFile()
    {
        ifstream file("books.dat", ios::binary | ios::in);
        if (!file)
            return;
        Book b;
        while (file.read((char *)&b, sizeof(Book)))
            books.push_back(b);
        file.close();
    }

public:
    Library()
    {
        loadFromFile();
    }

    void addBook()
    {
        int id;
        string title, author;
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        books.emplace_back(id, title, author);
        saveToFile();
        cout << "Book added successfully!\n";
    }

    void displayBooks()
    {
        if (books.empty())
            cout << "No books available.\n";
        for (auto &b : books)
            b.display();
    }

    void issueBook()
    {
        int id;
        cout << "Enter Book ID to issue: ";
        cin >> id;
        for (auto &b : books)
        {
            if (b.id == id)
            {
                if (b.isIssued)
                {
                    cout << "Book is already issued.\n";
                }
                else
                {
                    b.isIssued = true;
                    saveToFile();
                    cout << "Book issued successfully!\n";
                }
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void returnBook()
    {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;
        for (auto &b : books)
        {
            if (b.id == id)
            {
                if (!b.isIssued)
                {
                    cout << "Book is not issued.\n";
                }
                else
                {
                    b.isIssued = false;
                    saveToFile();
                    cout << "Book returned successfully!\n";
                }
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void searchBook()
    {
        string keyword;
        cin.ignore();
        cout << "Enter keyword to search (title/author): ";
        getline(cin, keyword);
        bool found = false;
        for (auto &b : books)
        {
            if (b.title.find(keyword) != string::npos || b.author.find(keyword) != string::npos)
            {
                b.display();
                found = true;
            }
        }
        if (!found)
            cout << "No matching books found.\n";
    }
};

int main()
{
    Library lib;
    int choice;
    while (true)
    {
        cout << "\n--- Library Management ---\n";
        cout << "1. Add Book\n2. Display Books\n3. Issue Book\n4. Return Book\n5. Search Book\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            lib.addBook();
            break;
        case 2:
            lib.displayBooks();
            break;
        case 3:
            lib.issueBook();
            break;
        case 4:
            lib.returnBook();
            break;
        case 5:
            lib.searchBook();
            break;
        case 6:
            exit(0);
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
