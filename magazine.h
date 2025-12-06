
//Shaheer van Duyn
#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "libraryitem.h"

class Magazine : public LibraryItem
{
private:
    //Variables
    int m_issueNumber;
    QString m_publicationDate;

public:
    //Constructor
    Magazine(const QString &title = "", const QString &author = "", int id = 0,
             int issueNumber = 0, const QString &publicationDate = "");

    //Destructor
    virtual ~Magazine() {}

    //Getters
    int getIssueNumber() const;
    QString getPublicationDate() const;

    //Setters
    void setIssueNumber(int issueNumber);
    void setPublicationDate(const QString &publicationDate);

    //Override virtual functions from LibraryItems class
    QString displayInfo() const;
    QString getType() const;

    //Override file I/O methods
    QString toFileString() const;
    void fromFileString(const QString &data);
};

#endif // MAGAZINE_H
