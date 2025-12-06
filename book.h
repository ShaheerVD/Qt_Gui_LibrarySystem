
//Shaheer van Duyn
#ifndef BOOK_H
#define BOOK_H

#include "libraryitem.h"


class Book : public LibraryItem
{
private:
    //variables
    QString m_genre;
    int m_pageCount;

public:
    //constructor
    Book(const QString &title = "", const QString &author = "", int id = 0,
         const QString &genre = "", int pageCount = 0);

    //destructor
    virtual ~Book() {}

    //getters
    QString getGenre() const;
    int getPageCount() const;

    //setters
    void setGenre(const QString &genre);
    void setPageCount(int pageCount);

    //Override virtual functions from LibraryItems class
    QString displayInfo() const;
    QString getType() const;

    // Override file I/O methods
    QString toFileString() const;
    void fromFileString(const QString &data);
};

#endif // BOOK_H
