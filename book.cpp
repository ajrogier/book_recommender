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


std::string escapeCSV(const std::string& input)
{
    std::string output = "\"";
    for (const auto& ch : input) {
        if (ch == '\"') {
            output += "\"\"";
        } else {
            output += ch;
        }
    }
    output += "\"";
    return output;
}

std::ostream& operator<<(std::ostream& os, Book book)
{
    return os << escapeCSV(book.title().toStdString()) << "," << escapeCSV(book.author().toStdString()) << "," << escapeCSV(book.review().toStdString());
}
