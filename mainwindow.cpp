



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QString>
#include "src/RailwayMinistry.hpp"
#include "src/Station.hpp"
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
    model->setColumnCount(19);
    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("车次"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("起点"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("终点"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("出发时间"));
    model->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("到达时间"));
    model->setHeaderData(5,Qt::Horizontal,QString::fromLocal8Bit("经过时间"));
    model->setHeaderData(6,Qt::Horizontal,QString::fromLocal8Bit("商务座"));
    model->setHeaderData(7,Qt::Horizontal,QString::fromLocal8Bit("特等座"));
    model->setHeaderData(8,Qt::Horizontal,QString::fromLocal8Bit("一等座"));
    model->setHeaderData(9,Qt::Horizontal,QString::fromLocal8Bit("二等座"));
    model->setHeaderData(10,Qt::Horizontal,QString::fromLocal8Bit("高级软卧ui->start->text()"));
    model->setHeaderData(11,Qt::Horizontal,QString::fromLocal8Bit("软卧"));
    model->setHeaderData(12,Qt::Horizontal,QString::fromLocal8Bit("硬卧"));
    model->setHeaderData(13,Qt::Horizontal,QString::fromLocal8Bit("软座"));
    model->setHeaderData(14,Qt::Horizontal,QString::fromLocal8Bit("硬座"));
    model->setHeaderData(15,Qt::Horizontal,QString::fromLocal8Bit("无座"));
    model->setHeaderData(16,Qt::Horizontal,QString::fromLocal8Bit("高级软卧"));
    model->setHeaderData(17,Qt::Horizontal,QString::fromLocal8Bit("软卧下"));
    model->setHeaderData(18,Qt::Horizontal,QString::fromLocal8Bit("硬卧下"));
    Station a,b;
    a=Station(ui->start->text().toStdString());
    b=Station(ui->target->text().toStdString());
    vector<Train>trains=user.getTrainByST(a,b,Date(1998,1,1,12,12));
    for(int i=0;i<trains.size();i++){
        model->setItem(i,0,new QStandardItem(QString::fromStdString(trains[i].getID())));
        model->setItem(i,1,new QStandardItem(QString::fromStdString(a.getName())));
        model->setItem(i,2,new QStandardItem(QString::fromStdString(b.getName())));
        model->setItem(i,3,new QStandardItem(QString::fromStdString(trains[i].getTime(a).to_string())));
        model->setItem(i,4,new QStandardItem(QString::fromStdString(trains[i].getTime(b).to_string())));
    }
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
