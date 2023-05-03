#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "bookcollection.h"

QList<Book> BookCollection::books()
{
    return mBooks;
}


void BookCollection::addBook(const Book &book)
{
    mBooks.append(book);
}

int BookCollection::count() const
{
    return mBooks.count();
}

Book BookCollection::bookAt(int index) const
{
    return mBooks.at(index);
}

void BookCollection::clear()
{
    mBooks.clear();
}

void BookCollection::saveCollection(const QString &filePath)
{
    //https://cplusplus.com/doc/tutorial/files/
    std::ofstream file;
    file.open(filePath.toStdString());
    int bookCount = count();
    if(file.is_open()) {
        for(int i=0; i<bookCount; ++i){
            Book book = bookAt(i);
            file << book << "\n";
        }
        file.close();
    }
}

void BookCollection::loadCollection(const QString &filePath)
{
    clear();
    //https://cplusplus.com/doc/tutorial/files/
    std::ifstream file;
    std::string line;

    file.open(filePath.toStdString());
    if(file.is_open()) {
        while(std::getline(file, line)){
            std::string field;
            std::ostringstream fieldStream;
            std::vector<QString> fields;

            bool inQuotes = false;

            for (char c : line) {
                if (c == '"') {
                    inQuotes = !inQuotes;
                } else if (c == ',' && !inQuotes) {
                    field = fieldStream.str();
                    fields.push_back(QString::fromStdString(field));
                    fieldStream.str("");
                    fieldStream.clear();
                } else {
                    fieldStream << c;
                }
            }
            field = fieldStream.str();
            fields.push_back(QString::fromStdString(field));

            Book book(fields[0], fields[1], fields[2]);
            addBook(book);
        }
        file.close();
    }
}
