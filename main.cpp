#include "userwindow.h"

#include <QApplication>

class Recommender {
    // Dummy recommender idea: Just return books with the same genre and if possible author, then sort according to title.
public:
    void train(const std::vector<Book>& catalog);
    Book recommend();
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UserWindow w;
    w.show();
    return a.exec();
}
