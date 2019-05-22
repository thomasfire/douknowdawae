#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int n = ui->lineEdit_2->text().toInt();
    int size = ui->lineEdit_3->text().toInt();
    mpf = new MapField(QString("generate"), n, size);
    mpf->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open a Matrix", QDir::homePath());
    // int n = ui->label->text().toInt();
    // int m = ui->label_2->text().toInt();
    int size = ui->lineEdit_3->text().toInt();
    mpf = new MapField(filename, 0, size);
    mpf->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    int n = ui->lineEdit_2->text().toInt();
    int size = ui->lineEdit_3->text().toInt();
    mpf = new MapField(QString("blank"), n, size);
    mpf->show();
}
