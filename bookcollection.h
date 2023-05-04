#ifndef BOOKCOLLECTION_H
#define BOOKCOLLECTION_H

#include <QList>
#include "book.h"

class BookCollection
{
public:
    QList<Book> books() const;
    void addBook(const Book &book);
    int count() const;
    Book bookAt(int index) const;
    void clear();
    void saveCollection(const QString &filePath);
    void loadCollection(const QString &filePath);
private:
    QList<Book> mBooks;
};

#endif // BOOKCOLLECTION_H
