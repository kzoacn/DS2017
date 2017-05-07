﻿#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "minewindow.h"
using namespace sjtu;
AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}
void AdminWindow::load(string _id, shared_ptr<RailwayMinistry> _rm){
    admin=Admin(_id,_rm);
}

void AdminWindow::on_openCSV_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open CSV"), ".", tr("CSV Files(*.csv)"));
    if(path.length() == 0) {
               QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
     } else {
        ui->CSVPath->setText(path);
     }
}

void AdminWindow::on_load_clicked()
{
    admin.addTrainFromCSV(ui->CSVPath->text().toStdString());
    QMessageBox::information(NULL, tr("Path"), tr("Success!"));
}

void AdminWindow::on_queryInfo_clicked()
{
    MineWindow *mine=new MineWindow();
    mine->load(ui->user->text().toStdString(),admin.rw);
    mine->show();
}
