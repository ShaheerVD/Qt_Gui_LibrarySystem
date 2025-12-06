
//Shaheer van Duyn

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QListWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QTextEdit>

#include "libraryitem.h"
#include "storage.h"
#include "book.h"
#include "magazine.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //slots
private slots:
    void addBook();
    void addMagazine();
    void searchItems();
    void borrowItem();
    void returnItem();
    void deleteItem();
    void refreshList();
    void clearFields();
    void saveData();
    void loadData();
    void onItemSelected();

private:
    //ui setup
    void setupUI();
    void updateItemList();
    void clearInputFields();
    int getNextId();

    //file io
    void saveToFile();
    void loadFromFile();

    //storage
    Storage<LibraryItem *> m_storage;
    QList<LibraryItem *> m_allItems;

    //widgets
    QWidget *m_centralWidget;

    //input
    QLineEdit *m_bookTitleEdit;
    QLineEdit *m_bookAuthorEdit;
    QLineEdit *m_bookGenreEdit;
    QSpinBox *m_bookPagesSpin;

    QLineEdit *m_magazineTitleEdit;
    QLineEdit *m_magazineAuthorEdit;
    QSpinBox *m_magazineIssueSpin;
    QLineEdit *m_magazineDateEdit;

    //displat
    QListWidget *m_itemList;
    QTextEdit *m_detailsText;
    QLineEdit *m_searchEdit;

    //buttons
    QPushButton *m_addBookBtn;
    QPushButton *m_addMagazineBtn;
    QPushButton *m_searchBtn;
    QPushButton *m_borrowBtn;
    QPushButton *m_returnBtn;
    QPushButton *m_deleteBtn;
    QPushButton *m_saveBtn;
    QPushButton *m_loadBtn;
    QPushButton *m_clearBtn;

    //selection
    LibraryItem *m_selectedItem;
};

#endif // MAINWINDOW_H
