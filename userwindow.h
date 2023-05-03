#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include "bookcollection.h"

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
    void on_addBookPushButton_clicked();
    void on_saveCollectionPushButton_clicked();
    void on_loadCollectionPushButton_clicked();
    void addBookToCollectionTableWidget_new(Book);
private:
    Ui::UserWindow *ui;
    BookCollection mBookCollection;
};
#endif // USERWINDOW_H
