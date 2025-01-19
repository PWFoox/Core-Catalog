#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Добавляем несколько книг для примера
    publications.push_back(new Book("Война и мир", "Лев Толстой", 1869, "Роман", 1225));
    publications.push_back(new Book("Преступление и наказание", "Федор Достоевский", 1866, "Роман", 672));
    publications.push_back(new Book("Мастер и Маргарита", "Михаил Булгаков", 1967, "Фантастика", 480));

    updateBookList();
}

MainWindow::~MainWindow()
{
    for (auto pub : publications) {
        delete pub;
    }
    delete ui;
}

void MainWindow::updateBookList()
{
    ui->bookListWidget->clear();
    for (const auto pub : publications) {
        QString displayText = QString("%1 (%2)")
        .arg(pub->getTitle())
            .arg(pub->isAvailable() ? "В наличии" : "Выдана");
        ui->bookListWidget->addItem(displayText);
    }
}

void MainWindow::on_addBookButton_clicked()
{
    QString title = ui->titleEdit->text();
    QString author = ui->authorEdit->text();
    int year = ui->yearEdit->text().toInt();
    QString genre = ui->genreEdit->text();
    int pages = ui->pagesEdit->text().toInt();

    if (title.isEmpty() || author.isEmpty() || year == 0 || genre.isEmpty() || pages == 0) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля");
        return;
    }

    publications.push_back(new Book(title, author, year, genre, pages));
    updateBookList();

    // Очищаем поля ввода
    ui->titleEdit->clear();
    ui->authorEdit->clear();
    ui->yearEdit->clear();
    ui->genreEdit->clear();
    ui->pagesEdit->clear();
}

void MainWindow::on_borrowButton_clicked()
{
    int currentRow = ui->bookListWidget->currentRow();
    if (currentRow >= 0 && currentRow < publications.size()) {
        if (publications[currentRow]->isAvailable()) {
            publications[currentRow]->setAvailability(false);
            QMessageBox::information(this, "Успех", "Книга успешно выдана");
            updateBookList();
        } else {
            QMessageBox::warning(this, "Ошибка", "Книга уже выдана");
        }
    }
}

void MainWindow::on_returnButton_clicked()
{
    int currentRow = ui->bookListWidget->currentRow();
    if (currentRow >= 0 && currentRow < publications.size()) {
        if (!publications[currentRow]->isAvailable()) {
            publications[currentRow]->setAvailability(true);
            QMessageBox::information(this, "Успех", "Книга успешно возвращена");
            updateBookList();
        } else {
            QMessageBox::warning(this, "Ошибка", "Книга уже в библиотеке");
        }
    }
}
