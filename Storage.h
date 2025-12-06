
//Shaheer van Duyn

#ifndef STORAGE_H
#define STORAGE_H

#include <QList>



template <typename T>
class Storage
{
private:
    QList<T> m_items;

public:
    //Constructor
    Storage() = default;

    //Destructor
    ~Storage() = default;

    //Add an item to storage
    void addItem(const T &item)
    {
        m_items.append(item);
    }

    //Remove an item from storage
    bool removeItem(const T &item)
    {
        int index = m_items.indexOf(item);
        if (index != -1)
        {
            m_items.removeAt(index);
            return true;
        }
        return false;
    }

    //Remove item by index
    bool removeItemAt(int index)
    {
        if (index >= 0 && index < m_items.size())
        {
            m_items.removeAt(index);
            return true;
        }
        return false;
    }

    //Search for items
    template <typename Predicate>
    QList<T> search(Predicate pred) const
    {
        QList<T> results;
        for (const auto &item : m_items)
        {
            if (pred(item))
            {
                results.append(item);
            }
        }
        return results;
    }

    //Get item by index
    T getItem(int index) const
    {
        if (index >= 0 && index < m_items.size())
        {
            return m_items.at(index);
        }
        return T();
    }

    //Get all items
    QList<T> getAllItems() const
    {
        return m_items;
    }

    //Get size of storage
    int size() const
    {
        return m_items.size();
    }

    //Check if storage is empty
    bool isEmpty() const
    {
        return m_items.isEmpty();
    }

    //Clear all items
    void clear()
    {
        m_items.clear();
    }









};

#endif // STORAGE_H
