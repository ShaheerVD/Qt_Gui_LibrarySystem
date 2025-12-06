
//Shaheer van Duyn
#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <QString>
class LibraryItem
//Base class
{

private:
    QString m_title;
    QString m_author;
    int m_id;
    bool m_isBorrowed;

public:
    //Constructor
    LibraryItem(const QString &title ="", const QString &author = "", int id = 0);

    ~LibraryItem(){}

    //getter
    QString getTitle()const;
    QString getAuthor() const;
    int getId() const;
    bool getIsBorrowed() const;

    //setters
    void setTitle(const QString &title);
    void setAuthor(const QString &author);
    void setId(int id);
    void setIsBorrowed(bool borrowed);

    //virtual functions
    virtual QString displayInfo() const = 0;
    virtual QString getType() const = 0;


    virtual QString toFileString() const;
    virtual void fromFileString(const QString &data);

};

#endif // LIBRARYITEM_H
