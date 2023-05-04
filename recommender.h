#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include "bookcollection.h"

class Recommender
{
public:
    BookCollection recommend(const BookCollection& userCollection, const BookCollection& supplierCollection);
    BookCollection diff(const BookCollection& userCollection, const BookCollection& supplierCollection);
};

#endif // RECOMMENDER_H
