#include "minewindow.h"
#include "ui_minewindow.h"
#include <QStandardItemModel>
#include <QString>
#include "src/RailwayMinistry.hpp"
#include "src/Station.hpp"
#include <QMessageBox>
#include "minewindow.h"
#include "src/lib/shared_ptr.hpp"


MineWindow::MineWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MineWindow)
{
    ui->setupUi(this);
}

MineWindow::~MineWindow()
{
    delete ui;
}

void MineWindow::load(string id, shared_ptr<RailwayMinistry> _rm){
    user=User(id,_rm);
}

void MineWindow::on_queryTicket_clicked()
{
    vector<Ticket>tickets=user.queryTicket();
    QStandardItemModel  *model = new QStandardItemModel();
    model->setColumnCount(9);
    model->setHeaderData(0,Qt::Horizontal,tr("车次"));
    model->setHeaderData(1,Qt::Horizontal,tr("起点"));
    model->setHeaderData(2,Qt::Horizontal,tr("终点"));
    model->setHeaderData(3,Qt::Horizontal,tr("出发时间"));
    model->setHeaderData(4,Qt::Horizontal,tr("到达时间"));
    model->setHeaderData(5,Qt::Horizontal,tr("经过时间"));
    model->setHeaderData(6,Qt::Horizontal,tr("座位种类"));
    model->setHeaderData(7,Qt::Horizontal,tr("个数"));
    model->setHeaderData(8,Qt::Horizontal,tr("单价"));
    for(int i=0;i<tickets.size();i++){
        Ticket tic=tickets[i];
        model->setItem(i,0,new QStandardItem(QString::fromStdString(tic.getTrain())));
        model->setItem(i,1,new QStandardItem(QString::fromStdString(tic.getStart().getName())));
        model->setItem(i,2,new QStandardItem(QString::fromStdString(tic.getTarget().getName())));
        model->setItem(i,3,new QStandardItem(QString::fromStdString(tic.getStartDate().to_string())));
        model->setItem(i,4,new QStandardItem(QString::fromStdString(tic.getTargetDate().to_string())));
        model->setItem(i,5,new QStandardItem(QString::number(tic.getTargetDate()-tic.getStartDate())));
        model->setItem(i,6,new QStandardItem(QString::fromStdString(Ticket::to_string(tic.getLevel()))));
        model->setItem(i,7,new QStandardItem(QString::number(tic.getNum())));
        model->setItem(i,8,new QStandardItem(QString::number(tic.getCost())));
    }
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

}
