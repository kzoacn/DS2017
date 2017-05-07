﻿

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QString>
#include "src/RailwayMinistry.hpp"
#include "src/Station.hpp"
#include <QMessageBox>
using namespace sjtu;
using std::to_string;
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

void MainWindow::load(string _id, shared_ptr<RailwayMinistry> _rm){
    user=User(_id,_rm);
}

void MainWindow::on_search_clicked()
{
    QStandardItemModel  *model = new QStandardItemModel();
    model->setColumnCount(16);
    model->setHeaderData(0,Qt::Horizontal,tr("车次"));
    model->setHeaderData(1,Qt::Horizontal,tr("起点"));
    model->setHeaderData(2,Qt::Horizontal,tr("终点"));
    model->setHeaderData(3,Qt::Horizontal,tr("出发时间"));
    model->setHeaderData(4,Qt::Horizontal,tr("到达时间"));
    model->setHeaderData(5,Qt::Horizontal,tr("经过时间"));
    model->setHeaderData(6,Qt::Horizontal,tr("二等座"));
    model->setHeaderData(7,Qt::Horizontal,tr("一等座"));
    model->setHeaderData(8,Qt::Horizontal,tr("商务座"));
    model->setHeaderData(9,Qt::Horizontal,tr("特等座"));
    model->setHeaderData(10,Qt::Horizontal,tr("无座"));
    model->setHeaderData(11,Qt::Horizontal,tr("软座"));
    model->setHeaderData(12,Qt::Horizontal,tr("硬座"));
    model->setHeaderData(13,Qt::Horizontal,tr("高级软卧"));
    model->setHeaderData(14,Qt::Horizontal,tr("软卧下"));
    model->setHeaderData(15,Qt::Horizontal,tr("硬卧下"));
    Station a,b;
    a=Station(ui->start->text().toStdString());
    b=Station(ui->target->text().toStdString());
    Date date(2017,3,28,0,0);
    vector<Train>trains=user.getTrainByST(a,b,date);
    for(int i=0;i<trains.size();i++){
        model->setItem(i,0,new QStandardItem(QString::fromStdString(trains[i].getID())));
        model->setItem(i,1,new QStandardItem(QString::fromStdString(a.getName())));
        model->setItem(i,2,new QStandardItem(QString::fromStdString(b.getName())));
        model->setItem(i,3,new QStandardItem(QString::fromStdString(trains[i].getTime(date,a).to_string())));
        model->setItem(i,4,new QStandardItem(QString::fromStdString(trains[i].getTime(date,b).to_string())));
        model->setItem(i,5,new QStandardItem(QString::fromStdString(to_string((trains[i].getTime(date,b)-trains[i].getTime(date,a))))));
        for(int l=0;l<10;l++){
            if(trains[i].getCost(a,b,Ticket::toLevel(l))==0)
                model->setItem(i,6+l,new QStandardItem("-"));
            else
                model->setItem(i,6+l,new QStandardItem(QString::fromStdString(to_string((trains[i].getCost(a,b,Ticket::toLevel(l)))))));
        }
    }
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}



void MainWindow::on_train_query_clicked()
{
    QStandardItemModel  *model = new QStandardItemModel();
    model->setColumnCount(19);
    model->setHeaderData(0,Qt::Horizontal,tr("车次"));
    Train train=user.getTrainByID(ui->train_number->text().toStdString());

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

}

void MainWindow::on_buy_clicked()
{
    int row=ui->tableView->currentIndex().row();
    int col=ui->tableView->currentIndex().column();
    string trainid = (ui->tableView->model()->index(row,0,QModelIndex()).data())
                                .toString().toStdString();
    Station a,b;
    a=Station(ui->start->text().toStdString());
    b=Station(ui->target->text().toStdString());
    Date date(2017,3,28,0,0);
    TicketLevel level=Ticket::toLevel(ui->tableView->model()->headerData(col,Qt::Horizontal).toString().toStdString());
    user.buyTicket(trainid,a,b,level,1,date);
    QMessageBox::information(NULL, tr("提示"), tr("购票成功"));
}


void MainWindow::on_mine_clicked()
{

}
