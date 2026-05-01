#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <limits>
#include <sstream>

// Import the standard namespace to simplify code.
using namespace std;  

// HELPER FUNCTIONS

// Capitalizes the first letter of each word in a string. (For Title, Author, Category and Borrower Name)
string toTitleCase(const string& str) {
    string result = str;
    bool capitalizeNext = true;
    for (char& c : result) {
        if (c == ' ') {
            capitalizeNext = true;
        } else {
            if (capitalizeNext) {
                c = toupper(c);
                capitalizeNext = false;
            } else {
                c = tolower(c);
            }
        }
    }
    return result;
}

// Logical dates for the publication year. Year must be between 1000 and current year.

// Returns the current year using system time.
int getCurrentYear() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    return now->tm_year + 1900;
}

// Validates a year is not future/negative.
bool isValidYear(int year) {
    int currentYear = getCurrentYear();
    return (year >= 1000 && year <= currentYear);
}

// Clears cin fail state and ignores leftover input in the buffer.
void clearCinError() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Reads a non-empty string. Repeats until valid input is given.
string readNonEmptyString(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) {
            return value;
        }
        cout << "  [!] This field cannot be empty. Please try again." << endl;
    }
}

// Reads a valid integer. Clears the buffer on bad (non-integer) input.
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "  [!] Invalid input. Please enter a number." << endl;
        clearCinError();
    }
}

// Reads and validates a publication year.
int readValidYear(const string& prompt) {
    while (true) {
        int year = readInt(prompt);
        if (isValidYear(year)) {
            return year;
        }
        cout << "  [!] Invalid year. Please enter a year between 1000 and "
             << getCurrentYear() << "." << endl;
    }
}

// Trims leading and trailing whitespace from a string when parsing CSV fields.
string trimWhitespace(const string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end   = str.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : str.substr(start, end - start + 1);
}

// -------------- Assignment Template Code --------------

// Define a Book class to represent an individual book.
class Book {

    private:
        // Private member variables to store book information.
        string bookID;
        string title;
        string author;
        string category;
        int    publicationYear;
        bool   available;
        string borrowerName;   // New - Tracks who borrowed the book when issued.

    public:
        // Constructor to initialize book information.
        Book(const string& id, const string& bookTitle, const string& authorName,
            const string& bookCategory, const int& year, const bool& isAvailable)
            : bookID(id), title(bookTitle), author(authorName),
            category(bookCategory), publicationYear(year),
            available(isAvailable), borrowerName("") {
        }

        // TASK 01: Public member functions (getters) to access book information.

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

        // Setters used by edit, issue, and return operations.
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

        // Display all information about a book in a structured format
        void displayBookInfo() const {
            cout << "  Book ID          : " << bookID          << endl;
            cout << "  Title            : " << title           << endl;
            cout << "  Author           : " << author          << endl;
            cout << "  Category         : " << category        << endl;
            cout << "  Publication Year : " << publicationYear << endl;
            cout << "  Availability     : " << (available ? "Available" : "Issued") << endl;
            if (!available && !borrowerName.empty()) {
                cout << "  Borrower         : " << borrowerName << endl;
            }
        }
};

// Define a Library class to manage a list of books.
class Library {

    private:
        // Private member variable to store a vector of Book objects.
        vector<Book> books;

        // Checks whether a book ID already exists in the library.
        bool idExists(const string& id) const {
            for (const Book& book : books) {
                if (book.getID() == id) return true;
            }
            return false;
        }

    public:
        // Public member function to add a book to the library.
        // Adds a book only if the ID is unique. Returns false if duplicate.
        bool addBook(const Book& book) {
            if (idExists(book.getID())) {
                return false;
            }
            books.push_back(book);
            return true;
        }

        // TASK 02: Public member function to view all books in the library.
        
        // Public member function to view all books in the library.
        void viewBooks() {
            // Handles the empty library case.
            if (books.empty()) {
                cout << "  No books are currently in the system." << endl;
                return;
            }
            cout << "  ========================================" << endl;
            cout << "           ALL BOOKS IN LIBRARY           " << endl;
            cout << "  ========================================" << endl;
            for (const Book& book : books) {
                book.displayBookInfo();
                cout << "  ----------------------------------------" << endl;
            }
            cout << "  Total books: " << books.size() << endl;
        }

        // Public member function to edit a book.
        void editBook(const string& id) {
            for (Book& book : books) {
                if (book.getID() == id) {
                    cout << "\n  What would you like to edit?" << endl;
                    cout << "  1. Category"          << endl;
                    cout << "  2. Publication Year"  << endl;
                    int editChoice = readInt("  Enter choice: ");

                    if (editChoice == 1) {
                        string raw = readNonEmptyString("  Enter new Category                       : ");
                        book.setCategory(toTitleCase(raw));
                        cout << "  Category updated successfully." << endl;
                    } else if (editChoice == 2) {
                        // Title case and Year validation.
                        int newYear = readValidYear(    "  Enter new Publication Year (ex: 1999)    : ");
                        book.setPublicationYear(newYear);
                        cout << "  Publication Year updated successfully." << endl;
                    } else {
                        cout << "  [!] Invalid choice." << endl;
                    }
                    return;
                }
            }
            cout << "  [!] Book Not Found. No book exists with ID \"" << id << "\"." << endl;
        }

        // TASK 03: Public member function to delete a book from the LMS.

        void deleteBook(const string& id) {
            for (auto it = books.begin(); it != books.end(); ++it) {
                if (it->getID() == id) {
                    books.erase(it);
                    cout << "  Book with ID \"" << id << "\" deleted successfully." << endl;
                    return;
                }
            }
            cout << "  [!] Book Not Found. No book exists with ID \"" << id << "\"." << endl;
        }

        // Public member function to issue a book.
        void issueBook(const string& id) {
            for (Book& book : books) {
                if (book.getID() == id) {
                    // Cannot issue a book that is already issued.
                    if (!book.isAvailable()) {
                        cout << "  [!] This book is already issued and cannot be issued again." << endl;
                        return;
                    }
                    string borrower = readNonEmptyString("  Enter Borrower's Name                    : ");
                    book.setAvailable(false);
                    // Borrower name stored in title case.
                    book.setBorrowerName(toTitleCase(borrower));
                    cout << "  Book issued to \"" << toTitleCase(borrower) << "\" successfully." << endl;
                    return;
                }
            }
            cout << "  [!] Book Not Found. No book exists with ID \"" << id << "\"." << endl;
        }

        // Public member function to return a book.
        void returnBook(const string& id) {
            for (Book& book : books) {
                if (book.getID() == id) {
                    // Cannot return a book that is already available.
                    if (book.isAvailable()) {
                        cout << "  [!] This book is already Available and has not been issued." << endl;
                        return;
                    }
                    book.setAvailable(true);
                    book.setBorrowerName("");
                    cout << "  Book returned successfully." << endl;
                    return;
                }
            }
            cout << "  [!] Book Not Found. No book exists with ID \"" << id << "\"." << endl;
        }

        // Public member function to search for books.
        // TASK 1.6: Search book by ID, title, or author (case-insensitive partial match).
        void searchBook(const string& keyword) {
            string lowerKeyword = keyword;
            transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);

            vector<const Book*> results;
            for (const Book& book : books) {
                string lowerID     = book.getID();
                string lowerTitle  = book.getTitle();
                string lowerAuthor = book.getAuthor();
                transform(lowerID.begin(),     lowerID.end(),     lowerID.begin(),     ::tolower);
                transform(lowerTitle.begin(),  lowerTitle.end(),  lowerTitle.begin(),  ::tolower);
                transform(lowerAuthor.begin(), lowerAuthor.end(), lowerAuthor.begin(), ::tolower);

                if (lowerID.find(lowerKeyword)     != string::npos ||
                    lowerTitle.find(lowerKeyword)  != string::npos ||
                    lowerAuthor.find(lowerKeyword) != string::npos) {
                    results.push_back(&book);
                }
            }

            if (results.empty()) {
                cout << "  No books found matching \"" << keyword << "\"." << endl;
            } else {
                cout << "  Found " << results.size() << " result(s) for \"" << keyword << "\":" << endl;
                cout << "  ----------------------------------------" << endl;
                for (const Book* b : results) {
                    b->displayBookInfo();
                    cout << "  ----------------------------------------" << endl;
                }
            }
        }

        // Public member function to save books to a file.
        void saveLibraryToFile(const string& filename) {
            ofstream file(filename);
            if (file.is_open()) {
                for (const Book& book : books) {
                    file << "ID               : " << book.getID()              << "\n";
                    file << "Title            : " << book.getTitle()           << "\n";
                    file << "Author           : " << book.getAuthor()          << "\n";
                    file << "Category         : " << book.getCategory()        << "\n";
                    file << "Publication Year : " << book.getPublicationYear() << "\n";
                    file << "Available        : " << (book.isAvailable() ? "Yes" : "No") << "\n";
                    if (!book.isAvailable()) {
                        file << "Borrower         : " << book.getBorrowerName() << "\n";
                    }
                    file << "-----------------------------\n";
                }
                cout << "  Books saved to \"" << filename << "\" successfully." << endl;
                file.close();
            } else {
                cerr << "  [!] Error: Unable to open file \"" << filename << "\" for writing." << endl;
            }
        }

        // TASK 1.6: Import books from a CSV file into the library.

        // Expected CSV format (with header row):
        //   BookID,Title,Author,Category,PublicationYear,Available
        //   1001,The Great Gatsby,F Scott Fitzgerald,Fiction,1925,1
        void importFromCSV(const string& filename) {
            ifstream file(filename);
            if (!file.is_open()) {
                cerr << "  [!] Error: Cannot open file \"" << filename << "\". Please check the filename and try again." << endl;
                return;
            }

            string line;
            int imported = 0;
            int skipped  = 0;
            bool firstLine = true;

            while (getline(file, line)) {
                // Skip the header row.
                if (firstLine) {
                    firstLine = false;
                    continue;
                }

                // Skip blank lines.
                if (line.empty()) continue;

                // Parse the 6 comma-separated fields.
                stringstream ss(line);
                string fields[6];
                int fieldCount = 0;
                while (fieldCount < 6 && getline(ss, fields[fieldCount], ',')) {
                    fields[fieldCount] = trimWhitespace(fields[fieldCount]);
                    fieldCount++;
                }

                // Validate: must have exactly 6 fields and none of the key ones empty.
                if (fieldCount < 6 || fields[0].empty() || fields[1].empty() || fields[2].empty()) {
                    cout << "  [!] Skipping invalid row: \"" << line << "\"" << endl;
                    skipped++;
                    continue;
                }

                string id       = fields[0];
                string title    = toTitleCase(fields[1]);
                string author   = toTitleCase(fields[2]);
                string category = toTitleCase(fields[3]);
                int    year     = 0;
                bool   avail    = true;

                // Validate publication year.
                try {
                    year = stoi(fields[4]);
                } catch (...) {
                    cout << "  [!] Skipping row with invalid year: \"" << line << "\"" << endl;
                    skipped++;
                    continue;
                }
                if (!isValidYear(year)) {
                    cout << "  [!] Skipping row with out-of-range year (" << year << "): \"" << fields[1] << "\"" << endl;
                    skipped++;
                    continue;
                }

                // Parse availability (1 = available, 0 = issued).
                avail = (trimWhitespace(fields[5]) == "1");

                Book newBook(id, title, author, category, year, avail);

                // Skip if duplicate ID already exists.
                if (!addBook(newBook)) {
                    cout << "  [!] Skipping duplicate Book ID \"" << id << "\": \"" << title << "\"" << endl;
                    skipped++;
                } else {
                    imported++;
                }
            }

            file.close();
            cout << "  Import complete. " << imported << " book(s) imported, " << skipped << " skipped." << endl;
        }
};


// MAIN FUNCTION
int main() {
    Library library;

    cout << "========================================" << endl;
    cout << "     LIBRARY MANAGEMENT SYSTEM (LMS)    " << endl;
    cout << "========================================" << endl;

    int choice;
    do {
        cout << "\n--- MENU ---" << endl;
        cout << "  1. Add Book"                  << endl;
        cout << "  2. View Books"                << endl;
        cout << "  3. Edit Book"                 << endl;
        cout << "  4. Delete Book"               << endl;
        cout << "  5. Issue Book"                << endl;
        cout << "  6. Return Book"               << endl;
        cout << "  7. Save Book Details to File" << endl;
        cout << "  8. Search Book"               << endl;
        cout << "  9. Import Books from CSV"     << endl;
        cout << "  10. Quit"                     << endl;
        cout << "Enter your choice: ";

        // Safe integer read
        if (!(cin >> choice)) {
            clearCinError();
            choice = -1;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {

            // TASK 04: Case 1 — Add a new book to the LMS.

            case 1: {
                // Add a new book to the LMS.
                cout << "\n--- Add New Book ---" << endl;

                // Non-empty + no spaces in ID.
                string id;
                while (true) {
                    id = readNonEmptyString("Enter Book ID (ex: 1000)                  : ");
                    if (id.find(' ') != string::npos) {
                        cout << "  [!] Book ID cannot contain spaces. Please try again." << endl;
                        continue;
                    }
                    break;
                }

                // Title case + non-empty validation.
                string bookTitle    = toTitleCase(readNonEmptyString("Enter Title                               : "));
                string authorName   = toTitleCase(readNonEmptyString("Enter Author Name                         : "));
                string bookCategory = toTitleCase(readNonEmptyString("Enter Category                            : "));

                // Validated year.
                int year = readValidYear(             "Enter Publication Year (ex: 1999)         : ");

                // Availability — only 0 or 1 accepted.
                int availInt;
                while (true) {
                    availInt = readInt(              "Is the book available? (1 = Yes, 0 = No)  : ");
                    if (availInt == 0 || availInt == 1) break;
                    cout << "  [!] Please enter 1 for Yes or 0 for No." << endl;
                }
                bool isAvailable = (availInt == 1);

                Book newBook(id, bookTitle, authorName, bookCategory, year, isAvailable);

                // Duplicate ID check.
                if (!library.addBook(newBook)) {
                    cout << "  [!] Book ID is already available. Try a new ID." << endl;
                } else {
                    cout << "  Book added successfully!" << endl;
                }
                break;
            }

            // TASK 05: Case 2 — View all books in the LMS.

            case 2: {
                // View all books in the LMS.
                cout << "\n--- View All Books ---" << endl;
                library.viewBooks();
                break;
            }

            case 3: {
                // Edit a book.
                cout << "\n--- Edit Book ---" << endl;
                string idToEdit = readNonEmptyString("Enter Book ID to edit                     : ");
                library.editBook(idToEdit);
                break;
            }

            case 4: {
                // Delete a book from the library.
                cout << "\n--- Delete Book ---" << endl;
                string idToDelete = readNonEmptyString("Enter Book ID to delete                   : ");
                library.deleteBook(idToDelete);
                break;
            }

            case 5: {
                // Issue a book.
                cout << "\n--- Issue Book ---" << endl;
                string idToIssue = readNonEmptyString("Enter Book ID to issue                    : ");
                library.issueBook(idToIssue);
                break;
            }

            case 6: {
                // Return a book.
                cout << "\n--- Return Book ---" << endl;
                string idToReturn = readNonEmptyString("Enter Book ID to return                   : ");
                library.returnBook(idToReturn);
                break;
            }

            case 7: {
                // Save book details to a file.
                cout << "\n--- Save to File ---" << endl;
                string filename = readNonEmptyString("Enter filename (ex: library.txt)          : ");
                library.saveLibraryToFile(filename);
                break;
            }

            
            case 8: {
                // Search book by ID, title, or author.
                cout << "\n--- Search Book ---" << endl;
                cout << "  Search by Book ID, Title, or Author." << endl;
                string keyword = readNonEmptyString("Enter search keyword                      : ");
                library.searchBook(keyword);
                break;
            }

            case 9: {
                // Import books from a CSV file.
                cout << "\n--- Import Books from CSV ---" << endl;
                cout << "  CSV format: BookID,Title,Author,Category,PublicationYear,Available" << endl;
                cout << "  Available column: 1 = Available, 0 = Issued" << endl;
                string csvFile = readNonEmptyString("Enter CSV filename (ex: books.csv)        : ");
                library.importFromCSV(csvFile);
                break;
            }

            case 10: {
                // Exit the Library Management System.
                cout << "\nExiting Library Management System. Goodbye!" << endl;
                break;
            }

            default:
                // Default case catches any input outside 1–10.
                cout << "  [!] Invalid choice. Please enter a number between 1 and 10." << endl;
        }

    } while (choice != 10);

    return 0;
}