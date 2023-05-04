#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "bookcollection.h"
#include "recommender.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UserWindow; }
QT_END_NAMESPACE

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    UserWindow(QWidget *parent = nullptr);
    ~UserWindow();

private slots:
    void addBookToCollectionTableWidget(Book, QTableWidget*);
    void on_addBookPushButton_clicked();
    void on_saveCollectionPushButton_clicked();
    void on_loadCollectionPushButton_clicked();
    void on_recommendPushButton_clicked();

private:
    Ui::UserWindow *ui;
    BookCollection mUserCollection;
    BookCollection mSupplierCollection;
    Recommender mRecommender;
};
#endif // USERWINDOW_H
