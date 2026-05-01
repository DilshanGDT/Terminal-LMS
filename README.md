# Terminal Library Management System (LMS)

A simple terminal-based Library Management System written in C++ that allows users to manage a collection of books. This system supports adding, viewing, editing, deleting, issuing, returning, searching, and importing/exporting books via CSV files.

## Features

- **Add Books**: Add new books with unique IDs, titles, authors, categories, publication years, and availability status.
- **View Books**: Display all books in the library with detailed information.
- **Edit Books**: Modify the category or publication year of existing books.
- **Delete Books**: Remove books from the library by ID.
- **Issue Books**: Mark books as issued to borrowers.
- **Return Books**: Mark issued books as returned.
- **Search Books**: Search for books by ID, title, or author (case-insensitive partial matches).
- **Save to File**: Export the library data to a text file.
- **Import from CSV**: Import books from a CSV file with a specific format.

## Requirements

- C++ compiler (e.g., g++ from MinGW or MSYS2)
- Standard C++ libraries (included with most compilers)

## Installation and Setup

1. Clone or download the project files to your local machine.
2. Ensure you have a C++ compiler installed (e.g., g++).

## Building the Project

Use the provided build task in VS Code or compile manually:

```bash
g++ -fdiagnostics-color=always -g lms.cpp -o lms.exe
```

This will generate an executable `lms.exe` in the same directory.

## Running the Application

After building, run the executable:

```bash
./lms.exe
```

The application will display a menu with options from 1 to 10. Follow the prompts to perform operations.

## Usage

1. **Menu Options**:
   - 1. Add Book: Enter book details (ID, title, author, category, year, availability).
   - 2. View Books: Lists all books in the library.
   - 3. Edit Book: Enter book ID and choose what to edit (category or year).
   - 4. Delete Book: Enter book ID to remove.
   - 5. Issue Book: Enter book ID and borrower's name to issue.
   - 6. Return Book: Enter book ID to return.
   - 7. Save Book Details to File: Enter filename to save library data.
   - 8. Search Book: Enter keyword to search by ID, title, or author.
   - 9. Import Books from CSV: Enter CSV filename to import books.
   - 10. Quit: Exit the application.

2. **Input Validation**:
   - Book IDs must be unique and contain no spaces.
   - Titles, authors, and categories are automatically formatted to title case.
   - Publication years must be between 1000 and the current year.
   - Availability is set as 1 (available) or 0 (issued).

3. **CSV Import Format**:
   The CSV file should have a header row and the following columns:
   ```
   BookID,Title,Author,Category,PublicationYear,Available
   ```
   - Available: 1 for available, 0 for issued.
   - Example row: `1001,The Great Gatsby,F Scott Fitzgerald,Fiction,1925,1`

## File Structure

- `lms.cpp`: Main source file containing the Library Management System logic.
- `books.csv`: Sample CSV file for importing books.
- `bookDetails.txt`: Example output file for saved book details.
- `newLibrary.txt`: Another example output file.
- `library_management.cpp`: Basic implementation.

## Troubleshooting

- **Compilation Errors**: Ensure your C++ compiler supports C++11 or later. Check for missing includes or syntax errors.
- **Runtime Errors**: Verify input formats match the expected types (e.g., integers for years).
- **CSV Import Issues**: Ensure the CSV file has the correct format and no duplicate IDs. Check for invalid years or missing fields.
- **File Operations**: Ensure write permissions for saving files and correct paths for importing CSV.