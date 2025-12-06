
//Shaheer van Duyn
#include "book.h"
#include <QList>
//Constructor
Book::Book(const QString &title, const QString &author, int id,
           const QString &genre, int pageCount)
    : LibraryItem(title, author, id), m_genre(genre), m_pageCount(pageCount)
{
}
//Getters
QString Book::getGenre() const
{
    return m_genre;
}

int Book::getPageCount() const
{
    return m_pageCount;
}
//Setters
void Book::setGenre(const QString &genre)
{
    m_genre = genre;
}

void Book::setPageCount(int pageCount)
{
    m_pageCount = pageCount;
}

//Overriden displayinfo
QString Book::displayInfo() const
{
    QString status = getIsBorrowed() ? "Borrowed" : "Available";
    return QString("Book - Title: %1, Author: %2, Genre: %3, Pages: %4, ID: %5, Status: %6")
        .arg(getTitle())
        .arg(getAuthor())
        .arg(m_genre)
        .arg(m_pageCount)
        .arg(getId())
        .arg(status);
}

QString Book::getType() const
{
    return "Book";
}

QString Book::toFileString() const
{
    // Format: ID|Book|Title|Author|IsBorrowed|Genre|PageCount
    return QString("%1|Book|%2|%3|%4|%5|%6")
        .arg(getId())
        .arg(getTitle())
        .arg(getAuthor())
        .arg(getIsBorrowed() ? "1" : "0")
        .arg(m_genre)
        .arg(m_pageCount);
}

void Book::fromFileString(const QString &data)
{
    QStringList parts = data.split("|");
    if (parts.size() >= 7)
    {
        setId(parts[0].toInt());
        setTitle(parts[2]);
        setAuthor(parts[3]);
        setIsBorrowed(parts[4] == "1");
        m_genre = parts[5];
        m_pageCount = parts[6].toInt();
    }
}
