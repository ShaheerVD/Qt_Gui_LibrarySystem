# Qt_Gui_LibrarySystem
# Library Management System

A Qt-based GUI application for managing library items (books and magazines) with features for adding, borrowing, returning, searching, and persistent storage.

## Overview

This Library Management System is a desktop application built using C++ and the Qt framework. It demonstrates object-oriented programming concepts including inheritance, polymorphism, templates, and file I/O operations. The system allows librarians to manage a collection of books and magazines through an intuitive graphical interface.

## Features

- **Add Items**: Add books (with genre and page count) or magazines (with issue number and publication date)
- **Search**: Search for items by title, author, or ID
- **Borrow/Return**: Track borrowed items with status updates
- **Delete Items**: Remove items from the library collection
- **Persistent Storage**: Save and load library data to/from file (`library_data.txt`)
- **Item Details**: View detailed information about selected items
- **Automatic ID Assignment**: System automatically assigns unique IDs to new items

## Technologies Used

- **Language**: C++17
- **Framework**: Qt 6.9.0
- **Build System**: qmake
- **Compiler**: MinGW 64-bit

## Class Structure

### LibraryItem (Abstract Base Class)

The abstract base class for all library items with common attributes:

- Title
- Author
- ID
- Borrowed status

**Virtual methods**:

- `displayInfo()`: Display item information
- `getType()`: Return item type
- `toFileString()`: Serialize to file format
- `fromFileString()`: Deserialize from file format

### Book (Derived Class)

Inherits from `LibraryItem` with additional properties:

- Genre
- Page count

### Magazine (Derived Class)

Inherits from `LibraryItem` with additional properties:

- Issue number
- Publication date

### Storage (Template Class)

A generic template-based container for storing library items with operations:

- Add/remove items
- Search with predicates
- Get all items
- Clear storage

### MainWindow

The main GUI controller that handles:

- User interface setup
- Item management operations
- File I/O (save/load)
- User interactions

## File Structure

```
LibrarySystem/
├── libraryitem.h/cpp     # Abstract base class
├── book.h/cpp            # Book class implementation
├── magazine.h/cpp        # Magazine class implementation
├── Storage.h             # Template storage class
├── mainwindow.h/cpp      # Main window GUI controller
├── mainwindow.ui         # Qt Designer UI file
├── main.cpp              # Application entry point
├── LibrarySystem.pro     # Qt project file
├── library_data.txt      # Data persistence file (generated)
└── README.md             # This file
```

## Building the Project

### Prerequisites

- Qt 6.9.0 or later
- MinGW 64-bit compiler (or compatible C++17 compiler)
- qmake build tool

### Build Instructions

1. **Open the project in Qt Creator**:

   ```
   File → Open File or Project → Select LibrarySystem.pro
   ```

2. **Configure the project** with Qt 6.9.0 Desktop Kit (MinGW 64-bit)

3. **Build the project**:

   - Press `Ctrl+B` or
   - Build → Build Project "LibrarySystem"

4. **Run the application**:
   - Press `Ctrl+R` or
   - Build → Run

```

## Usage

### Adding a Book
1. Enter book details in the "Add Book" section (Title, Author, Genre, Page Count)
2. Click "Add Book" button
3. The book appears in the library list

### Adding a Magazine
1. Enter magazine details in the "Add Magazine" section (Title, Author, Issue Number, Publication Date)
2. Click "Add Magazine" button
3. The magazine appears in the library list

### Searching for Items
1. Enter search term in the search field
2. Click "Search" button
3. Results are filtered in the list

### Borrowing an Item
1. Select an item from the list
2. Click "Borrow Item" button
3. Item status updates to "Borrowed"

### Returning an Item
1. Select a borrowed item from the list
2. Click "Return Item" button
3. Item status updates to "Available"

### Deleting an Item
1. Select an item from the list
2. Click "Delete Item" button
3. Item is removed from the collection

### Saving Data
- Click "Save Data" button to save all items to `library_data.txt`
- Data is saved in a custom format with type prefixes (BOOK: or MAGAZINE:)

### Loading Data
- Click "Load Data" button to load items from `library_data.txt`
- Previously saved items will be restored

## Data File Format

The `library_data.txt` file uses a pipe-delimited format:

**Books**:
```

BOOK:|Title|Author|ID|IsBorrowed|Genre|PageCount

```

**Magazines**:
```

MAGAZINE:|Title|Author|ID|IsBorrowed|IssueNumber|PublicationDate

```

Example:
```

BOOK:|The Great Gatsby|F. Scott Fitzgerald|1|0|Fiction|180
MAGAZINE:|National Geographic|Various|2|1|1234|2025-01-01

```

## Key Programming Concepts Demonstrated

1. **Inheritance**: `Book` and `Magazine` inherit from `LibraryItem`
2. **Polymorphism**: Virtual functions for type-specific behavior
3. **Templates**: Generic `Storage<T>` class for flexible data management
4. **Encapsulation**: Private members with public getter/setter methods
5. **File I/O**: Persistent data storage and retrieval
6. **GUI Programming**: Qt widgets and signal/slot mechanism
7. **Memory Management**: Proper use of pointers and Qt's parent-child system

## Academic Integrity

This project was completed as part of university coursework for COS2614 at UNISA. If you are a student taking this course, please adhere to  academic integrity policies and do not use this code for direct submission.

## License

This project is submitted as academic work for educational purposes.




---

*Developed as Assignment 3
```
