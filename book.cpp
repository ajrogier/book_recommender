#include <iostream>
#include "book.h"

Book::Book(const QString &title, const QString &author, const QString &review): mTitle(title), mAuthor(author), mReview(review){}

QString Book::title() const
{
    return mTitle;
}

QString Book::author() const
{
    return mAuthor;
}

QString Book::review() const
{
    return mReview;
}

std::ostream& operator<<(std::ostream& os, Book book)
{
    return os << book.title().toStdString() << "," << book.author().toStdString() << "," << book.review().toStdString();
}
