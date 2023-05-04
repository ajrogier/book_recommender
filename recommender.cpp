    #include <QDebug>
#include "recommender.h"

BookCollection Recommender::recommend(const BookCollection& userCollection, const BookCollection& supplierCollection)
{
    BookCollection recommendedCollection;
    recommendedCollection = diff(userCollection, supplierCollection);
    return recommendedCollection;
}

BookCollection Recommender::diff(const BookCollection& userCollection, const BookCollection& supplierCollection)
{
    //Diff between userCollection and supplierCollection to find books unread by the user.
    BookCollection diffCollection;

    for(Book& supplierBook: supplierCollection.books()){
        bool found = false;
        for(Book& userBook: userCollection.books()){
            found = supplierBook.title() == userBook.title() && supplierBook.author() == userBook.author();
            if (found){
                break;
            }
        }
        if (!found){
            diffCollection.addBook(supplierBook);
        }
    }
    return diffCollection;
}
