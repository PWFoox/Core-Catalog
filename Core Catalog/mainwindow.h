#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QString>
#include "publication.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addBookButton_clicked();
    void on_borrowButton_clicked();
    void on_returnButton_clicked();
    void updateBookList();

private:
    Ui::MainWindow *ui;
    std::vector<Publication*> publications;
};
#endif // MAINWINDOW_H
