
//Shaheer van Duyn
#include "magazine.h"
#include <QList>
Magazine::Magazine(const QString &title, const QString &author, int id,
                   int issueNumber, const QString &publicationDate)
    : LibraryItem(title, author, id), m_issueNumber(issueNumber), m_publicationDate(publicationDate)
{
}

int Magazine::getIssueNumber() const
{
    return m_issueNumber;
}

QString Magazine::getPublicationDate() const
{
    return m_publicationDate;
}

void Magazine::setIssueNumber(int issueNumber)
{
    m_issueNumber = issueNumber;
}

void Magazine::setPublicationDate(const QString &publicationDate)
{
    m_publicationDate = publicationDate;
}

QString Magazine::displayInfo() const
{
    QString status = getIsBorrowed() ? "Borrowed" : "Available";
    return QString("Magazine - Title: %1, Author: %2, Issue: %3, Date: %4, ID: %5, Status: %6")
        .arg(getTitle())
        .arg(getAuthor())
        .arg(m_issueNumber)
        .arg(m_publicationDate)
        .arg(getId())
        .arg(status);
}

QString Magazine::getType() const
{
    return "Magazine";
}

QString Magazine::toFileString() const
{
    // Format: ID|Magazine|Title|Author|IsBorrowed|IssueNumber|PublicationDate
    return QString("%1|Magazine|%2|%3|%4|%5|%6")
        .arg(getId())
        .arg(getTitle())
        .arg(getAuthor())
        .arg(getIsBorrowed() ? "1" : "0")
        .arg(m_issueNumber)
        .arg(m_publicationDate);
}

void Magazine::fromFileString(const QString &data)
{
    QStringList parts = data.split("|");
    if (parts.size() >= 7)
    {
        setId(parts[0].toInt());
        setTitle(parts[2]);
        setAuthor(parts[3]);
        setIsBorrowed(parts[4] == "1");
        m_issueNumber = parts[5].toInt();
        m_publicationDate = parts[6];
    }
}
