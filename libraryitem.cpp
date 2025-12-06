//Shaheer van Duyn
#include "libraryitem.h"
#include<QList>
//Constructor
LibraryItem::LibraryItem(const QString &title, const QString &author, int id)
    : m_title(title), m_author(author), m_id(id), m_isBorrowed(false) {}


//Getter functionality
QString LibraryItem::getTitle() const{
    return m_title;
}

QString LibraryItem::getAuthor() const
{
    return m_author;
}

int LibraryItem::getId() const
{
    return m_id;
}

bool LibraryItem::getIsBorrowed() const
{
    return m_isBorrowed;
}

//Setters
void LibraryItem::setTitle(const QString &title)
{
    m_title = title;
}

void LibraryItem::setAuthor(const QString &author)
{
    m_author = author;
}

void LibraryItem::setId(int id)
{
    m_id = id;
}

void LibraryItem::setIsBorrowed(bool borrowed)
{
    m_isBorrowed = borrowed;
}

QString LibraryItem::toFileString() const
{

    return QString("%1|%2|%3|%4|%5")
        .arg(m_id)
        .arg(getType(), m_title, m_author)
        .arg(m_isBorrowed ? "1":"0");
}

void LibraryItem::fromFileString(const QString &data)
{
    QStringList parts = data.split("|");
    if (parts.size() >= 5)
    {
        m_id = parts[0].toInt();
        m_title = parts[2];
        m_author = parts[3];
        m_isBorrowed = (parts[4] == "1");
    }
}
