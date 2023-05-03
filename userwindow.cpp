#include <QDir>
#include <QDebug>

#include "userwindow.h"
#include "./ui_userwindow.h"
#include "book.h"

UserWindow::UserWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserWindow)
{
    ui->setupUi(this);
}

UserWindow::~UserWindow()
{
    delete ui;
}

void  UserWindow::addBookToCollectionTableWidget_new(Book book){
    int newRow = ui->collectionTableWidget->rowCount();
    ui->collectionTableWidget->insertRow(newRow);

    ui->collectionTableWidget->setItem(newRow, 0, new QTableWidgetItem(book.title()));
    ui->collectionTableWidget->setItem(newRow, 1, new QTableWidgetItem(book.author()));
    ui->collectionTableWidget->setItem(newRow, 2, new QTableWidgetItem(book.review()));
}


void UserWindow::on_addBookPushButton_clicked()
{
    QString title = ui->titleLineEdit->text();
    QString author = ui->authorLineEdit->text();
    QString review = ui->reviewTextEdit->toPlainText();

    Book newBook(title, author, review);
    mBookCollection.addBook(newBook);

    addBookToCollectionTableWidget_new(newBook);
}

void UserWindow::on_saveCollectionPushButton_clicked()
{
    QDir currentDir = QDir::currentPath();
    QString filePath = currentDir.absoluteFilePath("../../../../book_recommender/collections/collection1.csv");
    mBookCollection.saveCollection(filePath);
}

void UserWindow::on_loadCollectionPushButton_clicked()
{
    QDir currentDir = QDir::currentPath();
    QString filePath = currentDir.absoluteFilePath("../../../../book_recommender/collections/collection1.csv");
    mBookCollection.loadCollection(filePath);

    int bookCount = mBookCollection.count();

    ui->collectionTableWidget->setRowCount(0);
    for(int i=0; i<bookCount; ++i){
        Book newBook = mBookCollection.bookAt(i);
        addBookToCollectionTableWidget_new(newBook);
    }
}

