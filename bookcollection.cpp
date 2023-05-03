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
    //https://www.udacity.com/blog/2021/05/how-to-read-from-a-file-in-cpp.html
    std::ifstream file;
    std::string line;

    file.open(filePath.toStdString());
    if(file.is_open()) {
        while(std::getline(file, line)){
            std::istringstream ss(line);
            std::vector<QString> tokens;
            std::string token;
            while(std::getline(ss, token, ',')){
                tokens.push_back(QString::fromStdString(token));
            }
            Book book(tokens[0], tokens[1], tokens[2]);
            addBook(book);
        }
        file.close();
    }
}
