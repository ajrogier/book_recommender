#include <QDir>
#include <QDebug>

#include "userwindow.h"
#include "./ui_userwindow.h"
#include "book.h"
#include "bookcollection.h"
#include "recommender.h"

UserWindow::UserWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserWindow)
{
    ui->setupUi(this);

    Recommender mRecommender = Recommender();

    //Let's start with the supplierCollection already loaded in.
    QString filePath = QString::fromStdString(std::string(CMAKE_BINARY_DIR) + "/collections/suppliercollection1.csv");
    mSupplierCollection.loadCollection(filePath);
    
    ui->supplierCollectionTableWidget->setRowCount(0);
    for(Book& supplierBook: mSupplierCollection.books()){
        addBookToCollectionTableWidget(supplierBook, ui->supplierCollectionTableWidget);
    }

    ui->userCollectionTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->recommendedCollectionTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->supplierCollectionTableWidget->horizontalHeader()->setStretchLastSection(true);
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::addBookToCollectionTableWidget(Book book, QTableWidget* collectionTableWidget)
{
    int newRow = collectionTableWidget->rowCount();
    collectionTableWidget->insertRow(newRow);

    collectionTableWidget->setItem(newRow, 0, new QTableWidgetItem(book.title()));
    collectionTableWidget->setItem(newRow, 1, new QTableWidgetItem(book.author()));
    collectionTableWidget->setItem(newRow, 2, new QTableWidgetItem(book.review()));
}


void UserWindow::on_addBookPushButton_clicked()
{
    QString title = ui->titleLineEdit->text();
    QString author = ui->authorLineEdit->text();
    QString review = ui->reviewTextEdit->toPlainText();

    Book newBook(title, author, review);
    mUserCollection.addBook(newBook);

    addBookToCollectionTableWidget(newBook,  ui->userCollectionTableWidget);
}

void UserWindow::on_saveCollectionPushButton_clicked()
{
    QString filePath = QString::fromStdString(std::string(CMAKE_BINARY_DIR) + "/collections/usercollection1.csv");
    mUserCollection.saveCollection(filePath);
}


void UserWindow::on_loadCollectionPushButton_clicked()
{
    QString filePath = QString::fromStdString(std::string(CMAKE_BINARY_DIR) + "/collections/usercollection1.csv");
    mUserCollection.loadCollection(filePath);


    ui->userCollectionTableWidget->setRowCount(0);
    for(Book& userBook: mUserCollection.books()){
        qDebug() << "Adding to userCollection: " << userBook.title();
        addBookToCollectionTableWidget(userBook, ui->userCollectionTableWidget);
    }
}


void UserWindow::on_recommendPushButton_clicked()
{
    ui->recommendedCollectionTableWidget->setRowCount(0);

    BookCollection recommendedCollection = mRecommender.recommend(mUserCollection, mSupplierCollection);
    for(Book& recommendedBook: recommendedCollection.books()){
        qDebug() << "Adding to recommendedCollection: " << recommendedBook.title();
        addBookToCollectionTableWidget(recommendedBook, ui->recommendedCollectionTableWidget);
    }
}

