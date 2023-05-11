#include <iostream>
#include <QDebug>
#include "recommender.h"

Recommender::Recommender():  mDoc2VecModel(0)
{
    // Load the embeddings constituting the Word2Vec model on startup
    loadEmbeddings();
    w2v::d2vModel_t mDoc2VecModel = w2v::d2vModel_t(word2VecModel()->vectorSize());
}

void Recommender::loadEmbeddings()
{
    try {
        word2VecModel().reset(new w2v::w2vModel_t());
        // load w2v model file
        if (!word2VecModel()->load(std::string(CMAKE_BINARY_DIR)+"/embeddings/GoogleNews-vectors-negative300.bin")) {
            throw std::runtime_error(word2VecModel()->errMsg());
        }
    } catch (const std::exception &_e) {
        std::cerr << _e.what() << std::endl;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
    }
}

std::unique_ptr<w2v::w2vModel_t>& Recommender::word2VecModel()
{
    return mWord2VecModel;
}

BookCollection Recommender::recommend(const BookCollection& userCollection, const BookCollection& supplierCollection)
{
    BookCollection recommendedCollection;
    // Only use the books in the supplierCollection that are not part of the UserCollection
    BookCollection diffSupplierCollection = diff(userCollection, supplierCollection);

    w2v::d2vModel_t doc2VecModel(word2VecModel()->vectorSize());
    int diffSupplierCount = diffSupplierCollection.count();
    // Build the doc2VecModel based on supplierBook review
    for(int i = 0; i < diffSupplierCount; ++i){
        // We will recommend based on the reviews
        QString supplierReview = diffSupplierCollection.bookAt(i).review();
        // Convert the text of the review to an embedding vector
        w2v::doc2vec_t doc2Vec(word2VecModel(), supplierReview.toStdString());
        // Add the vector with ID = i to the model
        doc2VecModel.set(i, doc2Vec);
    }

    // For now we will assume that the embedding of the concatenation of all the reviews is a solid representation of the user.
    std::string completeReview;
    for(Book& userBook: userCollection.books()){
        completeReview += userBook.review().toStdString();
    }

    // Embed the entire users collection
    w2v::doc2vec_t doc2Vec(word2VecModel(), completeReview);

    // Create a vector of book indices and distances in descending order on distance
    std::vector<std::pair<std::size_t, float>> nearestSupplierBookIndices;
    doc2VecModel.nearest(doc2Vec, nearestSupplierBookIndices, doc2VecModel.modelSize());

    // Finally fill the recommendedCollection
    for (auto const &i: nearestSupplierBookIndices) {
        qDebug() << "Adding to recommendedCollection: " << diffSupplierCollection.bookAt(i.first).title() << ", distance: "<< i.second;
        recommendedCollection.addBook(diffSupplierCollection.bookAt(i.first));
    }
    return recommendedCollection;

}

BookCollection Recommender::dummyRecommend(const BookCollection& userCollection, const BookCollection& supplierCollection)
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
