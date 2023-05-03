#ifndef DUMMYRECOMMENDER_H
#define DUMMYRECOMMENDER_H

#include <vector>
#include "book.h"

// Dummy recommender idea: Just return books with the same genre and if possible author, then sort according to title.
class DummyRecommender
{
public:
    DummyRecommender();
    void train(const std::vector<Book> &catalog);
    Book recommend();
};

#endif // DUMMYRECOMMENDER_H
