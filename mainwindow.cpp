#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      aBookHandler(new address_book_handler(this))
{
    ui->setupUi(this);
    ui->tableView->setModel(aBookHandler);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_Address_Book_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Address Book"), "",
                                                    tr("Adress Book (*.csv);;All Files (*)"));
    aBookHandler->openFile(fileName);
}

void MainWindow::on_num1_clicked()
{
    this->updateDialedNum(QString("1"));
}

void MainWindow::on_num2_clicked()
{
    this->updateDialedNum(QString("2"));
}

void MainWindow::on_num3_clicked()
{
    this->updateDialedNum(QString("3"));
}

void MainWindow::on_num4_clicked()
{
    this->updateDialedNum(QString("4"));
}

void MainWindow::on_num5_clicked()
{
    this->updateDialedNum(QString("5"));
}

void MainWindow::on_num6_clicked()
{
    this->updateDialedNum(QString("6"));
}

void MainWindow::on_num7_clicked()
{
    this->updateDialedNum(QString("7"));
}

void MainWindow::on_num8_clicked()
{
    this->updateDialedNum(QString("8"));
}

void MainWindow::on_num9_clicked()
{
    this->updateDialedNum(QString("9"));
}

void MainWindow::on_num0_clicked()
{
    this->updateDialedNum(QString("0"));
}

void MainWindow::updateDialedNum(QString str)
{
    if (isdigit(str.toStdString()[0]) && this->dialedNum.length() < 12) {
        switch (this->dialedNum.length()) {
            case 3:
            case 7:
                this->dialedNum += "-";
        }
        this->dialedNum += str[0];
    } else {
        return;
    }
    ui->numBox->setText(this->dialedNum);
    aBookHandler->setFilterString(this->dialedNum);
}

void MainWindow::on_delChar_clicked()
{
    if (this->dialedNum.length() > 0) {
        this->dialedNum.remove(this->dialedNum.length() - 1, 1);
        aBookHandler->setFilterString(this->dialedNum);
        ui->numBox->setText(this->dialedNum);
    }
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    this->dialedNum = aBookHandler->getPhoneNumber(index.row());
    ui->numBox->setText(this->dialedNum);
    aBookHandler->setFilterString(this->dialedNum);
}
