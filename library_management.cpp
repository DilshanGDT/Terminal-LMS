#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Import the standard namespace to simplify code.
// Define a Book class to represent an individual book.
class Book {
private:
    // Private member variables to store book information.
    string bookID;
    string title;
    string author;
    string category;
    int publicationYear;
    bool available;
    string borrowerName; // stores borrower name when issued

public:
    // Constructor to initialize book information.
    Book(const string& id, const string& bookTitle, const string& authorName,
         const string& bookCategory, const int& year, const bool& isAvailable)
        : bookID(id), title(bookTitle), author(authorName),
          category(bookCategory), publicationYear(year),
          available(isAvailable), borrowerName("") {
    }

    // ---------------------------------------------------------------
    // TASK 01: Public member functions (getters) to access book info.
    // ---------------------------------------------------------------
    string getID() const {
        return bookID;
    }

    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    string getCategory() const {
        return category;
    }

    int getPublicationYear() const {
        return publicationYear;
    }

    bool isAvailable() const {
        return available;
    }

    string getBorrowerName() const {
        return borrowerName;
    }

    // Setters needed for issue/return/edit operations
    void setAvailable(bool status) {
        available = status;
    }

    void setBorrowerName(const string& name) {
        borrowerName = name;
    }

    void setCategory(const string& newCategory) {
        category = newCategory;
    }

    void setPublicationYear(int year) {
        publicationYear = year;
    }

    // Display all book information in a structured format
    void displayBookInfo() const {
        cout << "Book ID         : " << bookID << endl;
        cout << "Title           : " << title << endl;
        cout << "Author          : " << author << endl;
        cout << "Category        : " << category << endl;
        cout << "Publication Year: " << publicationYear << endl;
        cout << "Availability    : " << (available ? "Available" : "Issued") << endl;
        if (!available && !borrowerName.empty()) {
            cout << "Borrower        : " << borrowerName << endl;
        }
    }
};


// Define a Library class to manage a list of books.
class Library {
private:
    // Private member variable to store a vector of Book objects.
    vector<Book> books;

public:
    // Public member function to add a book to the library.
    void addBook(const Book& book) {
        books.push_back(book);
    }

    // ---------------------------------------------------------------
    // TASK 02: Public member function to view all books in the library.
    // ---------------------------------------------------------------
    void viewBooks() {
        if (books.empty()) {
            cout << "No books found in the library." << endl;
            return;
        }
        cout << "========================================" << endl;
        cout << "         ALL BOOKS IN LIBRARY           " << endl;
        cout << "========================================" << endl;
        for (const Book& book : books) {
            book.displayBookInfo();
            cout << "----------------------------------------" << endl;
        }
    }

    // Public member function to edit a book.
    void editBook(const string& id) {
        for (Book& book : books) {
            if (book.getID() == id) {
                cout << "What would you like to edit?" << endl;
                cout << "1. Category" << endl;
                cout << "2. Publication Year" << endl;
                cout << "Enter choice: ";
                int editChoice;
                cin >> editChoice;
                cin.ignore();

                if (editChoice == 1) {
                    string newCategory;
                    cout << "Enter new category: ";
                    getline(cin, newCategory);
                    book.setCategory(newCategory);
                    cout << "Category updated successfully." << endl;
                } else if (editChoice == 2) {
                    int newYear;
                    cout << "Enter new publication year: ";
                    cin >> newYear;
                    book.setPublicationYear(newYear);
                    cout << "Publication year updated successfully." << endl;
                } else {
                    cout << "Invalid choice." << endl;
                }
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    // ---------------------------------------------------------------
    // TASK 03: Public member function to delete a book from the LMS.
    // ---------------------------------------------------------------
    void deleteBook(const string& id) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getID() == id) {
                books.erase(it);
                cout << "Book with ID \"" << id << "\" has been deleted successfully." << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    // Public member function to issue a book.
    void issueBook(const string& id) {
        for (Book& book : books) {
            if (book.getID() == id) {
                if (!book.isAvailable()) {
                    cout << "Book is already issued." << endl;
                    return;
                }
                cout << "Enter borrower's name: ";
                string borrower;
                cin.ignore();
                getline(cin, borrower);
                book.setAvailable(false);
                book.setBorrowerName(borrower);
                cout << "Book issued to \"" << borrower << "\" successfully." << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    // Public member function to return a book.
    void returnBook(const string& id) {
        for (Book& book : books) {
            if (book.getID() == id) {
                if (book.isAvailable()) {
                    cout << "This book was not issued." << endl;
                    return;
                }
                book.setAvailable(true);
                book.setBorrowerName("");
                cout << "Book returned successfully." << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    // Public member function to save books to a file.
    void saveLibraryToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const Book& book : books) {
                file << "ID: " << book.getID() << endl;
                file << "Title: " << book.getTitle() << endl;
                file << "Author: " << book.getAuthor() << endl;
                file << "Category: " << book.getCategory() << endl;
                file << "Publication Year: " << book.getPublicationYear() << endl;
                file << "Available: " << (book.isAvailable() ? "Yes" : "No") << endl;
                file << "---------------------------" << endl;
            }
            cout << "Books saved to " << filename << " successfully." << endl;
            file.close();
        } else {
            cerr << "Error: Unable to open file " << filename << " for writing." << endl;
        }
    }
};


int main() {
    Library library;
    int choice;

    cout << "========================================" << endl;
    cout << "     LIBRARY MANAGEMENT SYSTEM (LMS)    " << endl;
    cout << "========================================" << endl;

    do {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. View Books" << endl;
        cout << "3. Edit Book" << endl;
        cout << "4. Delete Book" << endl;
        cout << "5. Issue Book" << endl;
        cout << "6. Return Book" << endl;
        cout << "7. Save Book Details to File" << endl;
        cout << "8. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            // ---------------------------------------------------------------
            // TASK 04: Case 1 — Add a new book to the LMS.
            // ---------------------------------------------------------------
            case 1: {
                string id, bookTitle, authorName, bookCategory;
                int year;
                bool isAvailable;

                cout << "\n--- Add New Book ---" << endl;

                cout << "Enter Book ID         : ";
                cin.ignore();
                getline(cin, id);

                cout << "Enter Title           : ";
                getline(cin, bookTitle);

                cout << "Enter Author Name     : ";
                getline(cin, authorName);

                cout << "Enter Category        : ";
                getline(cin, bookCategory);

                cout << "Enter Publication Year: ";
                cin >> year;

                cout << "Is the book available? (1 = Yes, 0 = No): ";
                cin >> isAvailable;

                Book newBook(id, bookTitle, authorName, bookCategory, year, isAvailable);
                library.addBook(newBook);
                cout << "Book added successfully!" << endl;
                break;
            }

            // ---------------------------------------------------------------
            // TASK 05: Case 2 — View all books in the LMS.
            // ---------------------------------------------------------------
            case 2: {
                cout << "\n--- View All Books ---" << endl;
                library.viewBooks();
                break;
            }

            case 3: {
                // Edit a book.
                string idToEdit;
                cout << "Enter the book ID of the book to edit: ";
                cin.ignore();
                getline(cin, idToEdit);
                library.editBook(idToEdit);
                break;
            }

            case 4: {
                // Delete a book from the library.
                string idToDelete;
                cout << "Enter the book ID of the book to delete: ";
                cin.ignore();
                getline(cin, idToDelete);
                library.deleteBook(idToDelete);
                break;
            }

            case 5: {
                // Issue a book.
                string idToIssue;
                cout << "Enter the book ID of the book to issue: ";
                cin.ignore();
                getline(cin, idToIssue);
                library.issueBook(idToIssue);
                break;
            }

            case 6: {
                // Return a book.
                string idToReturn;
                cout << "Enter the book ID of the book to return: ";
                cin.ignore();
                getline(cin, idToReturn);
                library.returnBook(idToReturn);
                break;
            }

            case 7: {
                // Save book details to a file.
                string filename;
                cout << "Enter the filename to save book details: ";
                cin.ignore();
                getline(cin, filename);
                library.saveLibraryToFile(filename);
                break;
            }

            case 8: {
                // Exit the Library Management System.
                cout << "Exiting Library Management System. Goodbye!" << endl;
                break;
            }

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 8);

    return 0;
}