#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStringList>


//Window constructor, init with Ui,load from text file and update the ui to reflect it
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_selectedItem(0)
{
    setupUI(); //create ui
    loadFromFile(); //load exisiting data or create a sample data
    updateItemList(); //add the loaded data to the ui
    setWindowTitle("Shaheer van Duyn Library Management System");
    resize(1280, 720);
}

MainWindow::~MainWindow()
{
    //Save data before closing
    saveToFile();

    //Clean storage
    for (int i = 0; i < m_allItems.size(); ++i)
    {
        delete m_allItems[i];
    }
}


//Create the ui with input and display
void MainWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    //Main layout
    QHBoxLayout *mainLayout = new QHBoxLayout(m_centralWidget);

    //Input side
    QVBoxLayout *leftLayout = new QVBoxLayout();

    //Book input group
    QGroupBox *bookGroup = new QGroupBox("Add Book");
    QGridLayout *bookLayout = new QGridLayout(bookGroup);

    //Input widgets for book
    m_bookTitleEdit = new QLineEdit();
    m_bookAuthorEdit = new QLineEdit();
    m_bookGenreEdit = new QLineEdit();
    m_bookPagesSpin = new QSpinBox();
    m_bookPagesSpin->setRange(1, 9999);
    m_bookPagesSpin->setValue(100);

    //Grid layout
    bookLayout->addWidget(new QLabel("Title:"), 0, 0);
    bookLayout->addWidget(m_bookTitleEdit, 0, 1);
    bookLayout->addWidget(new QLabel("Author:"), 1, 0);
    bookLayout->addWidget(m_bookAuthorEdit, 1, 1);
    bookLayout->addWidget(new QLabel("Genre:"), 2, 0);
    bookLayout->addWidget(m_bookGenreEdit, 2, 1);
    bookLayout->addWidget(new QLabel("Pages:"), 3, 0);
    bookLayout->addWidget(m_bookPagesSpin, 3, 1);

    //add boook button
    m_addBookBtn = new QPushButton("Add Book");
    bookLayout->addWidget(m_addBookBtn, 4, 0, 1, 2);

    //Magazine input group
    QGroupBox *magazineGroup = new QGroupBox("Add Magazine");
    QGridLayout *magazineLayout = new QGridLayout(magazineGroup);

    //Input widgets for magazine
    m_magazineTitleEdit = new QLineEdit();
    m_magazineAuthorEdit = new QLineEdit();
    m_magazineIssueSpin = new QSpinBox();
    m_magazineIssueSpin->setRange(1, 999);
    m_magazineIssueSpin->setValue(1);
    m_magazineDateEdit = new QLineEdit();
    m_magazineDateEdit->setText("2024-01-01");

    //Grid layout for magazine
    magazineLayout->addWidget(new QLabel("Title:"), 0, 0);
    magazineLayout->addWidget(m_magazineTitleEdit, 0, 1);
    magazineLayout->addWidget(new QLabel("Author:"), 1, 0);
    magazineLayout->addWidget(m_magazineAuthorEdit, 1, 1);
    magazineLayout->addWidget(new QLabel("Issue #:"), 2, 0);
    magazineLayout->addWidget(m_magazineIssueSpin, 2, 1);
    magazineLayout->addWidget(new QLabel("Date:"), 3, 0);
    magazineLayout->addWidget(m_magazineDateEdit, 3, 1);

    m_addMagazineBtn = new QPushButton("Add Magazine");
    magazineLayout->addWidget(m_addMagazineBtn, 4, 0, 1, 2);

    //Search UI, to search by title or author
    QGroupBox *searchGroup = new QGroupBox("Search");
    QVBoxLayout *searchLayout = new QVBoxLayout(searchGroup);

    m_searchEdit = new QLineEdit();
    m_searchEdit->setPlaceholderText("Search by title or author...");
    m_searchBtn = new QPushButton("Search");

    searchLayout->addWidget(m_searchEdit);
    searchLayout->addWidget(m_searchBtn);

    //Buttons for borrowing,returning,deleting etc
    QGroupBox *controlGroup = new QGroupBox("Controls");
    QVBoxLayout *controlLayout = new QVBoxLayout(controlGroup);


    m_borrowBtn = new QPushButton("Borrow Item");
    m_returnBtn = new QPushButton("Return Item");
    m_deleteBtn = new QPushButton("Delete Item");
    m_clearBtn = new QPushButton("Clear Fields");
    m_saveBtn = new QPushButton("Save Data");
    m_loadBtn = new QPushButton("Load Data");

    //Add buttons to layout
    controlLayout->addWidget(m_borrowBtn);
    controlLayout->addWidget(m_returnBtn);
    controlLayout->addWidget(m_deleteBtn);
    controlLayout->addWidget(m_clearBtn);
    controlLayout->addWidget(m_saveBtn);
    controlLayout->addWidget(m_loadBtn);

    leftLayout->addWidget(bookGroup);
    leftLayout->addWidget(magazineGroup);
    leftLayout->addWidget(searchGroup);
    leftLayout->addWidget(controlGroup);
    leftLayout->addStretch();

    //Display
    QVBoxLayout *rightLayout = new QVBoxLayout();

    //Library Item list
    m_itemList = new QListWidget();
    rightLayout->addWidget(new QLabel("Library Items:"));
    rightLayout->addWidget(m_itemList);

    //Item details
    m_detailsText = new QTextEdit();
    m_detailsText->setReadOnly(true);
    m_detailsText->setMaximumHeight(150);
    rightLayout->addWidget(new QLabel("Item Details:"));
    rightLayout->addWidget(m_detailsText);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    //Connect buttons to thier signals
    connect(m_addBookBtn, SIGNAL(clicked()), this, SLOT(addBook()));
    connect(m_addMagazineBtn, SIGNAL(clicked()), this, SLOT(addMagazine()));
    connect(m_searchBtn, SIGNAL(clicked()), this, SLOT(searchItems()));
    connect(m_borrowBtn, SIGNAL(clicked()), this, SLOT(borrowItem()));
    connect(m_returnBtn, SIGNAL(clicked()), this, SLOT(returnItem()));
    connect(m_deleteBtn, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(m_clearBtn, SIGNAL(clicked()), this, SLOT(clearFields()));
    connect(m_saveBtn, SIGNAL(clicked()), this, SLOT(saveData()));
    connect(m_loadBtn, SIGNAL(clicked()), this, SLOT(loadData()));
    connect(m_itemList, SIGNAL(itemSelectionChanged()), this, SLOT(onItemSelected()));

    updateItemList();
}


//Function for adding a book to the library
void MainWindow::addBook()
{
    //Get input
    QString title = m_bookTitleEdit->text();
    QString author = m_bookAuthorEdit->text();
    QString genre = m_bookGenreEdit->text();
    int pages = m_bookPagesSpin->value();

    //Error checking
    if (title.isEmpty() || author.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please ensure you have filled in the title and author");
        return;
    }

    //Create book object
    Book *book = new Book(title, author, getNextId(), genre, pages);
    m_storage.addItem(book);
    m_allItems.append(book);

    //Update UI and save the book to the file
    clearInputFields();
    updateItemList();
    saveToFile(); // Auto-save after adding
    QMessageBox::information(this, "Success", "Book added");
}
//Function for adding a magazine to the library
void MainWindow::addMagazine()
{
    //Get input
    QString title = m_magazineTitleEdit->text();
    QString author = m_magazineAuthorEdit->text();
    int issue = m_magazineIssueSpin->value();
    QString date = m_magazineDateEdit->text();
    //Error checking
    if (title.isEmpty() || author.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please ensure you have filled in the title and author");
        return;
    }

    //Create Magazine object
    Magazine *magazine = new Magazine(title, author, getNextId(), issue, date);
    m_storage.addItem(magazine);
    m_allItems.append(magazine);

    //Update UI and save to file
    clearInputFields();
    updateItemList();
    saveToFile(); // Auto-save after adding
    QMessageBox::information(this, "Success", "Magazine added successfully!");
}

//Search for library items using title or author name
void MainWindow::searchItems()
{
    //Get the text to search for and conver to lower case
    QString searchText = m_searchEdit->text().toLower();
    if (searchText.isEmpty()) //if empty show all items
    {
        updateItemList();
        return;
    }

    //Clear list to only show the search results
    m_itemList->clear();

    //Search through items
    for (int i = 0; i < m_allItems.size(); ++i)
    {
        LibraryItem *item = m_allItems[i];
        if (item->getTitle().toLower().contains(searchText) ||
            item->getAuthor().toLower().contains(searchText))
        {

            QString itemText = QString("[%1] %2 - %3 (%4)")
            .arg(item->getId())
                .arg(item->getTitle())
                .arg(item->getAuthor())
                .arg(item->getIsBorrowed() ? "Borrowed" : "Available");

            QListWidgetItem *listItem = new QListWidgetItem(itemText);
            listItem->setData(Qt::UserRole, QVariant::fromValue((void *)item));
            m_itemList->addItem(listItem);
        }
    }
}


//Sets the selected item to borrowed
void MainWindow::borrowItem()
{
    //if nothing is selected show an errror
    if (!m_selectedItem)
    {
        QMessageBox::warning(this, "Warning", "Please select an item to borrow.");
        return;
    }

    //Check if its already borrowed
    if (m_selectedItem->getIsBorrowed())
    {
        QMessageBox::warning(this, "Warning", "This item is already borrowed.");
        return;
    }

    //Set to borrowed and update the UI
    m_selectedItem->setIsBorrowed(true);
    updateItemList();
    onItemSelected();
    saveToFile(); // Auto-save after borrowing
    QMessageBox::information(this, "Success", "Item borrowed successfully!");
}


//Sets the selected item as returned
void MainWindow::returnItem()
{
    //Same functionality as borrowing
    if (!m_selectedItem)
    {
        QMessageBox::warning(this, "Warning", "Please select an item to return.");
        return;
    }

    if (!m_selectedItem->getIsBorrowed())
    {
        QMessageBox::warning(this, "Warning", "This item is not borrowed.");
        return;
    }

    m_selectedItem->setIsBorrowed(false);
    updateItemList();
    onItemSelected();
    saveToFile(); // Auto-save after returning
    QMessageBox::information(this, "Success", "Item returned successfully!");
}


//Delete a selected item and ask the user if they are sure
void MainWindow::deleteItem()
{

    if (!m_selectedItem)
    {
        QMessageBox::warning(this, "Warning", "Please select an item to delete.");
        return;
    }
    //Ask the user if they are sure to delete
    int response = QMessageBox::question(this, "Confirm",
                                    "Are you sure you want to delete this item?",
                                    QMessageBox::Yes | QMessageBox::No);


    if (response == QMessageBox::Yes)
    {

        m_storage.removeItem(m_selectedItem);

        m_allItems.removeOne(m_selectedItem);

        delete m_selectedItem;
        m_selectedItem = 0;

        updateItemList();
        m_detailsText->clear();
        saveToFile(); // Auto-save after deleting
        QMessageBox::information(this, "Success", "Item deleted successfully!");
    }
}
//To refresh the UI
void MainWindow::refreshList()
{
    updateItemList();
}

//Clear all input fields
void MainWindow::clearFields()
{
    clearInputFields();
    m_searchEdit->clear();
}

//Manualy save data
void MainWindow::saveData()
{
    saveToFile();
    QMessageBox::information(this, "Success", "Data saved to library_data.txt!");
}
//Manually load data
void MainWindow::loadData()
{
    loadFromFile();
    updateItemList();
    QMessageBox::information(this, "Success", "Data loaded from library_data.txt!");
}

void MainWindow::onItemSelected()
{
    QListWidgetItem *currentItem = m_itemList->currentItem();
    if (currentItem)
    {
        m_selectedItem = (LibraryItem *)currentItem->data(Qt::UserRole).value<void *>();
        if (m_selectedItem)
        {
            m_detailsText->setText(m_selectedItem->displayInfo());
        }
    }
    else
    {
        m_selectedItem = 0;
        m_detailsText->clear();
    }
}

void MainWindow::updateItemList()
{
    m_itemList->clear();

    for (int i = 0; i < m_allItems.size(); ++i)
    {
        LibraryItem *item = m_allItems[i];
        QString itemText = QString("[%1] %2 - %3 (%4)")
                               .arg(item->getId())
                               .arg(item->getTitle())
                               .arg(item->getAuthor())
                               .arg(item->getIsBorrowed() ? "Borrowed" : "Available");

        QListWidgetItem *listItem = new QListWidgetItem(itemText);
        listItem->setData(Qt::UserRole, QVariant::fromValue((void *)item));

        if (item->getIsBorrowed())
        {
            listItem->setBackground(QColor(255, 200, 200)); // Light red
        }
        else
        {
            listItem->setBackground(QColor(200, 255, 200)); // Light green
        }

        m_itemList->addItem(listItem);
    }
}
//Clear all input fields
void MainWindow::clearInputFields()
{
    m_bookTitleEdit->clear();
    m_bookAuthorEdit->clear();
    m_bookGenreEdit->clear();
    m_bookPagesSpin->setValue(100);

    m_magazineTitleEdit->clear();
    m_magazineAuthorEdit->clear();
    m_magazineIssueSpin->setValue(1);
    m_magazineDateEdit->setText("2024-01-01");
}
//Generate unique ID for library items
int MainWindow::getNextId()
{
    int maxId = 0;
    for (int i = 0; i < m_allItems.size(); ++i)
    {
        if (m_allItems[i]->getId() > maxId)
        {
            maxId = m_allItems[i]->getId();
        }
    }
    return maxId + 1;
}

//Save data to library_data.txt
void MainWindow::saveToFile()
{
    QFile file("library_data.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", "Could not open file");
        return;
    }

    QTextStream out(&file);
    out << "# Library Management System Data File\n";
    out << "# Format: ID|Type|Title|Author|IsBorrowed|[Type-specific data]\n";
    out << "# Book: ID|Book|Title|Author|IsBorrowed|Genre|PageCount\n";
    out << "# Magazine: ID|Magazine|Title|Author|IsBorrowed|IssueNumber|PublicationDate\n\n";

    for (int i = 0; i < m_allItems.size(); ++i)
    {
        out << m_allItems[i]->toFileString() << "\n";
    }

    file.close();
}

//Load data from library_data.txt
void MainWindow::loadFromFile()
{

    for (int i = 0; i < m_allItems.size(); ++i)
    {
        delete m_allItems[i];
    }
    m_allItems.clear();
    m_storage.clear();

    QFile file("library_data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //Add sample data for testing if the file does not exist
        Book *book1 = new Book("Keyboard", "Mouse", 1, "Computer", 250);
        Book *book2 = new Book("How to code", "Qt5", 2, "Education", 300);
        Magazine *mag1 = new Magazine("C++", "C Programming", 3, 100, "2025-08-11");

        m_allItems.append(book1);
        m_allItems.append(book2);
        m_allItems.append(mag1);

        m_storage.addItem(book1);
        m_storage.addItem(book2);
        m_storage.addItem(mag1);

        saveToFile();
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();

       //Skip empty lines
        if (line.isEmpty() || line.startsWith("#"))
        {
            continue;
        }

        QStringList parts = line.split("|");
        if (parts.size() < 5)
        {
            continue;
        }

        QString type = parts[1];
        LibraryItem *item = 0;

        if (type == "Book" && parts.size() >= 7)
        {
            item = new Book();
        }
        else if (type == "Magazine" && parts.size() >= 7)
        {
            item = new Magazine();
        }

        if (item)
        {
            item->fromFileString(line);
            m_allItems.append(item);
            m_storage.addItem(item);
        }
    }

    file.close();
}
