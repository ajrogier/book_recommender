#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book
{
public:
    //By using const references, the constructor can read the values of the passed arguments without copying them, which can improve performance, especially for large objects like strings.
    Book(const QString &title, const QString &author, const QString &review);
    QString title() const;
    QString author() const;
    QString review() const;
    friend std::string escapeCSV(const std::string&);
    friend std::ostream& operator<<(std::ostream&, Book);
private:
    //https://www.geeksforgeeks.org/naming-convention-in-c/
    QString mTitle;
    QString mAuthor;
    QString mReview;
};

#endif // BOOK_H
