#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include "bookcollection.h"
#include "word2vec++/include/word2vec.hpp"

class Recommender
{
public:
    Recommender();
    void loadEmbeddings();
    std::unique_ptr<w2v::w2vModel_t>& word2VecModel();
    w2v::d2vModel_t doc2VecModel();
    BookCollection recommend(const BookCollection& userCollection, const BookCollection& supplierCollection);
    BookCollection dummyRecommend(const BookCollection& userCollection, const BookCollection& supplierCollection);
    BookCollection diff(const BookCollection& userCollection, const BookCollection& supplierCollection);
private:
    std::unique_ptr<w2v::w2vModel_t> mWord2VecModel;
    w2v::d2vModel_t mDoc2VecModel;
};

#endif // RECOMMENDER_H
